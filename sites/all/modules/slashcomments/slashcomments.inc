<?php
// $Id: slashcomments.inc,v 1.1 2009/09/10 12:47:49 mukhsim Exp $

function comment_render($node, $cid = 0) {
  global $user;

  $output = '';

  if (user_access('access comments')) {
    // Pre-process variables.
    $nid = $node->nid;
    if (empty($nid)) {
      $nid = 0;
    }

    $mode = _comment_get_display_setting('mode', $node);
    $order = _comment_get_display_setting('sort', $node);
    $comments_per_page = _comment_get_display_setting('comments_per_page', $node);

    if ($cid && is_numeric($cid)) {
      // Single comment view.
      $query = 'SELECT c.cid, c.pid, c.nid, c.subject, c.comment, c.format, c.timestamp, c.name, c.mail, c.homepage, u.uid, u.name AS registered_name, u.signature, u.picture, u.data, c.status FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid WHERE c.cid = %d';
      $query_args = array($cid);
      if (!user_access('administer comments')) {
        $query .= ' AND c.status = %d';
        $query_args[] = COMMENT_PUBLISHED;
      }

      $query = db_rewrite_sql($query, 'c', 'cid');
      $result = db_query($query, $query_args);

      if ($comment = db_fetch_object($result)) {
        $comment->name = $comment->uid ? $comment->registered_name : $comment->name;
        $links = module_invoke_all('link', 'comment', $comment, 1);
        drupal_alter('link', $links, $node);

        $output .= theme('comment_view', $comment, $node, $links);
      }
    }
    else {
      // Multiple comment view
      $query_count = 'SELECT COUNT(*) FROM {comments} WHERE nid = %d';
      $query = 'SELECT c.cid as cid, c.pid, c.nid, c.subject, c.comment, c.format, c.timestamp, c.name, c.mail, c.homepage, u.uid, u.name AS registered_name, u.signature, u.picture, u.data, c.thread, c.status FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid WHERE c.nid = %d';

      $query_args = array($nid);
      if (!user_access('administer comments')) {
        $query .= ' AND c.status = %d';
        $query_count .= ' AND status = %d';
        $query_args[] = COMMENT_PUBLISHED;
      }

      if ($mode == COMMENT_MODE_FLAT) {
        $query .= ' ORDER BY c.cid';
      }
      else {
        // See comment above. Analysis reveals that this doesn't cost too
        // much. It scales much much better than having the whole comment
        // structure.
        $query .= ' ORDER BY SUBSTRING(c.thread, 1, (LENGTH(c.thread) - 1))';
      }
      $query = db_rewrite_sql($query, 'c', 'cid');
      $query_count = db_rewrite_sql($query_count, 'c', 'cid');

      // Start a form, for use with comment control.
      $result = pager_query($query, $comments_per_page, 0, $query_count, $query_args);

      $divs = 0;
      $num_rows = FALSE;
      $comments = '';
      drupal_add_css(drupal_get_path('module', 'comment') .'/comment.css');
      while ($comment = db_fetch_object($result)) {
        $comment = drupal_unpack($comment);
        $comment->name = $comment->uid ? $comment->registered_name : $comment->name;
        $comment->depth = count(explode('.', $comment->thread)) - 1;

        if ($mode == COMMENT_MODE_THREADED) {
          if ($comment->depth > $divs) {
            $divs++;
            $comments .= '<div class="indented">';
          }
          else {
            while ($comment->depth < $divs) {
              $divs--;
              $comments .= '</div>';
            }
          }
        }

        if ($mode == COMMENT_MODE_FLAT) {
          $comments .= theme('comment_view', $comment, $node, module_invoke_all('link', 'comment', $comment, 0), FALSE);
        }
        else if ($mode == COMMENT_MODE_THREADED) {
          $comments .= theme('comment_view', $comment, $node, module_invoke_all('link', 'comment', $comment, 0), FALSE);
        }

        $num_rows = TRUE;
      }
      while ($divs-- > 0) {
        $comments .= '</div>';
      }

      $comment_controls = variable_get('comment_controls_'. $node->type, COMMENT_CONTROLS_HIDDEN);
      if ($num_rows && ($comment_controls == COMMENT_CONTROLS_ABOVE || $comment_controls == COMMENT_CONTROLS_ABOVE_BELOW)) {
        $output .= drupal_get_form('comment_controls', $mode, $order, $comments_per_page);
      }

      $output .= $comments;
      $output .= theme('pager', NULL, $comments_per_page, 0);

      if ($num_rows && ($comment_controls == COMMENT_CONTROLS_BELOW || $comment_controls == COMMENT_CONTROLS_ABOVE_BELOW)) {
        $output .= drupal_get_form('comment_controls', $mode, $order, $comments_per_page);
      }
    }

    // If enabled, show new comment form if it's not already being displayed.
    $reply = arg(0) == 'comment' && arg(1) == 'reply';
    if (user_access('post comments') && node_comment_mode($nid) == COMMENT_NODE_READ_WRITE && (variable_get('comment_form_location_'. $node->type, COMMENT_FORM_SEPARATE_PAGE) == COMMENT_FORM_BELOW) && !$reply) {
      $output .= comment_form_box(array('nid' => $nid), t('Post a comment:'));
    }

    $output = theme('comment_wrapper', $output, $node);
  }

  return $output;
}
