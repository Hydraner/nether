<?php if(isset($content->content) && !empty($content->content)): ?>


	<?php if (!empty($settings['container-element'])): ?>
		<<?php print $settings['container-element']; ?> <?php print $settings['attributes']; ?>>
	<?php endif; ?>

		<?php if(isset($content->title) && !empty($content->title)): ?>
			<?php if (!empty($settings['headline-element'])): ?>
				<<?php print $settings['headline-element']; ?>>
			<?php endif; ?>
			<?php print render($content->title); ?>
			<?php if (!empty($settings['headline-element'])): ?>
				</<?php print $settings['headline-element']; ?>>
			<?php endif; ?>
		<?php endif; ?>

		<?php print render($content->content); ?>

	<?php if (!empty($settings['container-element'])): ?>	
		</<?php print $settings['container-element']; ?>>
	<?php endif; ?>	


<?php endif; ?>
