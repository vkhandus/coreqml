import QtQuick 2.0
import CoreQML 1.0

QtObject {
    property ButtonPaletteData normal: ButtonPaletteData  {
        borderColor: "transparent"
        backgroundColor: "white"
        textColor: "black"
    }

    property ButtonPaletteData pressed: ButtonPaletteData {
        borderColor: "transparent"
        backgroundColor: "cyan"
        textColor: "black"
    }

    property ButtonPaletteData disabled: ButtonPaletteData  {
        borderColor: "transparent"
        backgroundColor: "white"
        textColor: "grey"
    }
}
