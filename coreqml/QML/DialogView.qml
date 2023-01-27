import QtQuick 2.0
import CoreQML 1.0

// Dialog is a base component for dialogs.
Item {
    id: root

    // When QML engine is shutting down, 'root' may be null, and this line without checking for correctness of 'root' could produce warning.
    anchors.fill: root ? parent : undefined

    // signal fired when dialog are going to be dismissed.
    // use it to obtain result code
    signal finished( int code )

    // If enabled, dialog will skip touches delivered in first 1 second after showing dialog to avoid accidental rejection of the dialog
    property bool enableAccidentalRejection: true
    // If disabled - dialog will not be dismissed if user taps outside the dialog or press cancel key.
    property bool enableExplicitRejection: true
    // If true, dialog will be rejected when current view is closed
    property bool belongToCurrentView: true
    // This property holds dialog controller. See DialogController Item.
    property var controller: null
    // This property holds dialog state. Active Dialog are the most top visible dialog.
    property bool active: false
    // enables background shading effect
    property bool enableShading: true

    property alias rejectionArea: rejectionArea

    visible: active

    onActiveChanged: {
        if ( active ) {
            root.visible = true
            background.opacity = 0.5
        }
        else {
            background.opacity = 0
            root.visible = false
        }
    }

    onControllerChanged: {
        if ( controller !== null && controller.hasOwnProperty( "dialogView" ) ) {
            controller.dialogView = this
        }
    }

    function rejectByUserEvent() {
        if ( !enableExplicitRejection ) {
            return
        }

        if ( !enableAccidentalRejection || ( enableAccidentalRejection && !rejectionArea.accidentalRejectionGuardActive ) )
        {
            root.finished( Dialog.Rejected )
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent

        visible: enableShading
        color: "black"
        opacity: 0

        Behavior on opacity { NumberAnimation{ duration: 200 } }
    }

    MouseArea {
        id: rejectionArea
        anchors.fill: parent

        property bool accidentalRejectionGuardActive: true

        onClicked: {
            rejectByUserEvent()
        }

        Timer {
            interval: 500
            running: enableAccidentalRejection
            onTriggered: parent.accidentalRejectionGuardActive = false
        }
    }
}
