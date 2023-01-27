import QtQuick 2.0
import CoreQML 1.0

// Useful functions for scalable design accross different screen sizes and DPIs.
QtObject {
    id: screen

    readonly property real width: CApp.screen.screenSize.width
    readonly property real height: CApp.screen.screenSize.height
    readonly property real mdpi: 160
    readonly property real dpiX: CApp.screen.dpiX
    readonly property real dpiY: CApp.screen.dpiY
    readonly property real dpi: CApp.screen.dpi
    readonly property real hDPIRatio: dpiX / dpiY
    readonly property real vDPIRatio: dpiY / dpiX
    readonly property real uiSizeMultiplier: CApp.screen.uiSizeMultiplier
    readonly property real fontSizeMultiplier: CApp.screen.fontSizeMultiplier

    // Should be used in the most of the software.
    // It allows to make a scalable design
    function sp( spVal ) {
        return spVal * dpi / mdpi * uiSizeMultiplier
    }

    // sp aligned to nearest integer
    function isp( spVal ) {
        return Math.round( sp( spVal ) )
    }

    // Calibrated font size
    function fp( val ) {
        return fontSizeMultiplier * sp( val )
    }

    // Should be used in scale-independent controls s.t. ruler.
    // mm( 10 ) will return 10 millimeters-wide 'margin' for current screen
    function mm( dpVal ) {
        return dpVal * dpi / 25.4
    }
}
