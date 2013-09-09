<?php

/**
 * Implements template_preprocess_nether_panels().
 *
 * Add omega.development demo blocks feature to panels.
 */
function nether_preprocess_nether_panels(&$variables) {
  // Place dummy blocks in each region if the 'demo regions' setting is active
  // to force regions to be rendered.
  if (omega_extension_enabled('development') && omega_theme_get_setting ('omega_demo_regions', TRUE) && user_access('administer site configuration')) {
    $item = menu_get_item();

    // Don't interfere with the 'Demonstrate block regions' page.
    if (strpos('admin/structure/block/demo/', $item['path']) !== 0) {
      $regions = $variables['layout']['regions'];
      // TODO: Get regions from the selected layout.
      $configured = omega_theme_get_setting('omega_demo_regions_list', $variables['layout']['regions']);

      // Other then the omega version, this will support any layout region,
      // no matter if it's listed in the themes.info file or not.
      foreach (array_intersect_key($regions, array_flip($configured)) as $region => $name) {
        // If their is alrady contnet, we move it to #markup.
        if(!is_array($variables['content'][$region])) {
          $storage = $variables['content'][$region];
          unset($variables['content'][$region]);
          $variables['content'][$region]['#markup'] = $storage;
        }
        
        if (empty($page['layout'][$region])) {
          $variables['content'][$region]['#theme_wrappers'] = array('region');
          $variables['content'][$region]['#region'] = $region;
        }
        
        $variables['content'][$region]['#name'] = $name;
        $variables['content'][$region]['#debug'] = TRUE;
      }
    }
  }

}
