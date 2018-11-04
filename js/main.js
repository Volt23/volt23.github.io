
$(document).ready(function(){
     var $container = $('.portfolioContainer');
    $container.isotope({
        itemSelector: '.grid-item',
        masonry: {
        columnWidth: '.masonry__column',
        gutter: '.masonry__gutter',
        percentPosition: true,
        }
    });
    
})

