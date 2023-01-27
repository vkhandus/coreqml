import QtQuick 2.0
import CoreQML 1.0

// DialogController is a base component, which manages dialog data, and dialog view source.
// Controller is useful in many cases to reuse common dialog creation operations.
QtObject {
    id: root

    // signal fired when dialog are going to be dismissed.
    // use it to obtain result code
    signal finished( int code )

    // Holds component to use when create dialogView
    property url source: "qrc:/QML/DialogView.qml"
    // Holds dialogView ( Dialog ancestor)
    property var dialogView: null

    // Creates dialog and makes it active.
    function show() {
        App.dialogManager.showDialogCtrl( this )
    }

    // Dismisses dialogs with this controller
    function dismiss( code ) {
        App.dialogManager.dismissDialogCtrl( root, code )
    }
}
