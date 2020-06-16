import QtQml.Models 2.3
import QtQml 2.3
import QtQuick 2.3
import QtQuick 2.15
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import OpenGLWindow 1.0

//import fbitem 1.0

OpenGLWindow {
    id: window
    visible: true
    width: 1920
    height: 1080
    Material.theme: Material.Light
    Material.accent: Material.Purple
    inputPos: Qt.vector2d(pointhandler.point.x, pointhandler.point.x)
    //console.log: pointhandler.point.x + pointhandler.point.x

    PointHandler {
        id: pointhandler
    }

    WheelHandler {

    }

    PinchHandler {
        target: null
    }

    //title: qsTr("logix")

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rowSpacing: 5
        layoutDirection: Qt.LeftToRight
        flow: width > height ? GridLayout.TopToBottom : GridLayout.LeftToRight
        anchors.margins: 10

        MenuBar2 {
            Layout.row: 0
            Layout.column: 0
            content: [
                ToolButton {
                    text: qsTr("File")
                },

                ToolButton {
                    text: qsTr("Tools")
                }
            ]
        }

        Button {
            id: toolpaneToggleButton
            Layout.row: 0
            Layout.column: 3
            Material.background: Material.BlueGrey
            Material.elevation: 6
            text: qsTr("TOGGLE TOOLS")

            property bool toolPaneIsOn : width > height ? true : false
            onClicked: {
                toolPaneIsOn = !toolPaneIsOn
            }
        }

        Item {
            id: element
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 0
            Layout.columnSpan: 2
        }

        Pane {
            id: toolpane
            // width: 370
            Layout.minimumWidth: window.width > window.height ? 400 : 200
            Layout.row: 1
            Layout.column: 3
            Layout.fillHeight: true
            Material.elevation: 6
            visible: toolpaneToggleButton.toolPaneIsOn

            ColumnLayout {
                id: columnLayout2
                anchors.fill: parent

                TabBar {
                    id: tabBar
                    clip: true
                    Layout.fillWidth: true

                    TabButton {
                        id: tabButton
                        text: qsTr("Node Options")
                    }

                    TabButton {
                        id: tabButton1
                        text: qsTr("New")
                    }

                    TabButton {
                        id: tabButton2
                        text: qsTr("All")
                    }


                }

                StackLayout {
                    id: stackLayout
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    currentIndex: tabBar.currentIndex

                    ScrollView {
                        id: scrollView
                        contentWidth: -1
                        clip: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        ScrollBar.horizontal.interactive: false

                        Column {
                            id: column
                            spacing: 30
                            anchors.margins: 10

                            GroupList{
                                title: "positions";
                                height: childrenRect.height
                                width: childrenRect.width
                                content: [
                                    Slider {
                                        id: slider1
                                        value: 0.5
                                    },
                                    CheckBox {

                                    },
                                    Text {
                                        id: text1
                                        text: qsTr("row1\ndfgsfd")
                                    }

                                ]
                            }

                            GroupList{
                                title: "Group1";
                                height: childrenRect.height
                                width: childrenRect.width
                                content: [
                                    Slider {
                                        id: slider
                                        value: 0.5
                                    },
                                    CheckBox {

                                    }
                                ]
                            }
                        }
                    }
                }
            }
        }
    }
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
