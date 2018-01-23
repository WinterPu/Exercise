import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


Item {
    GroupBox {
        id: gbWavOne
        height: 150
        title: "Wav One"
        anchors.leftMargin: 30
        anchors.topMargin: 8
        anchors.rightMargin: 30
        anchors.bottomMargin: 281
        anchors.fill: parent
        Layout.fillWidth: true

        GridLayout {
            id: gridLayout1
            rows: 3
            flow: GridLayout.TopToBottom
            anchors.fill: parent

            Label {
                id:labelFrequencyOne
                text: "Frequency"
            }
            Label {
                id:labelVolumeOne
                text: "Volume"
            }

            Label {
                id:labelDurationOne
                text: "Duration"
            }

            Slider {
                id: sliderFrequencyOne
            }

            Slider {
                id: sliderVolumeOne
            }

            Slider {
                id: sliderDurationOne
            }

            TextField {
                id: textfieldFrequencyOne
                placeholderText: qsTr("Text Field")
            }
            TextField {
                id: textfieldVolumeOne
                placeholderText: qsTr("Text Field")
            }
            TextField {
                id: textfieldDurationOne
                placeholderText: qsTr("Text Field")
            }

            Label {
                id:labelFrequencyRangeOne
                text: "Frequency"
            }
            Label {
                id:labelVolumeRangeOne
                text: "Volume"
            }

            Label {
                id:labelDurationRangeOne
                text: "Duration"
            }

        }

    }






    GroupBox {
        id: gbWavTwo
        height: 150
        title: "Wav Two"
        anchors.leftMargin: 30
        anchors.topMargin: 242
        anchors.rightMargin: 30
        anchors.bottomMargin: 30
        anchors.fill: parent
        Layout.fillWidth: true

        GridLayout {
            id: gridLayout2
            rows: 3
            flow: GridLayout.TopToBottom
            anchors.fill: parent

            Label {
                id:labelFrequencyTwo
                text: "Frequency"
            }
            Label {
                id:labelVolumeTwo
                text: "Volume"
            }

            Label {
                id:labelDurationTwo
                text: "Duration"
            }

            Slider {
                id: sliderFrequencyTwo
            }

            Slider {
                id: sliderVolumeTwo
            }

            Slider {
                id: sliderDurationTwo
            }

            TextField {
                id: textfieldFrequencyTwo
                placeholderText: qsTr("Text Field")
            }
            TextField {
                id: textfieldVolumeTwo
                placeholderText: qsTr("Text Field")
            }
            TextField {
                id: textfieldDurationTwo
                placeholderText: qsTr("Text Field")
            }

            Label {
                id:labelFrequencyRangeTwo
                text: "Frequency"
            }
            Label {
                id:labelVolumeRangeTwo
                text: "Volume"
            }

            Label {
                id:labelDurationRangeTwo
                text: "Duration"
            }

        }

    }


}
