import QtQuick 2.0
import CoreQML 1.0

CoreStyle {
    id: root

    // Navigation bar style
    property var navigationBar: QtObject {
        property real height: App.screen.isp(64)
    }

    // Button style
    property var button: QtObject {
        property size defaultSize: Qt.size(App.screen.sp(200),
                                           App.screen.sp(64))
        property real fontSize: App.screen.fp(24)
        property real fontWeight: Font.Normal
        property real textMargins: App.screen.sp(2)
    }

    // Navigation Bar button
    property var navBarButton: QtObject {
        property int iconMarginInPercent: 25
    }

    // Buttons Dialog
    property var dialog: QtObject {
        property real fontSize: App.screen.fp(32)
        property bool useBoldFont: true
        property real borderWidth: 2
        property real buttonsSpacing: App.screen.isp(64)
        property real buttonsMargin: App.screen.isp(20)
    }

    // XKCD View
    property var xkcdView: QtObject {
        property int imageMargin: App.screen.isp(32)
        property int textBoxContentPadding: App.screen.isp(20)
        property int textBoxBorderWidth: App.screen.isp(3)
        property int textBoxBorderRadius: App.screen.isp(10)
        property int textBoxContentFontSize: App.screen.fp(24)
    }
}
