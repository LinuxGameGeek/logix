import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3

Item {
    width: row.width
    height: row.height
    property alias content: row.children
    ToolBar {
        id: toolBar
        anchors.fill: parent

        Row {
            id: row
            anchors.fill: parent

        }
    }
}
