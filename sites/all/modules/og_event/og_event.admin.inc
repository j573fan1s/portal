<?php
// $Id: og_event.admin.inc,v 1.1.2.1 2009/10/20 14:41:12 pounard Exp $

/**
 * @file
 * OG Event administration pages
 */

function og_event_admin() {
  $form = array();
  $form['ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('UI settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default behavior'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // UI settings
  $form['ui'][OG_EVENT_VIEW_NODE_TAB] = array(
    '#type' => 'checkbox',
    '#title' => t('See participants tab on node view page'),
    '#default_value' => variable_get(OG_EVENT_VIEW_NODE_TAB, FALSE),
    '#description' => t('If you change this option, menu cache will be rebuilt'),
  );
  $form['ui'][OG_EVENT_VIEW_LIST_IN_CONTENT] = array(
    '#type' => 'checkbox',
    '#title' => t('See participants list in node content'),
    '#default_value' => variable_get(OG_EVENT_VIEW_LIST_IN_CONTENT, FALSE),
    '#description' => t('This setting disable the participant list tab'),
  );
  $form['ui'][OG_EVENT_VIEW_REDIRECT_AFTER_SUBSCRIBE] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect on participant list after subscribe'),
    '#default_value' => variable_get(OG_EVENT_VIEW_REDIRECT_AFTER_SUBSCRIBE, FALSE),
    '#description' => t('If unchecked, users will be redirect on full node view after subscribe/unsubscribe'),
  );
  // Default behavior settings
  $options = array(
    'og_event_open_reg' => t('Members can participate'),
    'og_event_open_edit' => t('Members can edit'),
    'og_event_open_role' => t('Participants can enter a role'),
  );
  $form['behavior'][OG_EVENT_DEFAULT_BEHAVIOR] = array(
    '#type' => 'checkboxes',
    '#title' => t('Default selected options for new event form'),
    '#options' => $options,
    '#default_value' => variable_get(OG_EVENT_DEFAULT_BEHAVIOR, NULL),
  );

  $form = system_settings_form($form);
  // Make sure that our callback is called before the variable_set() stuff
  array_unshift($form['#submit'], 'og_event_admin_submit_rebuild');
  return $form;
}

function og_event_admin_submit_rebuild($form, &$form_state) {
  $view_mode = $form_state['values'][OG_EVENT_VIEW_NODE_TAB];
  if (variable_get(OG_EVENT_VIEW_NODE_TAB, FALSE) != $view_mode) {
    menu_cache_clear_all();
    // menu_rebuild(); // TODO: Better ?
  }
}
