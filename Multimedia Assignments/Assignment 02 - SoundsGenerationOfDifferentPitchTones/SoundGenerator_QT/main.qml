import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2

Window {
    id: mainWindows
    title: qsTr("Sound Generator")
    visible: true
    width: 800
    height: 600


    MainForm {
        id: mainForm
        anchors.fill: parent
        buttonShutDown.onClicked:{
            //messageDialog.show(qsTr("Button pressed"));
            mainWindows.close();
        }

        buttonOutput.onClicked: fileDialogOutput.open()


        FileDialog{
            id:fileDialogOutput
            selectExisting: false
        onAccepted: {
            mainForm.textFieldOutput.text = fileUrl

         }
        }


    }



    PageMode1{
        height: 380
        anchors.rightMargin: 30
        anchors.bottomMargin: 106
        anchors.leftMargin: 30
        anchors.topMargin: 108
        anchors.fill: parent
        visible: selectPages(0)
    }

    PageMode2{
        x: 0
        y: 110
        height: 380
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        visible: selectPages(1)
    }

    PageMode3{
        y: 110
        height: 380
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        visible: selectPages(2)
    }

    PageMode4{
        x: 56
        y: 26
        width: 800
        height: 530
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        visible: selectPages(3)

    }
    function selectPages(index){
        mainForm.modeTitle.text = mainForm.modeSelector.currentText;
        if(mainForm.modeSelector.currentIndex === index)
            return true;
        else
            return false;
    }

    function generate(){

    }
}
