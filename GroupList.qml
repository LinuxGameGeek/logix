import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
//import fbitem 1.0

GroupBox {
    id: groupBox
    Layout.fillWidth: true
    Layout.margins: parent.margin
    //anchors.fill: parent
    Material.foreground: Material.Pink
    title: qsTr("Group Box")
    Slider {
        id: slider
        value: 0.5
    }
}
