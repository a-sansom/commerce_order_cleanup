<?php

/**
 * @file
 * Admin settings form for commerce Order Cleanup module.
 */

/**
 * Commerce order cleanup settings form.
 **/
function commerce_order_cleanup_settings() {
  $form = array();
  $period_options = array(
    '1 month',
    '2 months',
    '3 months',
    '6 months',
    '9 months',
    '1 year',
    '2 years',
    '3 years',
  );

  $form['commerce_order_cleanup_batch_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Batches size of bulk delete'),
    '#default_value' => variable_get('commerce_order_cleanup_batch_size', 100),
    '#description' => t('Orders will be deleted as a small batches to avoid timeout.'),
  );

  $form['commerce_order_cleanup_max_date'] = array(
    '#type' => 'select',
    '#title' => t('Allow to delete orders changed before'),
    '#default_value' => variable_get('commerce_order_cleanup_max_date', '1 year'),
    '#options' => array_combine($period_options, $period_options),
    '#description' => t('Allowed to delete orders that are changed up to given period here. It will be dangerous to allow to delete orders changed on current date.'),
  );

  return system_settings_form($form);
}

/**
 * Batch process callback.
 *
 * @param $nids
 *
 * @return mixed
 *
 * @see drush_commerce_order_cleanup_delete_orders()
 */
function commerce_order_cleanup_delete_multiple($nids) {
  $result = commerce_order_delete_multiple($nids);
  $_SESSION['commerce_order_deleted'] += count($nids);
  drupal_set_message(t('Deleted @node_count orders.', array('@node_count' => $_SESSION['commerce_order_deleted'],)));
  return $result;
}


/**
 * Batch finish callback.
 *
 * @param $success
 * @param $results
 * @param $operations
 *
 * @see drush_commerce_order_cleanup_delete_orders()
 */
function commerce_order_cleanup_delete_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Deleted all orders successfully.'));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
  unset($_SESSION['commerce_order_total'], $_SESSION['commerce_order_deleted']);
}
