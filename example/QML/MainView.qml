import QtQuick 2.0
import QtQuick.Layouts 1.0
import CoreQML 1.0

// Provides navigation functionality to the application
Stack {
    id: root

    // Navigation Bar customization
    navigationBar {
        color: App.paletteManager.palette.navBar.backgroundColor
        sourceComponent: RowLayout {
            spacing: 0

            Button {
                paletteSelector {
                    paletteObject: App.paletteManager.palette.navigationBarButton
                    icon: root.depth <= 1 ? App.paletteManager.palette.navBar.homeIcn : App.paletteManager.palette.navBar.backIcn
                }

                height: parent.height
                width: height
                //paletteSelector.paletteObject.icon: root.depth <= 1 ? App.paletteManager.palette.navBar.homeIcn : App.paletteManager.palette.navBar.backIcn
                iconMarginInPercents: App.style.navBarButton.iconMarginInPercent

                onClicked: {
                    if (root.depth > 1) {
                        root.popView()
                    }
                }
            }

            Text {
                height: parent.height
                Layout.fillWidth: true

                text: root.currentItem.title
                font.pixelSize: parent.height / 2
                verticalAlignment: Text.AlignVCenter
                color: App.paletteManager.palette.navBar.textColor
                elide: Text.ElideRight
            }

            Button {
                paletteSelector {
                    paletteObject: App.paletteManager.palette.navigationBarButton
                    icon: App.paletteManager.palette.navBar.paletteIcn
                }
                height: parent.height
                width: height

                iconMarginInPercents: App.style.navBarButton.iconMarginInPercent

                onClicked: {
                    App.paletteManager.resetPalette(
                                (App.paletteManager.paletteMode + 1) % 2)
                }
            }

            // Every child view can add own items providing navBarItems component
            Loader {
                id: customItemLoader
                height: parent.height

                visible: root.currentItem.hasOwnProperty("navBarItems")
                sourceComponent: root.currentItem.navBarItems
            }
        }
    }
}
