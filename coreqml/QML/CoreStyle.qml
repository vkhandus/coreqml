import QtQuick 2.0
import CoreQML 1.0

QtObject {
    id:root

    // Navigation bar style
    property var navigationBar: QtObject {
        property real height: App.screen.isp( 50 )
    }

    // Button style
    property var button: QtObject {
        property size defaultSize: Qt.size( App.screen.sp( 120 ), App.screen.sp( 50 ) )
        property real fontSize: App.screen.fp( 24 )
        property real fontWeight: Font.Normal
        property real textMargins: App.screen.sp( 2 )
    }
}
