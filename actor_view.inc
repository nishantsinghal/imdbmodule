<?php
/**
 * @file
 * The Actor view inc file.
 * Developer-Nishant
 * Contains all function related to actor custom view.
 */

function actor_filter_form($form, &$form_state) {
  $form['category'] = array(
     '#type' => 'select',
     '#title' => t('Choose Category'), 
     '#options' => getCategory(),
     );
  $form['submit_button'] = array(
     '#type' => 'submit',
     '#value' => t('Apply'), 
    );
    return $form;
}

function actor_filter_form_submit($form, &$form_state) {
  $categoryid = $form_state['values']['category'];
  drupal_goto("examples/actors", array(
    'query' => array(
        'category' => $categoryid,
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

function actor_view($form) {
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ct_actor');

    $parameter = drupal_get_query_parameters();
    //dpm($parameter);

    if (isset($parameter['category']) && $parameter['category'] != "a") {
      $query->fieldCondition('field_ct_category', 'tid', $parameter['category']);
    }

    $result = $query->execute();
    $nodes = array();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
    }
    //print_r($nodes);
    $list = array();
    foreach ($nodes as $node) {
      $options = array('absolute' => TRUE);
      $url = url('node/' . $node->nid, $options);
      $list[] = '<a href=' . $url . '>' . $node->title . '</a>';
    }

    $theme_args = array('items' => $list, 'type' => 'ul');
    $content = theme('item_list', $theme_args);
    $view  = render(drupal_get_form($form));
    $view .= $content;
    return $view;
}