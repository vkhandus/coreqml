import QtQuick 2.0
import CoreQML 1.0

View {
    id: root

    property var bricks: viewController.bricks
    property var currentBrick: viewController.currentBrick
    readonly property int cROWS: bricks.length
    readonly property int cCOLUMNS: bricks[0].length
    readonly property var cGamePalette: App.paletteManager.palette.gameView

    focus: true
    title: "Another brick!"

    // Navigate to another view
    property var navBarItems: Component {
        Button {
            height: parent.height
            width: height

            paletteSelector {
                paletteObject: App.paletteManager.palette.navigationBarButton
                icon: App.paletteManager.palette.navBar.xkcdIcn
            }

            iconMarginInPercents: App.style.navBarButton.iconMarginInPercent

            onClicked: {
                stack.pushView({
                                   "source": "qrc:/QML/XKCDView.qml"
                               })
            }
        }
    }

    Image {
        anchors.fill: parent
        source: cGamePalette.gameBackground
    }

    Grid {
        id: gameGrid
        anchors.fill: parent

        readonly property size itemSize: Qt.size(width / cCOLUMNS,
                                                 height / cROWS)

        columns: cCOLUMNS
        Repeater {
            model: cROWS * cCOLUMNS

            Rectangle {
                width: gameGrid.itemSize.width
                height: gameGrid.itemSize.height

                border.width: height / 20
                border.color: isCurrent
                              || isPlaced ? cGamePalette.brickBorderColor : "transparent"
                radius: height / 10

                property int c: model.index % cCOLUMNS
                property int r: model.index / cCOLUMNS
                property bool isCurrent: currentBrick.x === r
                                         && currentBrick.y === c
                property bool isPlaced: bricks[r][c] === true

                color: {
                    if (isCurrent) {
                        return cGamePalette.currentBrickColor
                    } else if (isPlaced) {
                        return cGamePalette.placedBrickColor
                    }

                    return cGamePalette.invisibleBrickColor
                }
            }
        }
    }

    // Paused overlay: semitransparent overlay with a play button
    Item {
        id: pausedOverlay
        anchors.fill: parent
        visible: viewController.isPaused

        Rectangle {
            anchors.fill: parent
            color: cGamePalette.pausedOverlayColor
            opacity: visible ? cGamePalette.pausedOverlayOpacity : 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 300
                }
            }
        }

        Image {
            anchors.centerIn: parent
            sourceSize.width: parent.height / 2
            sourceSize.height: parent.height / 2
            source: cGamePalette.playIcn

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    viewController.isPaused = false
                }
            }
        }
    }

    onActiveChanged: {
        if (!active) {
            viewController.isPaused = true
        }
    }

    Keys.onPressed: event => {
                        if (event.key === Qt.Key_Escape) {
                            viewController.isPaused = true
                        } else if (event.key === Qt.Key_Space) {
                            viewController.isPaused = !viewController.isPaused
                        } else {
                            viewController.moveBrick(event.key)
                        }
                        event.accepted = true
                    }
}
