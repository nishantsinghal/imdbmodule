<?php
/**
 * @file
 * The Movie view inc file.
 * Developer-Nishant
 * Contains all function related to Movie  custom view.
 */

function movie_filter_form($form, &$form_state) {
  $form['category'] = array(
     '#type' => 'select',
     '#title' => t('Choose Category'), 
     '#options' => getCategory(),
     );
   $form['movietype'] = array(
     '#type' => 'select',
     '#title' => t('Choose Movie type'), 
     '#options' => getMovietype(),
     );
   $form['actor'] = array(
     '#type' => 'select',
     '#title' => t('Choose Actor'), 
     '#options' => getActor(),
     );
  $form['submit_button'] = array(
     '#type' => 'submit',
     '#value' => t('Apply'), 
    );
    return $form;
} 

function movie_filter_form_submit($form, &$form_state) {
  $actorid = $form_state['values']['actor'];
  $categoryid = $form_state['values']['category'];
  $movietypeid = $form_state['values']['movietype'];
  drupal_goto("examples/movies", array(
    'query' => array(
        'actor' => $actorid,
        'category' => $categoryid,
        'movietype' => $movietypeid,
    ),
    ));

}

function getCategory() {
  $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', 'category');
    $result = $query->execute();
    $nodes = array();
    if (isset($result['taxonomy_term'])) {
      $nids = array_keys($result['taxonomy_term']);
      $nodes = taxonomy_term_load_multiple($nids);
    }
    $list = array();
    $list["a"] = "None";
    //dpm($nodes);
    foreach ($nodes as $node) {
      $list[$node->tid] = $node->name;
    }
    //dpm($list);
    return $list;
}

function getMovietype() {
  $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', 'movie_type');
    $result = $query->execute();
    $nodes = array();
    if (isset($result['taxonomy_term'])) {
      $nids = array_keys($result['taxonomy_term']);
      $nodes = taxonomy_term_load_multiple($nids);
    }
    $list = array();
    $list["a"] = "None";
    //dpm($nodes);
    foreach ($nodes as $node) {
      $list[$node->tid] = $node->name;
    }
    //dpm($list);
    return $list;
}

function getActor() {
  $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ct_actor');
    $result = $query->execute();
    $nodes = array();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
    $list = array();
    $list["a"] = "None";
    //dpm($nodes);
    foreach ($nodes as $node) {
      $list[$node->nid] = $node->title;
    }
    //dpm($list);
    return $list;
}


function movie_view($form) {
  $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'movies');
    
    $parameter = drupal_get_query_parameters();
    //dpm($parameter);

    if (isset($parameter['actor']) && $parameter['actor'] != "a") {
      $query->fieldCondition('field_ct_actor', 'target_id', $parameter['actor']);
    }
    if (isset($parameter['category']) && $parameter['category'] != "a") {
      $query->fieldCondition('field_ct_category', 'tid', $parameter['category']);
    }
    if (isset($parameter['movietype']) && $parameter['movietype'] != "a") {
      $query->fieldCondition('field_ct_movie_type', 'tid', $parameter['movietype']);
    }
    // if ($_)


    $result = $query->execute();
    //dpm($result);
    
    $nodes = array();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
    //print_r($nodes[10]);
    //$parameter = drupal_get_query_parameters();
    //dpm($parameter);
    $list = array();
    $i = 0;
    foreach ($nodes as $node) {
    //dpm($node);
    
    $items = field_get_items('node', $node, 'field_ct_actor');
    
    //print_r($items);
    //print_r($actor_node->title);
    //$options = array('absolute' => TRUE);
    $path = 'node/' . $node->nid;
    $path_alias = drupal_get_path_alias($path);
    $movie_link = l(t($node->title), $path_alias);
    $list[$i] = $movie_link . '<br><p>Star Cast : ';
    foreach ($items as $it) {
      $item = array_shift($it);
      $value = $item;
      //print_r($item);
      $actor_node = node_load($value);
      //$actor_url = url('node/' . $actor_node->nid);
      $path = 'node/' . $actor_node->nid;
      $path_alias = drupal_get_path_alias($path);
      $actor_link = l(t($actor_node->title), $path_alias);
      $list[$i] .= $actor_link . '&nbsp;&nbsp;&nbsp;&nbsp;';
    // $path = 'node/'. $node->nid;
    // $path_alias = drupal_get_path_alias($path);
    // $movie_link = l(t($node->title),$path_alias);
    // dpm($movie_link);
    //$actor_link = l(t($actor_node->title),'/node/'. $actor_node->nid);
    //$list[] = $movie_link.'<br><p>Star Cast: '.$actor_link.'</p>';
    }
    $list[$i] .= '</p>';
    $i++;
  } 
    $theme_args = array('items' => $list, 'type' => 'ul');
    $content = theme('item_list', $theme_args);

    $view  = render(drupal_get_form($form));
    $view .= $content;
    return $view;

}