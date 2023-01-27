import QtQuick 2.0
import CoreQML 1.0

Palette {
    id: root

    // Basic colors
    readonly property color primaryDarkColor: "#1B2430"
    readonly property color primaryLightColor: "#B695A8"
    readonly property color primaryColor: "#51557E"
    readonly property color secondaryColor: "#816797"
    readonly property color primaryTextColor: "black"

    readonly property var navBar: QtObject {
        property color backgroundColor: primaryLightColor
        property color textColor: primaryTextColor
        property url homeIcn: "qrc:/res/home_light.svg"
        property url backIcn: "qrc:/res/back_light.svg"
        property url paletteIcn: "qrc:/res/palette_light.svg"
        property url xkcdIcn: "qrc:/res/xkcd_light.svg"
        property url reloadIcn: "qrc:/res/reload_light.svg"
    }

    property var iconButton: ButtonPalette {}

    property var navigationBarButton: ButtonPalette {
        normal {
            backgroundColor: "transparent"
        }

        pressed {
            backgroundColor: "transparent"
        }
    }

    // Dialog
    readonly property var dialog: QtObject {
        readonly property color backgroundColor: Qt.lighter(primaryLightColor)
        readonly property color borderColor: secondaryColor
        readonly property color textColor: primaryTextColor

        property var button: ButtonPalette {
            normal {
                backgroundColor: primaryLightColor
                textColor: root.primaryTextColor
            }

            pressed {
                backgroundColor: Qt.lighter(primaryLightColor, 1.2)
                textColor: root.primaryTextColor
            }
        }
    }

    // GameView
    readonly property var gameView: QtObject {
        readonly property color currentBrickColor: Qt.lighter("#7e4939")
        readonly property color placedBrickColor: "#7e4939"
        readonly property color brickBorderColor: primaryDarkColor
        readonly property color invisibleBrickColor: "transparent"
        readonly property color pausedOverlayColor: "pink"
        readonly property real pausedOverlayOpacity: 0.25
        readonly property url playIcn: "qrc:/res/play_btn_light.svg"
        readonly property url gameBackground: "qrc:/res/game_background_light.svg"
    }

    // XKCDView
    readonly property var xkcdView: QtObject {
        readonly property color backgroundColor: Qt.lighter(primaryLightColor)
        readonly property color textBorderColor: primaryDarkColor
        readonly property color textColor: primaryDarkColor
    }
}
