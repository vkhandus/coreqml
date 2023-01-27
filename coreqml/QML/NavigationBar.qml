import QtQuick 2.0
import CoreQML 1.0

// Navigation bar
Rectangle {
    id: root

    anchors.top: parent.top

    width: parent.width
    height: !hidden ? App.style.navigationBar.height : 0

    property bool hidden: false
    property alias sourceComponent: contentLoader.sourceComponent
    property alias sourceItem: contentLoader.item

    Loader {
        id: contentLoader
        anchors.fill: parent
    }
}
