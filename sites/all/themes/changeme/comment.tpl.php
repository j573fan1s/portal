<?php
// $Id: comment.tpl.php,v 1.1 2009/09/10 12:47:49 mukhsim Exp $

/**
 * @file comment.tpl.php
 * Default theme implementation for comments.
 *
 * Available variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: Body of the post.
 * - $date: Date and time of posting.
 * - $links: Various operational links.
 * - $new: New comment marker.
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *   comment-unpublished, comment-published or comment-review.
 * - $submitted: By line with date and time.
 * - $title: Linked title.
 *
 * These two variables are provided for context.
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * @see template_preprocess_comment()
 * @see theme_comment()
 */
?>

<?php 
  if (!$comment->name) {
    $comment->name = t('Anonymous');
  }
  
  $threshold = _slashcomments_get_display_setting('threshold', $node);
  $threshold = $threshold ? $threshold : 0;
  $collapsed = ($comment->score >= $threshold) ? '' : 'collapsed' ;
  $toggle_label = ($comment->score >= $threshold) ? 'non_toggle_label' : 'toggle_label' ;
  $toggle_label .= ' ' . $comment->own;
  $toggle_area = ($comment->score >= $threshold) ? 'non_toggle_area' : 'toggle_area' ;
  $toggle_area .= ' ' . $comment->own;

?>

<div class="<?php print $toggle_area ?>">
    <div  class="<?php print $toggle_label ?>" style="float: right; text-align: right"><b><?php print '#' . $comment->cid; ?></b></div>
    <div class="<?php print $toggle_label ?>">
      <span class="comment-name"><?php print $comment->name ?>.</span>
      <?php //print $comment->subject ?>
      <b><?php print $comment->rating ?></b>;
      <?php print $date ?>;
      <?php print $comment->subject ?>
      <?php if ($new != '') { ?><span class="new"><?php print $new; ?></span><?php } ?>       
  </div>
  
  <div class="toggle_content <?php if (arg(0) != 'comment'): print $collapsed; endif; ?>">
    <div class="author">
    <?php if ($picture) {
    print $picture;
    } ?>
    <?php print $author ?>
    </div>  

    <div class="comment-content">
     <?php print $content; ?>
      <div class="clear clear-block"></div>     
      <div class="meta">
        <div class="links"><?php print $links; ?></div>
      </div>
      <?php if ($signature): ?><div class="user-signature"><?php print $signature ?></div><?php endif; ?>
    </div>
    
  </div>
</div>
