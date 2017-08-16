<?php
/**
 * @file
 * Utility functions for use with the Islandora Orphaned Objects module.
 */

/**
 * Query for orphaned objects.
 *
 * @return array
 *   An array containing the results of the orphaned objects query.
 */
function islandora_orphaned_objects_get_orphaned_objects() {
  $connection = islandora_get_tuque_connection();
  $query = <<<EOQ
SELECT ?object ?collection ?title
WHERE {
  ?object <fedora-model:hasModel> <info:fedora/fedora-system:FedoraObject-3.0> ;
               <fedora-rels-ext:isMemberOfCollection> ?collection .
  ?object <fedora-model:label> ?title;
  OPTIONAL {
    ?collection <fedora-model:hasModel> ?model .
  }
  FILTER(!bound(?model))
}
EOQ;
  $optionals = (array) module_invoke('islandora_xacml_api', 'islandora_basic_collection_get_query_optionals', 'view');
  $filter_modules = array(
    'islandora_xacml_api',
    'islandora',
  );
  $filters = array();
  foreach ($filter_modules as $module) {
    $filters = array_merge_recursive($filters, (array) module_invoke($module, 'islandora_basic_collection_get_query_filters', 'view'));
  }
  $filter_map = function ($filter) {
    return "FILTER($filter)";
  };
  $sparql_query = format_string($query, array(
    '!optionals' => !empty($optionals) ? ('OPTIONAL {{' . implode('} UNION {', $optionals) . '}}') : '',
    '!filters' => !empty($filters) ? implode(' ', array_map($filter_map, $filters)) : '',
  ));
  $results = $connection->repository->ri->sparqlQuery($sparql_query);
  return $results;
}
