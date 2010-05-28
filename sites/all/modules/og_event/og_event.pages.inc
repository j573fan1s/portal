<?php
// $Id: og_event.pages.inc,v 1.1.2.1 2009/10/20 14:41:12 pounard Exp $

/**
 * @file
 * OG Event user pages
 */

/**
 * Display an event participants list.
 * 
 * @param int $nid
 *   event node id
 */
function og_event_list_cb($node) {
  drupal_set_title(t('Participants for !event', array('!event' => check_plain($node->title))));
  return theme('og_event_participants_list', $node, og_event_get_participants_list($node));
}

/**
 * Register a user to an event.
 */
function og_event_register_page($node, $account = NULL) {
  if (og_event_is_role_enabled($node)) {
    return drupal_get_form('og_event_handle_role_form', $node);
  }
  else {
    // This does a drupal_goto() redirection, no need for return
    _og_event_handle_registration('register', $node, $account);
  }
}

/**
 * Unregister a user to an event form.
 */
function og_event_unregister_page($node, $account = NULL) {
  _og_event_handle_registration('unregister', $node, $account);
}

/**
 * Role registration form.
 * 
 * @param int $nid
 *   event on which add the user registration with role
 */
function og_event_handle_role_form($form_state, $node, $account = NULL) {
  // Does our node exists and is an event node ?
  if (! og_event_is_registration_enabled($node)) {
    drupal_not_found();
  }

  if (! $account) {
    global $user;
    $account = $user;
  }

  $form = array();
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
  );
  $form['role'] = array(
    '#type' => 'textfield',
    '#title' => t('Role'),
    '#description' => t('Enter here the role you want to assume for this event.<br/>Leave null if you are just a visitor.'),
    '#required' => FALSE,
  );
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Subscribe'),
  );

  return $form;
}

function og_event_handle_role_form_validate($form, &$form_state) {
  // Check user rights
}

function og_event_handle_role_form_submit($form, &$form_state) {
  _og_event_handle_registration('register', node_load($form_state['values']['nid']), NULL, $form_state['values']['role']);
}

/**
 * Handle user registration.
 * 
 * @param string $op
 *   'register' : add a user registration
 *   'unregister' : delete a user registration
 * @param int $node
 *   Node object
 * @param int $account = NULL (optional)
 *   New registrant account object
 * @param string $role = NULL
 *   Role to affect to user
 */
function _og_event_handle_registration($op = 'register', $node, $account = NULL, $role = NULL) {
  if (! $account) {
    global $user;
    $account = $user;
  }
  if ($op == 'register') {
    _og_event_register_user($node, $account, $role);
  }
  else if ($op == 'unregister') {
    _og_event_unregister_user($node, $account);
  }
  // Redirection
  if (variable_get(OG_EVENT_VIEW_REDIRECT_AFTER_SUBSCRIBE, FALSE)) {
    drupal_goto('node/' . $node->nid . '/participants');
  }
  else {
    drupal_goto('node/' . $node->nid);
  }
}

/**
 * Theme subscript message below the participant list
 */
function theme_og_event_subscribe_message($node) {
  global $user;
  if (og_event_user_can_register($node, $user)) {
    if (! og_event_is_user_registered($node, $user)) {
      return l(t('Subscribe to this event'), 'node/' . $node->nid . '/register-event');
    }
    else {
      return l(t('Unsubscribe to this event'), 'node/' . $node->nid . '/unregister-event');
    }
  }
  else {
    if (! og_event_is_registration_enabled($node)) {
      return t('This event is closed.');
    }
    else {
      return t('You must join this group to subscribe to the event.');
    }
  }
}

/**
 * Render participant list output
 * 
 * @param int nid
 *   node nid from which participant are given
 * @param array $participants
 *   array, keys are uid, data is role if there is one (or NULL value)
 * @param string $title = NULL (optional)
 *   if given, display this title on top of the participants list
 * @return string
 *   xhtml output
 */
function theme_og_event_participants_list($node, $participants = array(), $title = NULL) {
  $output = "";

  if (! empty($title)) {
    $output .= "<h3>" . $title . "</h3>";
  }

  if (empty($participants)) {
    $output .= "<p>" . t('There is no participants registered.') . "</p>";
    $output .= "<p>" . theme('og_event_subscribe_message', $node) . "</p>";
    return $output;
  }

  // Does our current user can edit the subscributions ?
  $user_can_edit = og_event_user_can_edit($node);
  $roles_enabled = og_event_is_role_enabled($node);

  // Table headers
  $headers = array(t('User'));
  if ($roles_enabled) {
    $headers[] = t('Role');
  }
  if ($user_can_edit) {
    $headers[] = t('Edit');
  }

  // Table content
  $rows = array();
  foreach ($participants as $uid => $role) {
    $user = user_load(array('uid' => $uid));
    $row_data = array(
      theme('username', $user)
    );
    if ($roles_enabled) {
      $row_data[] = check_plain($role);
    }
    if ($user_can_edit) {
      $row_data[] = l(t('unsubscribe'), 'node/' . $node->nid . '/unregister-event/'.$uid);
    }
    // Construct the real row
    $rows[] = array('data' => $row_data);
  }
  $output .= theme('table', $headers, $rows);

  $output .= "<p>" . theme('og_event_subscribe_message', $node) . "</p>";

  return $output;
}
