<?php

function reporting_admin_settings($form, &$form_state) {
  $graph_types = array(
    'GeoChart' => t('GeoChart'),
    'TreeMap' => t('TreeMap'),
    'PieChart' => t('PieChart'), 
    'BarChart' => t('BarChart')
  );

  $options = array();
  $query = db_select('field_config', 'n')
  ->fields('n', array('field_name'))
  ->execute();

  $fields = $query->fetchAll();
  foreach ($fields as $field) {
    $options[$field->field_name] = $field->field_name;
  }

  $form['reporting_js']['reporting'] = array(
    '#type' => 'checkboxes',
    '#title' => t(' '),
    '#description' => t(' '),
    '#default_value' => variable_get('reporting', 1),
    '#options'  => $options,
  );

  foreach ($options as $label) {
    $form['reporting_js']['node-options-'.$label] = array(
    '#type'         =>  'radios',
    '#title'        =>  t($label),
    '#options'      =>  $graph_types,
    '#multiple'     =>  FALSE,
    '#default_value' => variable_get('node-options-'.$label, 'PieChart'),
    '#states' => array(
    'visible' => array(
      ':input[name="reporting['.$label.']"]' => array('checked' => TRUE), // We use "reporting" and its Nth option. in above field, See #options in above checkboxes field.
      ),
    ),
    );
  } 

  return system_settings_form($form);
}

?>