import QtQuick 2.0
import CoreQML 1.0

// Stack is a view, which holds stacked Views elements,
// and allow to switch between them using push/pop API
View {
    id: stack

    // return topmost View of this Stack
    property alias currentItem: stackView.currentItem
    property alias depth: stackView.depth
    readonly property alias views: stackView._views
    readonly property alias navigationBar: _navigationBar

    // Stack type. See possible types in ViewController.h
    type: ViewType.Stack

    onActiveChanged: {
        if ( stackView.currentItem ) {
            stackView.currentItem.active = active
        }
    }

    // Sets new root view fore Stack
    function resetRootView( item ) {
        return viewController.resetRootView( item ).view
    }

    // Pushs one View to Stack and make it active
    function pushView( item ) {
        return viewController.pushView( item ).view
    }

    // Pops one View from Stack
    function popView() {
        viewController.popView()
    }

    // Pops to root view of this Stack
    function popToRootView() {
        viewController.popToRootView()
    }

    // Pops views until predicate returns false
    function popViewsUntil( pred ) {
        while ( pred( currentItem ) ) {
            viewController.popView()
        }
    }

    function syncViewsAndControllers() {
        // 0. Put controllers to array
        var controllers = []
        for ( var i = 0; i < viewController.viewControllers.length; i++ ) {
            controllers.push( viewController.viewControllers[ i ] )
        }

        var controllersWithViews = []

        // 1. Remove all views without a controller
        for ( i = stackView._views.length - 1; i >= 0; i-- ) {
            var view = stackView._views[ i ];
            var ind = controllers.indexOf( view.viewController )
            if ( ind === -1 ) {
                view.active = false
                view.visible = false
                view.enabled = false
                view.destroy()
                stackView._views.splice( i, 1 )
            }
            else {
                controllersWithViews.push( controllers[ ind ] )
            }
        }

        // 2. Create view for each controllers without a view
        for ( i = 0; i < controllers.length; i++ ) {
            var ctrl = controllers[ i ]
            if ( controllersWithViews.indexOf( controllers[ i ] ) === -1 ) {
                var component = Qt.createComponent( ctrl.source )
                if ( component.status === Component.Ready ) {
                    var newPage = component.createObject( stackView, {
                                                             viewController: ctrl,
                                                             stack: stack,
                                                             visible: false } )
                    if ( !newPage ) {
                        console.log( component.errorString() )
                    }
                    else {
                        stackView._views.splice( i, 0, newPage )
                    }
                }
                else {
                    console.log( component.errorString() )
                }
            }
        }

        filterVisibleViews()

        stackView._viewsChanged()
    }

    function filterVisibleViews(predicate) {
        var invisibleViews = []
        var visibleViews = []
        if ( predicate ) {
            for ( var i = 0; i < stackView._views.length; ++i ) {
                if ( predicate( i, stackView._views[ i ] ) ) {
                    visibleViews.push( stackView._views[ i ] )
                } else {
                    invisibleViews.push( stackView._views[ i ] )
                }
            }
        } else {
            visibleViews = stackView._views
        }

        for ( i = 0; i < invisibleViews.length; ++i ) {
            invisibleViews[ i ].active = false
            invisibleViews[ i ].visible = false
            invisibleViews[ i ].enabled = false
        }

        // Check visible and active flags. Leave views at the bottom layer visible, if views from the top layer are not opaque
        var view
        var isPreviousViewsOpaque = visibleViews.length > 0 ? visibleViews[ visibleViews.length - 1 ].opaque : true
        for ( i = visibleViews.length - 2; i >= 0; --i ) {
            view = visibleViews[ i ]
            view.active = false
            view.visible = !isPreviousViewsOpaque && view.fullScreen
            view.enabled = !isPreviousViewsOpaque && view.fullScreen
            isPreviousViewsOpaque = isPreviousViewsOpaque || view.opaque
        }

        // Make top visible view active
        if ( visibleViews.length > 0 ) {
            view = visibleViews[ visibleViews.length - 1 ]
            view.visible = true
            view.enabled = true
            stackView.currentItem = view
            view.active = stack.active
        }
    }

    // C++ integraion. Updates view stack using C++ signals.
    Connections {
        target: viewController
        function onViewControllersChanged() {
            syncViewsAndControllers()
        }
    }

    NavigationBar {
        id: _navigationBar
    }

    Item {
        id: stackView
        anchors {
            top: _navigationBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        property var _views: []

        // mimic StackView methods
        property int depth: 0
        property var currentItem
        function get( index ) {
            return _views[ index ]
        }

        onCurrentItemChanged: {
            depth = _views.length
        }
    }
}
