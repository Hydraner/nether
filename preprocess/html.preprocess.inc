<?php

/**
 * Implements template_preprocess_html().
 *
 * We need to redo the body class-sidebar thingy, because the default omega function
 * does not respect panel regions.
 */
function nether_preprocess_html(&$variables) {
  $classes = array('two-sidebars', 'one-sidebar', 'sidebar_first', 'sidebar_second', 'no-sidebars');

  // Remove previously set classes, because they don't respect panels.
  foreach($variables['classes_array'] as $delat => $class) {
    if(in_array($class, $classes)) {
      unset($variables['classes_array'][$delat]);
    }
  }

  if (omega_extension_enabled('development') && omega_theme_get_setting('omega_demo_regions', TRUE) && user_access('administer site configuration')) {
    // Get enabled panel regions, no matter if they are used or not.
    // 
    $config_regions = omega_theme_get_setting('omega_demo_regions_list', TRUE);
    $regions = array();
    foreach($config_regions as $region) {
      if(!empty($region)) {
        $regions[] = $region;
      }
    }
  }
  else {
    // Get used panel regions in non-debugging mode.
    $regions = array_keys($variables['page']['#handler']->conf['display']->panels); 
  }
  
  if (in_array('sidebar_first', $regions) && in_array('sidebar_second', $regions) || isset($config_regions)) {
    $variables['classes_array'][] = 'two-sidebars';
  }
  elseif (in_array('sidebar_first', $regions)) {
    $variables['classes_array'][] = 'one-sidebar sidebar-first';
  }
  elseif (in_array('sidebar_second', $regions)) {
    $variables['classes_array'][] = 'one-sidebar sidebar-second';
  }
  else {
    $variables['classes_array'][] = 'no-sidebars';
  }


  // Add better isotope support and load more functunallity.
  if(module_exists('isotope')) {
    drupal_add_js(drupal_get_path('theme', 'nether') . '/js/isotope.js');  
  }
  
}
