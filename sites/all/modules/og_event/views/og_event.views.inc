<?php
// $Id: og_event.views.inc,v 1.1.2.1 2009/10/20 15:55:36 pounard Exp $

/**
 * @file
 * OG Event views module integration
 */

/**
 * Implementation of hook_views_data().
 */
function og_event_views_data() {
  $data = array();

  // OG Event main table

  $data['og_event_node'] = array();
  $data['og_event_node']['table'] = array(
    'group' => t('OG Event'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field'      => 'nid',
        'type'       => 'INNER',
      ),
    ),
  );

  $data['og_event_node']['nid'] = array(
    'title' => t('Node is an event node'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE),
    // This could be usefull to require the JOIN
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node')),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_boolean_operator'),
  );

  $data['og_event_node']['open_reg'] = array(
    'title' => t('Group members can subscribe'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_boolean_operator'),
  );
  $data['og_event_node']['open_edit'] = array(
    'title' => t('Group members can edit'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_boolean_operator'),
  );
  $data['og_event_node']['open_role'] = array(
    'title' => t('Group members can input a role'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_boolean_operator'),
  );

  // Participants table

  $data['og_event_participant'] = array();
  $data['og_event_participant']['table'] = array(
    'group' => t('OG Event'),
    'base' => array(
      'field' => 'uid',
      'title' => t('OG Event participants'),
      'help' => t("This table can use user fields with relationships."),
      'weight' => -10,
    ),
    'join' => array(
      'og_event_node' => array(
        'left_field' => 'nid',
        'field'      => 'nid',
        'type'       => 'INNER'
      ),
      'users' => array(
        'left_field' => 'uid',
        'field'      => 'uid',
        'type'       => 'INNER'
      ,)
    ),
  );

  // No need to put users fields here, because linked with user table will give
  // the user all he wants through the natural join.

  $data['og_event_participant']['nid'] = array(
    'title' => t('Event node NID'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_node'),
    // Because og_event_node is not a base table, we have to link to node table
    // to avoid relationships handler errors
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Event node')
    ),
    'argument' => array('handler' => 'views_handler_argument_node_nid'),
  );
  $data['og_event_participant']['uid'] = array(
    'title' => t('Participant UID'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_user'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
    ),
    'argument' => array('handler' => 'views_handler_argument_user_uid'),
  );
  $data['og_event_participant']['role'] = array(
    'title' => t('Participant role'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_string'),
  );

  return $data;
}
