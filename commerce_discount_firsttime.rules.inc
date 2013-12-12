<?php

/**
 * Implements hook_rules_condition_info()
 */
function commerce_discount_firsttime_rules_condition_info() {
  $inline_conditions = inline_conditions_get_info();
  $conditions = array();
  $conditions['commerce_order_first_time'] = array(
      'label' => t('Users First Order'),
      'parameter' => array(
          'commerce_order' => array(
              'label' => t('Order'),
              'description' => t('The order.'),
              'type' => 'commerce_order',
              'wrapped' => TRUE
          ),
      ),
      'module' => 'commerce_discount_firsttime',
      'group' => t('Commerce Order'),
      'callbacks' => array(
          'execute' => $inline_conditions['commerce_order_first_time']['callbacks']['build'],
      ),
  );

  return $conditions;
}


/**
 * Conditions to implement commerce_order_first_time rule
 */
function commerce_discount_firsttime_customer_build(EntityDrupalWrapper $wrapper) {
  $uid = $wrapper->uid->value();

  // If user is anonymous validate discount
  if($uid === '0') {
    return TRUE;
  }
  else {
    // Get given total order amount.
    $sql = 'SELECT COUNT(uid) FROM {commerce_order} WHERE uid = :uid';
    $total_orders = db_query($sql, array(':uid' => $uid))->fetchField();

    // If user has 1 or fewer orders
    if($total_orders <= 1) {
      return TRUE;
    }
  }

  return FALSE;
}
