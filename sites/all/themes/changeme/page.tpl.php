<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
<title><?php print $head_title ?></title>
<?php print $head ?>
<?php print $styles ?>
<?php print $scripts ?>
<script type="text/javascript"><?php /* Needed to avoid Flash of Unstyled Content in IE */ ?> </script>
<meta name="description" content="<?php print $site_name ?> |  <?php print $slogan ?>" />
</head>
		
<body class="<?php print $body_classes ?>">

<div id="wrapper">

	<div id="header-section" class="clear-block">
		  <div id="header-left">
		 	<?php if (!empty($logo)): ?>
		  		<div id="logo">
          	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo-link">
            	<img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          	</a>
       	 </div>
       	 <?php endif; ?>
		
			<div id="site-name">
				<?php print $site_name ?>
			</div>
		
			<?php if (!empty($site_slogan)): ?>
    		<div id="site-slogan"><?php print $site_slogan; ?></div>
   		<?php endif; ?>	
   	
   	</div>  <!-- End Header Left -->
   	
   	<div id="header-right">
   		<?php if (!empty($search_box)): ?>
        <div id="search-box"><?php print $search_box; ?></div>
    	<?php endif; ?>
		</div>  <!-- End Header right -->
		
		
			<div id="nav">
				<?php if (isset($primary_links)) : ?>
          			<?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
        		<?php endif; ?>
			</div>
	
	</div> <!--END HEADER SECTION-->
	
	
			<?php if (isset($secondary_links)) : ?>
         <div id="subnav">
          	<?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
       	</div>
       <?php endif; ?>




	<div id="content-region" class="clear-block">

		<?php if ($left) { ?>
      <div id="left-sidebar">
      		<?php print $left ?>
			</div> <!--END SIDEBAR-->
		<?php } ?>
				
		<div id="body-section">
			<?php print $tabs ?>
			<?php print $messages ?>
			<?php print $help ?>
			<?php if($title) { ?><h1><?php print $title ?></h1><?php } ?>
	 		<?php print $content ?>

		</div><!--END BODY SECTION-->
		
					
		<?php if ($right) { ?>
      		<div id="right-sidebar">
      			<?php print $right ?>
			</div> <!--END SIDEBAR-->
		<?php } ?>
	
	</div> <!-- end content-region -->
	
	
	<div id="footer">
 		<?php print $footer_message . $footer ?>
	</div> <!--END FOOTER-->


</div> <!-- End Wrapper -->


<?php print $closure ?>
</body>
</html>