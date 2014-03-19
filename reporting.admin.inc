<?php

/**
 * Settings form as implemented by hook_menu.
 */
function reporting_admin_settings($form, &$form_state) {
  $options = array();
  $query = db_select('field_config', 'n')
  ->fields('n', array('field_name'))
  ->execute();

  $fields = $query->fetchAll();
  foreach ($fields as $field){
    $options['field_data_' . $field->field_name] = 'field_data_' . $field->field_name;
  }
  
  $form['reporting_js'] = array(
    '#type' => 'checkboxes',
    '#title' => t(' '),
    '#description' => t(' '),
    '#default_value' => variable_get('reporting_js', 1),
    '#options'  => $options,
  );

  return system_settings_form($form);
}