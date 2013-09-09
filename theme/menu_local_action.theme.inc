<?php

/**
 * Implements theme_menu_local_action().
 *
 * We aresplitting up the given link to catch queries we use to prepopulate
 * entityreferences. If we don't do this, l is going to convert "=" and "?" to
 * safe characters.
 */
function nether_menu_local_action($variables) {
  $link = $variables['element']['#link'];

  $output = '<li>';
  if (isset($link['href'])) {
    $explode = explode('?', $link['href']);
    if(isset($explode[1])) {
    	list($url, $querys) = explode('?', $link['href']);
    	list($argument, $value) = explode('=', $querys);
      $output .= l($link['title'], $url, array(
      	'query' => array($argument => $value),
      	'attributes' => isset($link['localized_options']['attributes']) ? $link['localized_options']['attributes'] : array(),
  		));
    }
    else {
      $output .= l($link['title'], $link['href'], array(
        'attributes' => isset($link['localized_options']['attributes']) ? $link['localized_options']['attributes'] : array(),
      ));
    }
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }
  $output .= "</li>\n";

  return $output;
}
