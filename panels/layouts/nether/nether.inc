<?php
/**
 * @file
 * Registers Omega layouts as Panels layouts.
 *
 * We defenetly have to recheck all the variables, not sure if fubhy
 * catched them all (and right).
 */

/**
 * Implementation of hook_LAYOUT_panels_layouts()
 */
function nether_nether_panels_layouts() {
  // We cannot use the 'path' property here and anywhere in our layouts declared
  // in nether_panels_get_sublayouts() because panels uses it for both, the icon
  // and the include file in panels_theme() which we don't want. It's something
  // that works for things like 'flexible' layouts but not when the child plugin
  // mechanism is only used for an alternative discovery logic as in this
  // case.
  return array(
    'title' => t('Omega'),
    'category' => t('Omega page layouts'),
    'description' => t('nether page layouts for use as Panels Everywhere site templates.'),
    'get child' => 'nether_panels_get_sublayout',
    'get children' => 'nether_panels_get_sublayouts',
    'theme' => 'nether_panels',
    'admin theme' => 'nether_panels_admin',
    'regions' => array(),
  );
}

/**
 * Callback to provide a single nether layout.
 */
function nether_panels_get_sublayout($plugin, $layout, $sublayout) {
  $layouts = nether_panels_get_sublayouts($plugin, $layout);
  // dsm($layouts);
  if (isset($layouts["$layout:$sublayout"])) {
    return $layouts["$layout:$sublayout"];
  }
}

/**
 * Callback to provide all nether layouts.
 */
function nether_panels_get_sublayouts($plugin, $layout) {
  require_once drupal_get_path('theme', 'omega') . '/includes/omega.inc';
  // Fix layout preview width.
  drupal_add_css('.panels-layouts-checkboxes .form-checkboxes .form-item .layout-icon img { max-width: 100%; } }', 'inline');

  $layouts = array();
  if ($items = omega_layouts_info('omega')) {
    foreach ($items as $name => $info) {
      $layouts["$layout:$name"] = array(
        'name' => "$layout:$name",
        'title' => $info['info']['name'],
        'layout' => $info,
      ) + $plugin;

      // Panels calls the preview image 'icon'.
      // Panels is setting the icon path relative to the layouts directory.
      if (isset($info['info']['preview'])) {
        $layouts["$layout:$name"]['icon'] = '../../../../../../../' . $info['path'] . '/' . $info['info']['preview'];
      }

      // Various optional elements from the .info file of the layout.
      foreach (array('regions', 'category', 'description') as $key) {
        if (isset($info['info'][$key])) {
          $layouts["$layout:$name"][$key] = $info['info'][$key];
        }
      }
    }
  }
  return $layouts;
}

/**
 * Theme function for rendering a nether layout on the Panels admin UI.
 */
function theme_nether_panels_admin(&$variables) {
	drupal_process_attached(array('#attached' => $variables['layout']['layout']['attached']));

 	$variables['base_path']         = base_path();
  $variables['front_page']        = url();
  $variables['feed_icons']        = '';
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['logo']              = '';
  $variables['main_menu']         = '';
  $variables['secondary_menu']    = '';
  $variables['action_links']      = '';
  $variables['site_name']         = '';
  $variables['site_slogan']       = '';
  $variables['tabs']              = '';
  $variables['breadcrumb'] 				= '';
  $variables['title'] 						= '';
  $variables['messages']			 		= '';
	
  $variables['page'] = &$variables['content'];

  // Clean up the theme hook suggestion so we don't end up in an infinite loop.
  unset($variables['theme_hook_suggestion'], $variables['theme_hook_suggestions']);

  return theme($variables['layout']['layout']['template'], $variables);
}

/**
 * Theme function for rendering a nether layout.
 */
function theme_nether_panels(&$variables) {
  drupal_process_attached(array('#attached' => $variables['layout']['layout']['attached']));

  $variables['base_path']         = base_path();
  $variables['front_page']        = url();
  $variables['feed_icons']        = drupal_get_feeds();
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['logo']              = theme_get_setting('logo');
  $variables['main_menu']         = theme_get_setting('toggle_main_menu') ? menu_main_menu() : array();
  $variables['secondary_menu']    = theme_get_setting('toggle_secondary_menu') ? menu_secondary_menu() : array();
  $variables['action_links']      = menu_local_actions();
  $variables['site_name']         = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');
  $variables['site_slogan']       = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $variables['tabs']              = menu_local_tabs();
  $variables['tabs_primary']      = $vars['tabs'] = array(
                                      '#theme' => 'menu_local_tasks',
                                      '#primary' => menu_primary_local_tasks(),
                                    );
  $variables['tabs_secondary']    = $vars['tabs'] = array(
                                      '#theme' => 'menu_local_tasks',
                                      '#secondary' => menu_secondary_local_tasks(),
                                    );

  if ($node = menu_get_object()) {
    $variables['node'] = $node;
  }

  // Build the breadcrumb last, so as to increase the chance of being able to
  // re-use the cache of an already rendered menu containing the active link
  // for the current page.
  // @see menu_tree_page_data()
  $variables['breadcrumb'] = theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
  $variables['title'] = drupal_get_title();

  // Generate messages last in order to capture as many as possible for the
  // current page.
  $variables['messages'] = theme('status_messages');

  $variables['page'] = &$variables['content'];

  // Clean up the theme hook suggestion so we don't end up in an infinite loop.
  unset($variables['theme_hook_suggestion'], $variables['theme_hook_suggestions']);

  return theme($variables['layout']['layout']['template'], $variables);
}
