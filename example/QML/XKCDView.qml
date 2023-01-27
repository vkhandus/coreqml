import QtQuick 2.0
import CoreQML 1.0

View {
    id: root

    readonly property var cXkcdPalette: App.paletteManager.palette.xkcdView

    // To display reload button in the Navigation Bar
    property var navBarItems: Component {
        Button {
            height: parent.height
            width: height

            paletteSelector {
                paletteObject: App.paletteManager.palette.navigationBarButton
                icon: App.paletteManager.palette.navBar.reloadIcn
            }

            iconMarginInPercents: App.style.navBarButton.iconMarginInPercent

            RotationAnimation on rotation {
                running: xkcdItem.state === xkcdItem.loading
                loops: Animation.Infinite
                duration: 1000
                from: 0
                to: 360
            }

            onClicked: {
                xkcdItem.getRandomXkcd()
            }
        }
    }

    // Navigation Bar title
    title: {
        if (xkcdItem.state === xkcdItem.ready) {
            return xkcdItem.title
        } else if (xkcdItem.state === xkcdItem.loading) {
            return "Wait for it..."
        } else if (xkcdItem.state === xkcdItem.error) {
            return "Something wrong, try to reload page"
        }
        return ""
    }

    // Retrieves random XKCD comics from web
    QtObject {
        id: xkcdItem

        readonly property int maxItems: 2720
        readonly property int notinit: -1
        readonly property int ready: 0
        readonly property int loading: 1
        readonly property int error: 2

        property int state: notinit
        property string image: ""
        property string alt: ""
        property string title: ""

        function getRandomXkcd() {
            var randomComics = Math.floor(Math.random() * maxItems).toString()
            var xhr = new XMLHttpRequest()
            var url = "https://xkcd.com/" + randomComics + "/info.0.json"

            xhr.open("GET", url, true)
            xhr.onreadystatechange = function () {
                if (xhr.readyState == xhr.DONE) {
                    if (xhr.status == 200) {
                        var jsonObject = JSON.parse(xhr.responseText)

                        xkcdItem.state = ready
                        xkcdItem.image = jsonObject.img
                        xkcdItem.alt = jsonObject.alt
                        xkcdItem.title = jsonObject.safe_title
                    } else {
                        xkcdItem.state = error
                    }
                }
            }

            xkcdItem.state = loading
            xhr.send()
        }
    }

    // background
    Rectangle {
        anchors.fill: parent
        color: cXkcdPalette.backgroundColor
    }

    // XKCD image
    Image {
        anchors.fill: parent

        fillMode: Image.PreserveAspectFit
        anchors.margins: App.style.xkcdView.imageMargin
        source: xkcdItem.image
    }

    // XKCD text
    Rectangle {
        id: xkcdText
        width: xText.contentWidth + App.style.xkcdView.textBoxContentPadding
        height: xText.contentHeight + App.style.xkcdView.textBoxContentPadding

        anchors {
            bottom: parent.bottom
            margins: App.style.xkcdView.textBoxContentPadding
            horizontalCenter: parent.horizontalCenter
        }

        visible: false
        radius: App.style.xkcdView.textBoxBorderRadius
        border.color: cXkcdPalette.textBorderColor
        border.width: App.style.xkcdView.textBoxBorderWidth

        Text {
            id: xText
            color: cXkcdPalette.textColor

            x: App.style.xkcdView.textBoxContentPadding / 2
            y: App.style.xkcdView.textBoxContentPadding / 2
            width: root.width * 0.8

            wrapMode: Text.Wrap
            font.pixelSize: App.style.xkcdView.textBoxContentFontSize
            text: xkcdItem.alt

            onTextChanged: {
                xkcdText.visible = false
            }
        }
    }

    // Shows/hides XKCD text
    MouseArea {
        anchors.fill: parent

        onClicked: {
            if (xkcdItem.state === xkcdItem.ready) {
                xkcdText.visible = !xkcdText.visible
            }
        }
    }

    onActiveChanged: {
        if (active) {
            xkcdItem.getRandomXkcd()
        }
    }
}
