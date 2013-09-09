<?php

/**
 * Implements template_preprocess_menu_link().
 */
function nether_preprocess_menu_link(&$variables) {
	if($variables['element']['#original_link']['menu_name'] != 'management') {
		$variables['element']['#attributes']['class'][] = 'menu--item';
		$variables['element']['#localized_options']['attributes']['class'][] = 'menu--item_link';
	}
}
