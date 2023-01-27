import QtQuick 2.0
import CoreQML 1.0

QtObject {
    id: selector

    // in params
    property ButtonPalette paletteObject
    property string icon
    property string backgroundImage

    property bool pressedFlag
    property bool disabledFlag

    // out params
    property ButtonPaletteData palette: {
        if ( !paletteObject ) {
            return undefined
        }
        if ( pressedFlag ) {
            return paletteObject.pressed
        }
        if ( disabledFlag ) {
            return paletteObject.disabled
        }

        return paletteObject.normal
    }

    property url paletteIcon: paletteObject ? _findImageForState( icon ) : ""
    property url paletteBackgroundImage: paletteObject ? _findImageForState( backgroundImage ) : ""

    function _findImageForState( baseUrl ) {
        if( !baseUrl ) {
            return ""
        }

        var _withoutqrc = baseUrl.replace( "qrc:/", "" ) // replace doesn't change original string
        var _removeSuffixRegex = /.svg$|.png$|.jpg$/i;
        var _baseImageClear = _withoutqrc.replace( _removeSuffixRegex, "" )
        var _suffix = _withoutqrc.substring( _baseImageClear.length )
        var _base = "qrc:/" + _baseImageClear + _suffix
        var _normalImage = _findImage( [ _base, "qrc:/" + _baseImageClear + "_normal" + _suffix ] )

        if ( pressedFlag ) {
            return _findImage( [ "qrc:/" + _baseImageClear + "_pressed" + _suffix, _normalImage.toString() ] )
        }
        if ( disabledFlag ) {
            return _findImage( [ "qrc:/" + _baseImageClear + "_disabled" + _suffix, _normalImage.toString() ] )
        }

        return _normalImage
    }

    function _findImage( urls ) {
        for ( var i = 0; i < urls.length; ++i ) {
            if ( CApp.resourcesManager.isResourceValid( urls[ i ] ) ) {
                return urls[ i ]
            }
        }
        return ""
    }
}
