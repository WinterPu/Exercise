import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: item1
    property alias textFieldInput: textFieldInput

    GroupBox {
        id: groupBox
        height: 40
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        title: qsTr("")

        StackLayout {
            id: stackLayout
            anchors.fill: parent

            RowLayout {
                id: rowLayout
                Layout.columnSpan: 3
                anchors.fill: parent

                Label {
                    id: labelInput
                    text: qsTr("Input Text File")
                    Layout.preferredHeight: 20
                    fontSizeMode: Text.Fit
                    Layout.preferredWidth: 100
                }

                TextField {
                    id: textFieldInput
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 300
                    placeholderText: qsTr("Text Field")
                }

                Button {
                    id: buttonInputFile
                    text: qsTr("...")
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 100
                    onClicked: fileDialogInput.open()
                }
            }
        }
    }


    FileDialog{
        id:fileDialogInput
        onAccepted: {
            textFieldInput.text = fileUrl;
        }
    }
}
