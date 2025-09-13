
$(document).ready( function() {
    $("#nav").load( "/foxmake/layout/nav.html" );
    $("#aside").load( "/foxmake/layout/aside.html" );
    $("#footer").load( "/foxmake/layout/footer.html" );
    $("#footer").load( "/foxmake/layout/footer.html" );

    $("body").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/foxmake/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );