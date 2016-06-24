<?php
/**
 * @file
 * The Block view inc file.
 * Developer-Nishant
 * Contains all function related to block custom view.
 */
  function actor_block_view() {
    // Used for get current path url---------------------
    $path = current_path();
    // dpm($path);

    // Used for get current path's alias url-------------
    $p = drupal_get_path_alias($path);
    // dpm($p);

    // Used for split-----------------------------------
    $p_array = explode("/", $p);
    $path_array = explode("/", $path);
    // dpm($path_array);
    if ($path_array[0] == "actor" || $p_array[0] == "actor") {
    $p_path = drupal_get_normal_path($path);
    // dpm($p_path);
    $node = menu_get_object('node', 1, $p_path);
    // dpm($node);

    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'movies')
    ->fieldCondition('field_ct_actor', 'target_id', $node->nid);
    $result = $query->execute();
    $nodes = array();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
    //dpm($nodes);
    //print_r($nodes);

    $query1 = new EntityFieldQuery();
    $query1
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'songs');
    $movie = array();
    foreach ($nodes as $node) {
      //dpm($node->nid);
      $movie[] = $node->nid;
    }
      $query1->fieldCondition('field_movie', 'target_id', $movie);
    $result1 = $query1->execute();
    //dpm($result1);
    $nodes1 = array();
    if (isset($result1['node'])) {
      $nids1 = array_keys($result1['node']);
      $nodes1 = node_load_multiple($nids1);
    }
    //dpm($nodes1);

    $list = array();
    foreach ($nodes1 as $node) {
      //dpm($node->title);
      $path = 'node/' . $node->nid;
      $path_alias = drupal_get_path_alias($path);
      $song_link = l(t($node->title), $path_alias);
      $list[] .= $song_link;
    }

    $theme_args = array('items' => $list, 'type' => 'ul');
    $content = theme('item_list', $theme_args);
    
    return $content;
    }
  }

  function movie_block_view() {
    $path = current_path();
    //dpm($path);
    $p_path = drupal_get_normal_path($path);
    //dpm($p_path);
    $node = menu_get_object('node', 1, $p_path);
    //dpm($node);


    $query = new EntityFieldQuery();
    $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'songs')
    ->fieldCondition('field_movie', 'target_id', $node->nid);

    $result = $query->execute();
    $nodes = array();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
    //dpm($nodes);
    //print_r($nodes);
    $list = array();
    foreach ($nodes as $node) {
      dpm($node->title);
      $path = 'node/' . $node->nid;
      $path_alias = drupal_get_path_alias($path);
      $song_link = l(t($node->title), $path_alias);
      $list[] .= $song_link;
    }

    $theme_args = array('items' => $list, 'type' => 'ul');
    $content = theme('item_list', $theme_args);
    
    return $content;

  }