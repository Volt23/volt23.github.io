
$(document).ready(function(){
    var $menu = $('.menu');
    $menu.click(function(){
        $('.menuscreen').fadeToggle();
        $('.logo2').fadeToggle();
    });
    
})

$(window).load(function(){
    var $container = $('.portfolioContainer');
    $container.isotope({
        itemSelector: '.grid-item',
        percentPosition: true,
        masonry: {
        columnWidth: '.masonry__column',
        gutter: '.masonry__gutter',
        }
    });

    $('.portfolioFilter a').click(function(){
        $('.portfolioFilter .current').removeClass('current');
        $(this).addClass('current');
        var selector = $(this).attr('data-filter');
        $container.isotope({
            filter: selector,
         });
         return false;
    }); 

});

