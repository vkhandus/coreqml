import QtQuick 2.0
import CoreQML 1.0

View {
    id: root

    Component {
        id: logoScreen
        AnimatedImage {
            id: root
            anchors.fill: parent
            fillMode: Image.Stretch
            source: viewController.splash
        }
    }

    Loader {
        id: splashLoader
        anchors.fill: parent
        sourceComponent: logoScreen

        onLoaded: {
            loadNextPage.start()
        }
    }

    Timer {
        id: loadNextPage
        repeat: false
        interval: 2000 // wait some time for user to see the splash
        running: false
        onTriggered: {
            viewController.loaded()
        }
    }
}
