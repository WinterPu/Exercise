import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


Item {
    id: item1
    StackLayout {
        id: stackLayout1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            Layout.columnSpan: 3
            anchors.fill: parent



            GroupBox {
                id: gbWavOne
                x: 0
                y: 0
                height: 100
                Layout.preferredHeight: 100
                Layout.preferredWidth: 580
                Layout.fillHeight: false
                title: "Wav One"
                anchors.leftMargin: 30
                anchors.topMargin: 8
                anchors.rightMargin: 30
                anchors.bottomMargin: 281
                anchors.fill: parent
                Layout.fillWidth: true

                GridLayout {
                    id: gridLayout1
                    height: 100
                    rows: 3
                    flow: GridLayout.TopToBottom
                    anchors.fill: parent

                    Label {
                        id:labelFrequencyOne
                        text: "Frequency"
                        Layout.preferredHeight: 20
                    }
                    Label {
                        id:labelVolumeOne
                        text: "Volume"
                        Layout.preferredHeight: 20
                    }

                    Label {
                        id:labelDurationOne
                        text: "Duration"
                        Layout.preferredHeight: 20
                    }

                    Slider {
                        id: sliderFrequencyOne
                        maximumValue: 10000
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        stepSize: 1
                        updateValueWhileDragging: {
                            textfieldFrequencyOne.text = value
                        }
                    }

                    Slider {
                        id: sliderVolumeOne
                        stepSize: 1
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        maximumValue: 100
                        updateValueWhileDragging:{
                            textfieldVolumeOne.text = value
                        }
                    }

                    Slider {
                        id: sliderDurationOne
                        stepSize: 1
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        maximumValue: 10
                        updateValueWhileDragging: {
                            textfieldDurationOne.text = value
                        }
                    }

                    TextField {
                        id: textfieldFrequencyOne
                        placeholderText: qsTr("Text Field")
                        text:sliderFrequencyOne.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75

                        validator:RegExpValidator { regExp:  /^([1-9]\d{0,3})|10000|0$ / }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderFrequencyOne.value = number;
                        }

                    }
                    TextField {
                        id: textfieldVolumeOne
                        placeholderText: qsTr("Text Field")

                        text:sliderVolumeOne.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75
                        validator:RegExpValidator { regExp:  /^100$|^(\d|[1-9]\d)$/ }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderVolumeOne.value = number;
                        }
                    }
                    TextField {
                        id: textfieldDurationOne
                        placeholderText: qsTr("Text Field")

                        text:sliderDurationOne.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75

                        validator:RegExpValidator { regExp:  /^(([0-9]|10)$/ }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderDurationOne.value = number;
                        }
                    }

                    Label {
                        id:labelFrequencyRangeOne
                        text: "[ 0 , 10000 ]"
                        Layout.preferredHeight: 20
                    }
                    Label {
                        id:labelVolumeRangeOne
                        text: "[ 0 , 100 ]"
                        Layout.preferredHeight: 20
                    }

                    Label {
                        id:labelDurationRangeOne
                        text: "[ 0 , 10 ]"
                        Layout.preferredHeight: 20
                    }

                }

            }




            GroupBox {
                id: gbWavTwo
                x: 0
                y: 0
                height: 100
                Layout.preferredHeight: 100
                Layout.fillHeight: false
                title: "Wav Two"
                anchors.leftMargin: 30
                anchors.topMargin: 187
                anchors.rightMargin: 30
                anchors.bottomMargin: 85
                anchors.fill: parent
                Layout.fillWidth: true

                GridLayout {
                    id: gridLayout2
                    height: 100
                    anchors.bottomMargin: 85
                    rows: 3
                    flow: GridLayout.TopToBottom
                    anchors.fill: parent

                    Label {
                        id:labelFrequencyTwo
                        text: "Frequency"
                        Layout.preferredHeight: 20
                    }
                    Label {
                        id:labelVolumeTwo
                        text: "Volume"
                        Layout.preferredHeight: 20
                    }

                    Label {
                        id:labelDurationTwo
                        text: "Duration"
                        Layout.preferredHeight: 20
                    }

                    Slider {
                        id: sliderFrequencyTwo

                        maximumValue: 10000
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        stepSize: 1
                        updateValueWhileDragging: {
                            textfieldFrequencyTwo.text = value
                        }
                    }

                    Slider {
                        id: sliderVolumeTwo

                        stepSize: 1
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        maximumValue: 100
                        updateValueWhileDragging:{
                            textfieldVolumeTwo.text = value
                        }
                    }

                    Slider {
                        id: sliderDurationTwo

                        stepSize: 1
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 200
                        maximumValue: 10
                        updateValueWhileDragging: {
                            textfieldDurationTwo.text = value
                        }
                    }

                    TextField {
                        id: textfieldFrequencyTwo
                        placeholderText: qsTr("Text Field")

                        text:sliderFrequencyTwo.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75

                        validator:RegExpValidator { regExp:  /^([1-9]\d{0,3})|10000|0$ / }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderFrequencyTwo.value = number;
                        }
                    }
                    TextField {
                        id: textfieldVolumeTwo
                        placeholderText: qsTr("Text Field")

                        text:sliderVolumeTwo.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75
                        validator:RegExpValidator { regExp:  /^100$|^(\d|[1-9]\d)$/ }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderVolumeTwo.value = number;
                        }
                    }
                    TextField {
                        id: textfieldDurationTwo
                        placeholderText: qsTr("Text Field")

                        text:sliderDurationTwo.value
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 75

                        validator:RegExpValidator { regExp:  /^(([0-9]|10)$/ }
                        onTextChanged: {
                            var number = parseInt(text);
                            sliderDurationTwo.value = number;
                        }
                    }

                    Label {
                        id:labelFrequencyRangeTwo
                        text: "[ 0 , 10000 ]"
                        Layout.preferredHeight: 20
                    }
                    Label {
                        id:labelVolumeRangeTwo
                        text: "[ 0 , 100 ]"
                        Layout.preferredHeight: 20
                    }

                    Label {
                        id:labelDurationRangeTwo
                        text: "[ 0 , 10 ]"
                        Layout.preferredHeight: 20
                    }

                }

            }
        }
    }

    GroupBox {
        id: gbDiffDuration
        y: 404
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        Layout.preferredHeight: 40
        anchors.topMargin: 317
        anchors.top: parent.top
        Layout.fillHeight: false
        title: "Difference Duration"
        Layout.fillWidth: false

        StackLayout {
            id: stackLayout
            height: 40
            anchors.fill: parent

            RowLayout {
                id: rowLayout
                height: 40
                Layout.columnSpan: 4
                anchors.fill: parent


                Label {
                    id:labelDiffDuration
                    text: "Duration"
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 100
                }




                Slider {
                    id: sliderDiffDuration

                    stepSize: 1
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 300
                    maximumValue: 3
                    updateValueWhileDragging:{
                        textfieldDiffDuration.text = value
                    }
                }






                TextField {
                    id: textfieldDiffDuration
                    placeholderText: qsTr("Text Field")

                    text:sliderDiffDuration.value
                    Layout.preferredHeight: 20
                    Layout.preferredWidth: 75

                    validator:RegExpValidator { regExp:  /^(([0-9]|10)$/ }
                    onTextChanged: {
                        var number = parseInt(text);
                        sliderDiffDuration.value = number;
                    }
                }

                Label {
                    id:labelDiffDurationRange
                    text: "[ 0 , 3 ]"
                }
            }
        }




    }


}
