
$(document).ready( function() {
    $("#nav").load( "/layout/nav.html" );
    $("#aside").load( "/layout/aside.html" );
    $("#footer").load( "/layout/footer.html" );
    $("#footer").load( "/layout/footer.html" );

    $("body").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );