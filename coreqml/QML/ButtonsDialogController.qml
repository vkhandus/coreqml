import QtQuick 2.0
import CoreQML 1.0

DialogController {
    id: qmlDialog

    property string title
    property string text
    property var buttons: [] // should contain list of objects that contain `id`, `title`. Additionaly can contain `disabled`. E.g.:
                             // [ { id: 1, title: "Yes" }, { id: 2, title: "No" } ]
}
