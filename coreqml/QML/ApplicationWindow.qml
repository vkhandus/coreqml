import QtQuick 2.0
import CoreQML 1.0

// Root visible Item of the QML application. Loads/resets application root view.
Item {
    id: appWindow

    width: App.screen.width
    height: App.screen.height

    property var _rootView: null

    function resetRootView( view, properties ) {
        var component;
        properties = typeof properties !== 'undefined' ? properties : {};
        if ( typeof( view ) === "string" ) { // View URI
            component = Qt.createComponent( view );
        }
        else {
            component = view;
        }

        if ( component.status === Component.Ready ) {
            if ( _rootView ) {
                _rootView.active = false
                _rootView.destroy()
            }

            _rootView = component.createObject( appWindow, properties );
            _rootView.active = true

            // Dynamically created view should be children of the rootView to properly handle
            // hardware keys by rootView
            App.dialogManager.parentView = _rootView
        }
        else {
            console.log( "Cannot create component for view, reason", component.errorString() );
        }

        return null;
    }

    Connections {
        target: cAppWindow
        function onRootViewControllerChanged() {
            resetRootView( cAppWindow.rootViewController.source.toString(), { viewController: cAppWindow.rootViewController } )
        }
    }

    Component.onDestruction: {
        // This will call viewDidBecomeInactive for active views.
        if ( _rootView )
        {
            _rootView.active = false
        }
    }
}
