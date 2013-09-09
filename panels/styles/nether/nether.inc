<?php

/**
 * @file
 * Registers nether layouts as Panels layouts.
 */

/**
 * Implementation of hook_STYLE_panels_styles()
 */
function nether_nether_panels_styles() {
  return array(
    'hidden' => TRUE,
    'hook theme' => 'nether_panels_theme_registry_hack',
  );
}

/**
 * Slight hack that ensures that the nether layouts are always properly
 * registered so that they can be used in Panels backend UIs.
 */
function nether_panels_theme_registry_hack(&$theme, $data) {
  require_once drupal_get_path('theme', 'omega') . '/template.php';
  $theme = array_merge($theme, omega_theme());
}
