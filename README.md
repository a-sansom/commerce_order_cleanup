commerce_order_cleanup
======================

Allows to delete orders by various filters(like last changed date, status).


<img src="https://travis-ci.org/vijaycs85/commerce_order_cleanup.svg?branch=7.x-1.x" />

<img src="https://insight.sensiolabs.com/projects/8f86b6bf-cee3-4456-97d5-88a67ca7bef9/big.png" />

Configuration
-------------

Provides list of variables to control the delete process.

1. <strong>commerce_order_cleanup_batch_size</strong> - The delete operation batch size. Default to 100.
2. <strong>commerce_order_cleanup_max_date</strong> - The most earliest date allowed to delete orders. Can be changed from configuration page.
3. <strong>commerce_order_cleanup_min_date</strong> - The most oldest date allowed to delete orders. Delete for commerce project created date (October 15, 2009 9:41pm). 
