<?php

/**
 * @page
 * Override theme_() functions for the Descartes theme.
 */
// Overrides theme_breadcrumb()

function phptemplate_breadcrumb($breadcrumb) {
  if (empty($breadcrumb))
    return;
  
  $attr = array(
    'class' => 'breadcrumb-items'
  );
  $crumbs = theme('item_list', $breadcrumb, null, 'ul', $attr);
  return '<div class="breadcrumb">' . $crumbs . '</div>';
} 