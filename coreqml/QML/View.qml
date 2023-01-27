import QtQuick 2.0
import CoreQML 1.0

// View is a base component for full-screen views with
// assignable C++ viewController
Item {
    id: root

    x: 0
    y: 0
    width: parent ? parent.width : undefined
    height: parent ? parent.height : undefined

    // Emits when current view did became active. Could be used to configure view after creation.
    signal viewDidBecomeActive
    // Emits when current view did became inactive. Could be used to release retained resources.
    signal viewDidBecomeInactive

    // Holds reference to controller instance. Controller instance could hold some
    // usefull bindings with C++ code
    property var viewController: null
    // Holds reference to parent Stack component. See Stack.qml
    property var stack: null
    // View title
    property string title: viewController.params.title || ""
    // True if view is currently visible
    property bool active: false
    // View type. See possible types in ViewController.h
    property int type: ViewType.Generic
    // Specifies if current view fully opaque, or have some transparent areas
    property bool opaque: true
    // Specifies if current view is visually full screen
    property bool fullScreen: true

    onActiveChanged: {
        if ( active ) {
            viewDidBecomeActive()
            viewController.onViewDidBecomeActive()
        }
        else {
            viewDidBecomeInactive()
            viewController.onViewDidBecomeInactive()
        }
    }

    Component.onCompleted: {
        if ( viewController ) {
            viewController.onViewAttached( this )
        }
    }

    Component.onDestruction: {
        if ( viewController ) {
            viewController.onViewDetached()
        }
    }
}
