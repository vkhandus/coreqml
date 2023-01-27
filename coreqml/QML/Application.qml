pragma Singleton
import QtQuick 2.2
import "qrc:/Core/Utils.js" as PrivateUtils

// Provides access to the basic components of the fore QML application
QtObject {
    id: root

    property string styleObjectURL: "qrc:/Core/CoreStyle.qml"
    readonly property var style: PrivateUtils.createQMLObject( styleObjectURL, root )
    readonly property var screen: PrivateUtils.createQMLObject( "qrc:/Core/AppScreen.qml", root )
    readonly property var paletteManager: PrivateUtils.createQMLObject( "qrc:/Core/PaletteManager.qml", root )
    readonly property var dialogManager: PrivateUtils.createQMLObject( "qrc:/Core/DialogManager.qml", root )
}
