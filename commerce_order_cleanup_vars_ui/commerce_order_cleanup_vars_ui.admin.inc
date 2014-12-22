<?php

/**
 * @file
 * Admin form(s) for Commerce Order Cleanup Vars UI module.
 */

/**
 * List the variables set that are in the format to be used by Commerce Order
 * Cleanup.
 */
function commerce_order_cleanup_vars_ui_summary() {
  $content = array(
    'summary' => array(
      '#markup' => t('Table lists any variables that !link
        module will use, if any are set.', array('!link' => l('Commerce Order Cleanup', 'admin/commerce/config/order-cleanup'))),
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => array(t('Variable name'), t('Description'), t('Value')),
      '#rows' => array(),
    ),
  );

  foreach (commerce_product_types() as $type_key => $type_definition) {
    foreach (commerce_order_statuses() as $status_key => $status_definition) {
      foreach (array('min', 'max') as $range) {
        $variable_name = 'commerce_order_cleanup_' . $range . '_' . $type_key . '_' . $status_key;
        $variable_value = variable_get($variable_name, '');

        if ($variable_value) {
          $content['table']['#rows'][] = array(
            $variable_name,
            t('Orders containing "@product_type" products with a status of
              "@order_status" @range range constraint',
                array(
                  '@product_type' => $type_definition['name'],
                  '@order_status' => $status_definition['title'],
                  '@range' => $range
                )
            ),
            $variable_value,
          );
        }
      }
    }
  }

  if (!$content['table']['#rows']) {
    $content['table']['#rows'][] = array(
      array(
        'data' => t('No variable(s) to show.'),
        'colspan' => 3
      ),
    );
  }

  return $content;
}
