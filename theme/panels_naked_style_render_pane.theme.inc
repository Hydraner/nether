<?php

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function nether_panels_naked_style_render_pane($vars) {
  return render($vars['content']->content);
}

