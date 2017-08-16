<?php
/**
 * @file
 * Management form for the Islandora Orphaned Objects module.
 */

/**
 * Builds the management form for the Orphaned Objects module.
 *
 * @param array $form
 *   An array representing a form within Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 *
 * @return array
 *   An array containing the form to be rendered.
 */
function islandora_orphaned_objects_manage_form($form, $form_state) {
  module_load_include('inc', 'islandora_orphaned_objects', 'includes/utilities');

  if (isset($form_state['show_confirm'])) {
    $form['confirm_message'] = array(
      '#type' => 'item',
      '#markup' => format_plural(count($form_state['pids_to_delete']),
      'Are you sure you want to delete the 1 object?',
      'Are you sure you want to delete the @count objects?'),
    );
    $form['confirm_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Confirm'),
      '#weight' => 2,
      '#submit' => array('islandora_orphaned_objects_manage_confirm_submit'),
    );
    $form['cancel_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#weight' => 3,
    );
  }
  else {
    $orphaned_objects = islandora_orphaned_objects_get_orphaned_objects();
    $rows = array();
    foreach ($orphaned_objects as $orphaned_object) {
      $pid = $orphaned_object['object']['value'];
      $rows[$pid] = array(l($orphaned_object['title']['value'], "islandora/object/$pid"));
    }
    $form['management_table'] = array(
      '#type' => 'tableselect',
      '#header' => array(t('Object')),
      '#options' => $rows,
      '#attributes' => array(),
      '#empty' => t('No orphaned objects were found.'),
    );
    if (!empty($rows)) {
      $form['submit_selected'] = array(
        '#type' => 'submit',
        '#name' => 'islandora-orphaned-objects-submit-selected',
        '#validate' => array('islandora_orphaned_objects_manage_delete_selected_validate'),
        '#submit' => array('islandora_orphaned_objects_manage_delete_submit'),
        '#value' => t('Delete Selected'),
      );
      $form['submit_all'] = array(
        '#type' => 'submit',
        '#name' => 'islandora-orphaned-objects-submit-all',
        '#submit' => array('islandora_orphaned_objects_manage_delete_submit'),
        '#value' => t('Delete All'),
      );
    }
  }
  return $form;
}

/**
 * Validation for the Islandora Orphaned Objects management form.
 *
 * @param array $form
 *   An array representing a form within Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_orphaned_objects_manage_delete_selected_validate($form, $form_state) {
  $selected = array_filter($form_state['values']['management_table']);
  if (empty($selected)) {
    form_error($form['management_table'], t('At least one object must be selected to delete!'));
  }
}

/**
 * Submit handler for the delete buttons in the workflow management form.
 *
 * @param array $form
 *   An array representing a form within Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_orphaned_objects_manage_delete_submit(&$form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'islandora-orphaned-objects-submit-selected') {
    $selected = array_keys(array_filter($form_state['values']['management_table']));
  }
  else {
    $selected = array_keys($form_state['values']['management_table']);
  }
  $form_state['pids_to_delete'] = $selected;
  // Rebuild to show the confirm form.
  $form_state['rebuild'] = TRUE;
  $form_state['show_confirm'] = TRUE;
}

/**
 * Submit handler for the workflow management confirm form.
 *
 * @param array $form
 *   An array representing a form within Drupal.
 * @param array $form_state
 *   An array containing the Drupal form state.
 */
function islandora_orphaned_objects_manage_confirm_submit($form, &$form_state) {
  module_load_include('inc', 'islandora_orphaned_objects', 'includes/batch');
  $batch = islandora_orphaned_objects_delete_create_batch($form_state['pids_to_delete']);
  batch_set($batch);
}
