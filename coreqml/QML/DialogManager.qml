import QtQuick 2.0
import CoreQML 1.0

// Dialog manager used to create, manage and destroy dialogs
QtObject {
    id: root

    // This property holds the view, which would be passed as parrent to created dialogs
    // Should be initialized by owner Item.
    property var parentView: null
    // Stack of active dialogs.
    // Do not change this property outside of this item!
    property var activeDialogs: []

    /*!
     * Returns number of active dialogs
     */
    function numberOfActiveDialogs() {
        return activeDialogs.length
    }

    /*!
     *  Shows modal dialog
     *  Parameters:
     *      dialog: component id or URL of a dialog
     *      parameters: additionalProperties
     */
    function showDialog( dialog, properties ) {
        var component;
        properties = typeof properties !== 'undefined' ? properties : {};
        if ( typeof( dialog ) === "string" ) { // Dialog URI
            component = Qt.createComponent( dialog );
        }
        else {
            component = dialog;
        }

        if ( component.status === Component.Ready ) {
            var dialogView = component.createObject( parentView, properties );
            return _showDialogView( dialogView );
        }
        else {
            console.log( "Cannot create component for dialog, reason", component.errorString() );
        }

        return null;
    }

    /*!
     *  Shows modal dialog using dialogCtrl ( ancestor of BaseDialogCtrl )
     */
    function showDialogCtrl( dialogCtrl ) {
        var dialogView = showDialog( dialogCtrl.source.toString(), { controller: dialogCtrl } )
        if ( dialogView !== null ) {
            dialogView.finished.connect( dialogCtrl.finished )
        }
        return dialogView
    }

    /*!
     *  Dismiss modal dialog using dialogCtrl
     */
    function dismissDialogCtrl( dialogCtrl, result ) {
        // Calling finished() signal removes dialog from activeDialogs array, so save target dialogs to tmp variable first
        var dialogWithCtrl = activeDialogs.filter( function( dialogView ) { return dialogView.controller === dialogCtrl } )
        for ( var i = 0; i < dialogWithCtrl.length; ++i ) {
            dialogWithCtrl[ i ].finished( result )
        }
    }

    /*!
     *  Returns false and do nothing, if there are dialogs in current dialog stack that could not be dismissed explicitly.
     *  ( have enableExplicitRejection set to false ). Otherwise dismiss all dialogs with DIALOG_CANCELLED code.
     */
    function dismissAllDialogs( onlyBelongToCurrentView ) {
        for ( var i = activeDialogs.length - 1; i >= 0; --i ) {
            if ( !activeDialogs[ i ].enableExplicitRejection ) {
                return false
            }
            else if ( !onlyBelongToCurrentView || activeDialogs[ i ].belongToCurrentView ) {
                var dialog = activeDialogs[ i ]
                dialog.finished( dialog.cDIALOG_DISMISSED )
            }
        }

        return true
    }

    /*!
     *  Shows modal dialog view. This method shold not be used directly
     */
    function _showDialogView( dialogView ) {
        dialogView.finished.connect( function( code ) {
            dialogView.active = false
            dialogView.enabled = false
            dialogView.destroy()
            activeDialogs.splice( activeDialogs.indexOf( dialogView ), 1 )

            if ( activeDialogs.length ) {
                activeDialogs[ activeDialogs.length - 1 ].active = true
            }
        } )

        if ( activeDialogs.length ) {
            activeDialogs[ activeDialogs.length - 1 ].active = false
        }

        activeDialogs.push( dialogView )
        dialogView.active = true

        return dialogView;
    }

    Component.onCompleted: {
        CApp.dialogManager.initialize( this )
    }

    Component.onDestruction: {
        CApp.dialogManager.deinitialize()
    }
}
