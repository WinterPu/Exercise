import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Item {
    id: pageMode1
    width: 560
    height: 420
    property alias sliderDuration: sliderDuration
    property alias sliderVolume: sliderVolume
    property alias sliderFrequency: sliderFrequency

    GroupBox {
        id: gridBox
        anchors.fill: parent
        Layout.fillWidth: true

        GridLayout {
            id: gridLayout
            rows: 3
            flow: GridLayout.TopToBottom
            anchors.fill: parent

            Label {
                id:labelFrequency
                text: "Frequency"
            }
            Label {
                id:labelVolume
                text: "Volume"
            }

            Label {
                id:labelDuration
                text: "Duration"
                Layout.preferredHeight: 20
                Layout.preferredWidth: 75
            }

            Slider {
                id: sliderFrequency
                stepSize: 1
                Layout.preferredHeight: 20
                Layout.preferredWidth: 300
                maximumValue: 10000
                updateValueWhileDragging: {
                    textfieldFrequency.text = value
                }

            }

            Slider {
                id: sliderVolume
                stepSize: 1
                Layout.preferredHeight: 20
                Layout.preferredWidth: 300
                maximumValue: 100
                updateValueWhileDragging:{
                    textfieldVolume.text = value
                }
            }

            Slider {
                id: sliderDuration
                stepSize: 1
                Layout.preferredHeight: 20
                Layout.preferredWidth: 300
                maximumValue: 10
                updateValueWhileDragging: {
                    textfieldDuration.text = value
                }
            }

            TextField {
                id: textfieldFrequency
                placeholderText: qsTr("Text Field")
                text:sliderFrequency.value
                Layout.preferredHeight: 20
                Layout.preferredWidth: 75

                validator:RegExpValidator { regExp:  /^([1-9]\d{0,3})|10000|0$ / }
                onTextChanged: {
                        var number = parseInt(text);
                        sliderFrequency.value = number;
                }

            }
            TextField {
                id: textfieldVolume
                placeholderText: qsTr("Text Field")
                text:sliderVolume.value
                Layout.preferredHeight: 20
                Layout.preferredWidth: 75
                validator:RegExpValidator { regExp:  /^100$|^(\d|[1-9]\d)$/ }
                onTextChanged: {
                    var number = parseInt(text);
                    sliderVolume.value = number;
                }
            }
            TextField {
                id: textfieldDuration
                placeholderText: qsTr("Text Field")
                text:sliderDuration.value
                Layout.preferredHeight: 20
                Layout.preferredWidth: 75

                validator:RegExpValidator { regExp:  /^(([0-9]|10)$/ }
                onTextChanged: {
                        var number = parseInt(text);
                        sliderDuration.value = number;
                }
            }

            Label {
                id:labelFrequencyRange
                text: "[ 0,10000 ]"
            }
            Label {
                id:labelVolumeRange
                text: "[ 0, 100]"
            }

            Label {
                id:labelDurationRange
                text: "[ 0 , 10 ]"
            }

        }

    }




}
