import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
//import fbitem 1.0

Item{
    property string title
    property alias content: column2.children

    Material.foreground: Material.Purple
    Column {
        id: column1
        spacing: 10
        Text {
            color: Material.color(Material.Purple)
            id: title1
            text: qsTr(title)
        }
        Column {
            id: column2
            spacing: 10
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
