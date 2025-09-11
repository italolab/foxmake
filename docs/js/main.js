
$(document).ready( function() {
    $("#nav").load( "/cbuild/layout/nav.html" );
    $("#aside").load( "/cbuild/layout/aside.html" );
    $("#footer").load( "/cbuild/layout/footer.html" );
    $("#footer").load( "/cbuild/layout/footer.html" );

    $("body").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/cbuild/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );