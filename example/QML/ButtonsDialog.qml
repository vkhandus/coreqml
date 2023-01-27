import QtQuick 2.1
import CoreQML 1.0

DialogView {
    id: root

    readonly property var cDialogPalette: App.paletteManager.palette.dialog

    Rectangle {
        anchors.centerIn: parent
        width: root.width / 2
        height: root.height / 2

        color: cDialogPalette.backgroundColor
        radius: height / 20

        border {
            width: App.style.dialog.borderWidth
            color: cDialogPalette.borderColor
        }

        Item {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: buttons.top
            }

            Text {
                anchors.centerIn: parent
                color: cDialogPalette.textColor

                font.pixelSize: App.style.dialog.fontSize
                font.bold: App.style.dialog.useBoldFont
                text: controller.text
            }
        }

        MouseArea {
            // consume mouse events
            anchors.fill: parent
        }

        Row {
            id: buttons

            height: childrenRect.height
            spacing: App.style.dialog.buttonsSpacing
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
                margins: App.style.dialog.buttonsMargin
            }

            Repeater {
                model: controller.buttons

                Button {
                    title: modelData.title
                    radius: height / 5
                    paletteSelector.paletteObject: cDialogPalette.button

                    onClicked: {
                        root.finished(modelData.id)
                    }
                }
            }
        }
    }
}
