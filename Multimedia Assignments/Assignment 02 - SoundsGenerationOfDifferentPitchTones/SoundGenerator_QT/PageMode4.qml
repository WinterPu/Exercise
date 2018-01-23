import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: item1








    GroupBox {
        id: groupBox1
        x: 47
        y: 54
        width: 546
        height: 383
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        title: qsTr("Group Box")

        StackLayout {
            id: stackLayout
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

            RowLayout {
                id: rowLayout1
                Layout.columnSpan: 2
                anchors.fill: parent

                TextArea {
                    id: textArea
                    width: 255
                    height: 357
                    Layout.fillHeight: true
                }

                ColumnLayout {
                    id: columnLayout
                    width: 100
                    height: 100
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.rowSpan: 2

                    RowLayout {
                        id: rowLayout2
                        width: 100
                        height: 100
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.columnSpan: 2

                        GroupBox {
                            id: toneOne
                            width: 100
                            height: 260
                            Layout.preferredHeight: 250
                            Layout.preferredWidth: 50
                            Layout.fillHeight: true
                            Layout.fillWidth: false
                            title: qsTr("Tone One")

                            RadioButton {
                                id: rbTone0One
                                x: 0
                                y: 16
                                text: qsTr("Tone 0")
                            }

                            RadioButton {
                                id: rbTone1One
                                x: 0
                                y: 41
                                width: 56
                                text: qsTr("Tone 1")
                            }

                            RadioButton {
                                id: rbTone2One
                                x: 0
                                y: 66
                                text: qsTr("Tone 2")
                            }

                            RadioButton {
                                id: rbTone3One
                                x: 0
                                y: 91
                                text: qsTr("Tone 3")
                            }

                            RadioButton {
                                id: rbTone4One
                                x: 0
                                y: 116
                                text: qsTr("Tone 4")
                            }

                            RadioButton {
                                id: rbTone5One
                                x: 0
                                y: 141
                                text: qsTr("Tone 5")
                            }

                            RadioButton {
                                id: rbTone6One
                                x: 0
                                y: 166
                                text: qsTr("Tone 6")
                            }

                            RadioButton {
                                id: rbTone7One
                                x: 0
                                y: 191
                                text: qsTr("Tone 7")
                            }

                            RadioButton {
                                id: rbTone8One
                                x: 0
                                y: 216
                                text: qsTr("Tone 8")
                            }
                        }

                        GroupBox {
                            id: toneTwo
                            width: 100
                            height: 260
                            Layout.preferredWidth: 50
                            Layout.fillHeight: true
                            Layout.fillWidth: false
                            title: qsTr("Tone Two")

                            RadioButton {
                                id: rbTone0Two
                                x: 0
                                y: 16
                                text: qsTr("Tone 0")
                            }

                            RadioButton {
                                id: rbTone1Two
                                x: 0
                                y: 41
                                width: 56
                                text: qsTr("Tone 1")
                            }

                            RadioButton {
                                id: rbTone2Two
                                x: 0
                                y: 66
                                text: qsTr("Tone 2")
                            }

                            RadioButton {
                                id: rbTone3Two
                                x: 0
                                y: 91
                                text: qsTr("Tone 3")
                            }

                            RadioButton {
                                id: rbTone4Two
                                x: 0
                                y: 116
                                text: qsTr("Tone 4")
                            }

                            RadioButton {
                                id: rbTone5Two
                                x: 0
                                y: 141
                                text: qsTr("Tone 5")
                            }

                            RadioButton {
                                id: rbTone6Two
                                x: 0
                                y: 166
                                text: qsTr("Tone 6")
                            }

                            RadioButton {
                                id: rbTone7Two
                                x: 0
                                y: 191
                                text: qsTr("Tone 7")
                            }

                            RadioButton {
                                id: rbTone8Two
                                x: 0
                                y: 216
                                text: qsTr("Tone 8")
                            }
                        }
                    }

                    GroupBox {
                        id: groupBox
                        width: 315
                        height: 60
                        title: qsTr("Group Box")

                        RowLayout {
                            id: rowLayout
                            anchors.fill: parent

                            Label {
                                id: label
                                text: qsTr("Label")
                                Layout.preferredHeight: 20
                                Layout.preferredWidth: 30
                            }

                            Slider {
                                id: sliderHorizontal
                                width: 150
                                Layout.preferredHeight: 20
                                Layout.preferredWidth: 150
                            }

                            TextField {
                                id: textField
                                x: 200
                                width: 50
                                Layout.preferredHeight: 20
                                Layout.preferredWidth: 50
                                placeholderText: qsTr("Text Field")
                            }

                        }
                    }
                }
            }
        }
    }
}
