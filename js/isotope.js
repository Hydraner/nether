/**
 * Usage of isotope:
 *	- Add the "isotope" class to the view wich provides the content.
 *	- Optional add "isotope--filter" to a view wich provides filter functionallity.
 *		- When using filtering option, add the filter selector to the content view.
 *			For example filter--[tid] would be a good one.
 *		- The filter view needs to provide links using the following syntax:
 *			<a data-filter=".filter--[tid]" href="#">[name]</a>
 */
(function ($) {

	Drupal.behaviors.nether_isotope = {
	  attach: function (context, settings) {
			var $container = $('.isotope .view-content', context);
			// initialize isotope
			$container.isotope({
		  	itemSelector : '.views-row',
			});

			// filter items when filter link is clicked
			$('.isotope--filter a', context).click(function() {
			  var selector = $(this).attr('data-filter');
			  $container.isotope({ filter: selector });
			  return false;
			});

		}
	};

})(jQuery);
