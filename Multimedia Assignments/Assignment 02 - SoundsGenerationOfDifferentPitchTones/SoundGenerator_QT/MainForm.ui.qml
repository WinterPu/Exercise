import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle {
    id: baseView

    width: 800
    height: 600
    property alias progressBarGeneration: progressBarGeneration
    property alias buttonOutputFilePath: buttonOutputFilePath
    property alias labelOutputStatus: labelOutputStatus
    property alias buttonGeneration: buttonGeneration
    property alias textFieldOutput: textFieldOutput
    property alias modeSelector: modeSelector
    property alias cbModeItems: cbModeItems
    property alias modeTitle: modeTitle
    property alias buttonShutDown: buttonShutDown


    Image {
        id: background_image
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "GUI_Image/Background.jpg"
    }

    Rectangle {
        id: topPanel
        height: 91
        color: "#cc000000"
        border.width: 1
        border.color: "#cc000000"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Text {
            id: modeTitle
            width: 340
            height: 92
            color: "#ffffff"
            text: qsTr("Mode: Wav Generation")
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: false
            styleColor: "#ffffff"
            font.pixelSize: 29

        }

        ComboBox {
            id: modeSelector
            x: 360
            y: 36
            width: 174
            height: 27

            model: ListModel {
                id: cbModeItems
                ListElement { text: "Wav Generation"; color: "Yellow" }
                ListElement { text: "Sound Generation [From File]"; color: "Green" }
                ListElement { text: "Sound Generation [From Wav]"; color: "Brown" }
                ListElement { text: "Sound Generation [From User Input]"; color: "Black" }
            }
        }

        CheckBox {
            id: boxFM
            x: 639
            y: 30
            width: 74
            height: 33
            //text: qsTr("FM")
            checked: false
            
            style: CheckBoxStyle {
                label: Text {
                    color: "white"
                    text:"FM"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize:  20
                }
            }
        }

        Button {
            id: buttonShutDown
            x: 736
            y: 21
            width: 50
            height: 50
            iconSource: "GUI_Image/shutdown_icon.png"
            checkable: false
            clip: false
            visible: true

            style: ButtonStyle {
                background: Rectangle {
                    color: "#27a9e3"
                    border.color: "#27a9e3"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                    }
                }
            }
        }

        MouseArea {
            id: shutDown
            x: 736
            width: 50
            height: 50
            visible: false
            anchors.right: parent.right
            anchors.rightMargin: 14
            anchors.top: parent.top
            anchors.topMargin: 21

            Rectangle {
                id: rectangle
                x: -17
                width: 50
                height: 50
                color: "#27a9e3"
                radius: 3
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
            }

            Image {
                id: image1
                x: 0
                y: 0
                width: 40
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "GUI_Image/shutdown_icon.png"
            }

        }
    }

    Rectangle {
        id: funtionArea
        y: 110
        height: 381
        opacity: 0.9
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
    }

    Rectangle {
        id: generationArea
        y: 512
        height: 74
        opacity: 0.5
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30

        GroupBox {
            id: groupBox
            anchors.fill: parent
            title: qsTr("")

            ColumnLayout {
                id: columnLayout
                width: 740
                anchors.fill: parent

                RowLayout {
                    id: rowLayout
                    width: 740
                    height: 100
                    Layout.columnSpan: 3
                    Layout.rowSpan: 1
                    Label {
                        id: labelOutput
                        x: 0
                        y: 0
                        width: 100
                        text: qsTr("Output Path:")
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 100
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    TextField {
                        id: textFieldOutput
                        x: 0
                        y: 0
                        width: 500
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 500
                        placeholderText: qsTr("Text Field")
                    }

                    Button {
                        id: buttonOutputFilePath
                        x: 0
                        width: 100
                        text: qsTr("...")
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 100
                    }
                }

                RowLayout {
                    id: rowLayout1
                    width: 740
                    height: 100
                    Layout.columnSpan: 3
                    ProgressBar {
                        id: progressBarGeneration
                        width: 500
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 400
                    }
                    Label {
                        id: labelOutputStatus
                        x: 0
                        y: 0
                        width: 100
                        text: qsTr("Done")
                        fontSizeMode: Text.Fit
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 100
                    }

                    Button {
                        id: buttonGeneration
                        x: 0
                        width: 0
                        height: 0
                        text: qsTr("Generation")
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                    }
                }
            }
        }

    }

}
