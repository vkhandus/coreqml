import QtQuick 2.0
import CoreQML 1.0

ApplicationWindow {
    id: root

    readonly property int cPaletteLight: 0
    readonly property int cPaletteDark: 1

    Component.onCompleted: {
        App.styleObjectURL = "qrc:/QML/ExampleStyle.qml"
        App.paletteManager.registerPaletteFile("qrc:/QML/PaletteLight.qml",
                                               cPaletteLight)
        App.paletteManager.registerPaletteFile("qrc:/QML/PaletteDark.qml",
                                               cPaletteDark)
        App.paletteManager.resetPalette(cPaletteDark)
    }
}
