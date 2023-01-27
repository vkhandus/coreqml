import QtQuick 2.0
import CoreQML 1.0
import "qrc:/Core/Utils.js" as PrivateUtils

// Base class for Button
Rectangle {
    id: button
    property alias paletteSelector: paletteSelector

    property string title: ""
    property alias titleFontSize: text.font.pixelSize
    property alias titleFontWeight: text.font.weight
    property alias titleFontItalic: text.font.italic

    property bool autosizeToBackground: false

    signal clicked()

    property bool pressed: false
    property bool disabled: false

    // Set one of following two options depending on required icon sizing behaviour
    property real iconMarginInPercents : 12.5
    property size iconSize: Qt.size( width - 2 * Math.min( height, width ) * iconMarginInPercents / 100,
                                     height - 2 * Math.min( height, width ) * iconMarginInPercents / 100 )
    property alias iconFillMode: iconImage.fillMode

    border.color: paletteSelector.palette.borderColor
    border.width: paletteSelector.backgroundImage ? 0 : 1

    color: paletteSelector.backgroundImage ? "transparent" : paletteSelector.palette.backgroundColor

    width: autosizeToBackground ? background.width : App.style.button.defaultSize.width
    height: autosizeToBackground ? background.height : App.style.button.defaultSize.height

    ButtonPaletteSelector {
        id: paletteSelector

        paletteObject: App.paletteManager.palette.iconButton
        pressedFlag: _mouseArea.pressed && !button.disabled
        disabledFlag: button.disabled
    }

    Image {
        id: background
        width: autosizeToBackground ? Image.width : parent.width
        height: autosizeToBackground ? Image.height : parent.height
        visible: PrivateUtils.isValidURL( paletteSelector.paletteBackgroundImage )

        sourceSize.height: !autosizeToBackground ? Math.ceil( parent.height ) : Image.height
        fillMode: Image.PreserveAspectFit

        source: paletteSelector.paletteBackgroundImage
    }

    Image {
        id: iconImage

        anchors.centerIn: parent
        width: Math.min( parent.width, implicitWidth )
        height: Math.min( parent.height, implicitHeight )

        sourceSize: iconSize
        visible: PrivateUtils.isValidURL( paletteSelector.paletteIcon )
        fillMode: Image.PreserveAspectFit
        source: paletteSelector.paletteIcon
    }

    Text {
        id: text

        anchors.margins: App.style.button.textMargins
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: App.style.button.fontSize
        font.weight: App.style.button.fontWeight
        color: paletteSelector.palette.textColor
        wrapMode: Text.WordWrap
        text: button.title
        elide: Text.ElideRight
    }

    MouseArea {
        id: _mouseArea
        anchors.fill: parent

        onClicked: {
            button.click()
        }
    }

    function click() {
        if ( !button.disabled ) {
            button.clicked()
        }
    }
}
