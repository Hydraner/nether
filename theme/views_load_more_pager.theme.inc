<?php

function nether_views_load_more_pager($vars) {
  global $pager_page_array, $pager_total;

  drupal_add_js(drupal_get_path('module', 'views_load_more') . '/views_load_more.js');
  drupal_add_js(drupal_get_path('theme', 'nether') . '/js/views_load_more.js');  

  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];

  $li_next = theme('pager_next',
    array(
      'text' => (isset($tags[3]) ? $tags[3] : t($vars['more_button_text'])),
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  if (empty($li_next)) {
    $li_next = "&nbsp;";
  }

  if ($pager_total[$element] > 1) {
    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );
    return theme('item_list',
      array(
        'items' => $items,
        'title' => NULL,
        'type' => 'ul',
        'attributes' => array('class' => array('pager', 'pager-load-more')),
      )
    );
  }
}
