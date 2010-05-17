<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?><?php if ($teaser) {print ' teaser'; } ?>">

<?php if($page == 0): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

<div class="submitted">
	<?php print $submitted ?>
</div>
  <div class="content clear-block">
    <?php print $content ?>
  </div>

<?php if($links OR $terms) { ?>
	<div class="node-links">
		<?php if ($terms) { ?>
			<div class="terms">
				<?php print t('filed under:  ') ?><?php print $terms ?>
			</div>
		<?php } ?>
		<?php print $links ?>
	</div>
<?php } ?>

</div>