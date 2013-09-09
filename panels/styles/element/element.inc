<?php

/**
 * Impelements hook_element_panels_styles().
 */
function nether_element_panels_styles() {
  $plugin = array(
    'title' => t('Element pane style'),
    'render region' => 'panels_element_style_render_region',
    'settings form' => 'panels_element_style_region_settings_form',
    'render pane' => 'panels_element_style_render_pane',
    'pane settings form' => 'panels_element_style_settings_form',
    'hidden' => TRUE,
    'hook theme' => array(
      'panels_element' => array(
        'variables' => array(
          'content' => NULL,
          'settings' => NULL,
        ),
        'path' => drupal_get_path('theme', 'nether') .'/panels/styles/element',
        'template' => 'element-pane',
      ),
    )
  );
  return $plugin;
}

/**
 * Implementation of theme_panels_element_style_render_pane(). 
 *
 * Render callback for a single pane.
 */
function theme_panels_element_style_render_pane($vars) {
  $settings = $vars['settings'];
  $settings['headline-element'] = isset($settings['headline-element']) ? $settings['headline-element'] : 'h2';
  $container_element = (isset($settings['container-element']) && !empty($settings['container-element'])) ? $settings['container-element'] : FALSE;
  $settings['container-element'] = $container_element;
  $content = $vars['content'];
  $attributes = (isset($settings['attributes']) && !empty($settings['attributes'])) ? drupal_attributes($settings['attributes']) : '';
  $settings['attributes'] = $attributes;

  // When content is coming from theme_panel_pane().
  if(!isset($content->content)) {
    $content = new StdClass();
    $content->content = $vars['content'];
  }

  return theme('panels_element', array('content' => $content, 'settings' => $settings));
}

/**
 * Implementation of theme_panels_element_style_render_pane(). 
 *
 * Render callback for a single pane.
 */
function theme_panels_element_style_render_region($vars) {
  $settings = $vars['settings'];
  $container_element = (isset($settings['container-element']) && !empty($settings['container-element'])) ? $settings['container-element'] : FALSE;
  $attributes = (isset($settings['attributes']) && !empty($settings['attributes'])) ? drupal_attributes($settings['attributes']) : '';

  $output = '';
  if(!empty($container_element)) {
    $output .= '<' . $container_element . $attributes . '>' . implode('', $vars['panes']) . '</' . $container_element . '>';
  }
  else {
    $output .= implode('', $vars['panes']);
  }
  return $output;
}

/**
 * Implementation of panels_element_style_settings_form().
 */
function panels_element_style_settings_form($settings) {
  $form['headline-element'] = array(
    '#type' => 'select',
    '#title' => t('Headline element'),
    '#options' => fences_get_fences_options('field'),
    '#default_value' => (isset($settings['headline-element'])) ? $settings['headline-element'] : 'h2',
  );
  $form['container-element'] = array(
    '#type' => 'select',
    '#title' => t('Container element'),
    '#options' => fences_get_fences_options('field'),
    '#default_value' => (isset($settings['container-element'])) ? $settings['container-element'] : 'no_wrapper',
  );

  return $form;
}

function panels_element_style_region_settings_form($settings) {
  $form['container-element'] = array(
    '#type' => 'select',
    '#title' => t('Container element'),
    '#options' => fences_get_fences_options('field'),
    '#default_value' => (isset($settings['container-element'])) ? $settings['container-element'] : 'no_wrapper',
  );

  return $form;
}

/**
 * Overrides theme_panels_pane().
 */
function nether_panels_pane($vars) {
  return theme('panels_element_style_render_pane', $vars);
}

/**
 * Implements hook_ctools_plugin_pre_alter().
 *
 * Replace the default style plugin definitions with the element
 * style definitions, to get the element settings form on the
 * default style element.
 */
function nether_ctools_plugin_pre_alter(&$plugin, &$info) {
  if ($info['type'] == 'styles' && $plugin['name'] == 'default') {
    // dsm($plugin);
    $plugin = array(
      'title' => t('Element pane style'),
      'render region' => 'panels_element_style_render_region',
      'settings form' => 'panels_element_style_region_settings_form',
      'render pane' => 'panels_element_style_render_pane',
      'pane settings form' => 'panels_element_style_settings_form',
      'hook theme' => array(
        'panels_element' => array(
          'variables' => array(
            'content' => NULL,
            'settings' => NULL,
          ),
          'path' => drupal_get_path('theme', 'nether') . '/panels/styles/element',
          'template' => 'element-pane',
        ),
      ),
      'module' => 'nether',
      'name' => 'element',
      'path' => drupal_get_path('theme', 'nether') .'/panels/styles/element',
      'file' => 'element.inc',
      'plugin module' => 'panels',
      'plugin type' => 'styles',
    );
  }
}
