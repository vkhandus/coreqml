import QtQuick 2.0
import CoreQML 1.0

Palette {
    id: root

    // Basic colors
    readonly property color primaryDarkColor: "#1B2430"
    readonly property color primaryLightColor: "#D6D5A8"
    readonly property color primaryColor: "#51557E"
    readonly property color secondaryColor: "#816797"
    readonly property color primaryTextColor: "white"

    readonly property var navBar: QtObject {
        property color backgroundColor: primaryDarkColor
        property color textColor: primaryTextColor
        property url homeIcn: "qrc:/res/home_dark.svg"
        property url backIcn: "qrc:/res/back_dark.svg"
        property url paletteIcn: "qrc:/res/palette_dark.svg"
        property url xkcdIcn: "qrc:/res/xkcd_dark.svg"
        property url reloadIcn: "qrc:/res/reload_dark.svg"
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
        readonly property color backgroundColor: primaryDarkColor
        readonly property color borderColor: primaryLightColor
        readonly property color textColor: primaryTextColor

        property var button: ButtonPalette {
            normal {
                backgroundColor: root.primaryColor
                textColor: root.primaryTextColor
            }

            pressed {
                backgroundColor: root.secondaryColor
                textColor: root.primaryTextColor
            }
        }
    }

    // GameView
    readonly property var gameView: QtObject {
        readonly property color currentBrickColor: Qt.lighter("#9e6959")
        readonly property color placedBrickColor: "#9e6959"
        readonly property color brickBorderColor: primaryDarkColor
        readonly property color invisibleBrickColor: "transparent"
        readonly property color pausedOverlayColor: "blue"
        readonly property real pausedOverlayOpacity: 0.25
        readonly property url playIcn: "qrc:/res/play_btn_dark.svg"
        readonly property url gameBackground: "qrc:/res/game_background_dark.svg"
    }

    // XKCDView
    readonly property var xkcdView: QtObject {
        readonly property color backgroundColor: secondaryColor
        readonly property color textBorderColor: "black"
        readonly property color textColor: "black"
    }
}
