
$(document).ready( function() {
    $("#nav").load( "/docs/layout/nav.html" );
    $("#aside").load( "/docs/layout/aside.html" );
    $("#footer").load( "/docs/layout/footer.html" );
    $("#footer").load( "/docs/layout/footer.html" );

    $("body").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/docs/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );