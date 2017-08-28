<?php
/**
 * @file
 * Batch functions for the Islandora Orphaned Objects module.
 */

/**
 * Constructs the batch that will go out and delete objects.
 *
 * @param array $pids
 *   The array of pids to be deleted.
 *
 * @return array
 *   An array detailing the batch that is about to be run.
 */
function islandora_orphaned_objects_delete_create_batch($pids) {
  // Set up a batch operation.
  $batch = array(
    'operations' => array(
      array('islandora_orphaned_objects_delete_batch_operation', array($pids)),
    ),
    'title' => t('Deleting the selected objects...'),
    'init_message' => t('Preparing to delete objects.'),
    'progress_message' => t('Time elapsed: @elapsed <br/>Estimated time remaining @estimate.'),
    'error_message' => t('An error has occurred.'),
    'finished' => 'islandora_orphaned_objects_delete_batch_finished',
    'file' => drupal_get_path('module', 'islandora_orphaned_objects') . '/includes/batch.inc',
  );
  return $batch;
}

/**
 * Constructs and performs the deleting batch operation.
 *
 * @param array $pids
 *   An array of pids to be deleted.
 * @param array $context
 *   The context of the Drupal batch.
 */
function islandora_orphaned_objects_delete_batch_operation($pids, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['pids'] = $pids;
    $context['sandbox']['total'] = count($pids);
    $context['results']['success'] = array();
  }

  if (!empty($context['sandbox']['pids'])) {
    $target_pid = array_pop($context['sandbox']['pids']);
    $target_object = islandora_object_load($target_pid);
    $context['message'] = t('Deleting @label (@pid) (@current of @total)...', array(
        '@label' => $target_object->label,
        '@pid' => $target_object->pid,
        '@current' => $context['sandbox']['progress'],
        '@total' => $context['sandbox']['total'],
    ));
    islandora_delete_object($target_object);
    $context['results']['success'][] = $target_pid;
    $context['sandbox']['progress']++;
  }
  $context['finished'] = ($context['sandbox']['total'] == 0) ? 1 : ($context['sandbox']['progress'] / $context['sandbox']['total']);
}

/**
 * Finished function for the orphaned objects delete batch.
 *
 * @param bool $success
 *   Whether the batch was successful or not.
 * @param array $results
 *   An array containing the results of the batch operations.
 * @param array $operations
 *   The operations array that was used in the batch.
 */
function islandora_orphaned_objects_delete_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results['success']), 'One object deleted.', '@count objects deleted.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}
