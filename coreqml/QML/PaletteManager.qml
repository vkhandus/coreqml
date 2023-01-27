import QtQuick 2.0
import CoreQML 1.0

// Manages dynamic palette change
QtObject {
    id: root

    property var palette : null
    readonly property int paletteMode : CApp.paletteManager.paletteMode
    property var _palettes: []

    function resetPalette( mode ) {
        CApp.paletteManager.paletteMode = mode
    }

    function registerPaletteFile( paletteUrl, mode ) {
        _palettes[ mode ] = paletteUrl
    }

    Component.onCompleted: {
        // register default palette
        registerPaletteFile( "qrc:/Core/Palette.qml", -1 )
        resetPalette( CApp.paletteManager.paletteMode )
    }

    property Connections myConnections: Connections {
        target: CApp.paletteManager
        function onPaletteModeChanged( mode ) {
            var oldPalette = palette

            if ( _palettes[ mode ] )
            {
                var component = Qt.createComponent( _palettes[ mode ] )
                if ( component.status === Component.Ready ) {
                    palette = component.createObject( root )
                    if ( oldPalette !== null ) {
                        oldPalette.destroy()
                    }
                }
                else {
                    console.log( "Error loading component:", component.errorString() )
                }
            }
        }
    }
}
