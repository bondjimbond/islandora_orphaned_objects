<?php
/**
 * @file
 * Utility functions for use with the Islandora Orphaned Objects module.
 */

/**
 * Query for orphaned objects.
 *
 * @return array
 *   An array containing the results of the orphaned objects queries.
 */
function islandora_orphaned_objects_get_orphaned_objects() {
  $connection = islandora_get_tuque_connection();

// First query: get standard objects.
  $object_query = <<<EOQ
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

// Second query: get paged objects. Includes newspaper issues, book pages, newspaper pages.
  $paged_query = <<<EOQ
SELECT ?object ?book ?title
WHERE {
  ?object <fedora-model:hasModel> <info:fedora/fedora-system:FedoraObject-3.0> ;
             <fedora-rels-ext:isMemberOf> ?book .
  ?object <fedora-model:label> ?title;
  OPTIONAL {
    ?book <fedora-model:hasModel> ?model .
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

// Separate queries for different object types, due to different relationship types.
  $sparql_query_objects = format_string($object_query, array(
    '!optionals' => !empty($optionals) ? ('OPTIONAL {{' . implode('} UNION {', $optionals) . '}}') : '',
    '!filters' => !empty($filters) ? implode(' ', array_map($filter_map, $filters)) : '',
  ));
  $sparql_query_paged = format_string($paged_query, array(
    '!optionals' => !empty($optionals) ? ('OPTIONAL {{' . implode('} UNION {', $optionals) . '}}') : '',
    '!filters' => !empty($filters) ? implode(' ', array_map($filter_map, $filters)) : '',
  ));
  $object_results = $connection->repository->ri->sparqlQuery($sparql_query_objects);
  $paged_results = $connection->repository->ri->sparqlQuery($sparql_query_paged);

// Merge results of both queries into a single variable and return.
  $results = array_merge($object_results, $paged_results);
  return $results;
}
