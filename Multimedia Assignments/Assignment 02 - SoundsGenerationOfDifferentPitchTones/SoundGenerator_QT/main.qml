import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2


import WAV_Lib 1.0
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

        buttonOutputFilePath.onClicked: fileDialogOutput.open()
        buttonGeneration.onClicked: generate()

        FileDialog{
            id:fileDialogOutput
            selectExisting: false
        onAccepted: {
            mainForm.textFieldOutput.text = fileUrl
           }
        }


    }



    PageMode1{
        id: pageMode1
        height: 380
        anchors.rightMargin: 30
        anchors.bottomMargin: 106
        anchors.leftMargin: 30
        anchors.topMargin: 108
        anchors.fill: parent
        visible: selectPages(0)
    }

    PageMode2{
        id: pageMode2
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
        id: pageMode3
        x: 86
        y: 108
        width: 638
        height: 485
        scale: 1

        visible: selectPages(2)
    }

    PageMode4{
        id: pageMode4
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



    WavFileGenerator{id: myWavFileGenerator}
     function generate(){

         var indexMode = mainForm.modeSelector.currentIndex;

         if(indexMode === 0)
         {
             console.log("OK");


             var path = mainForm.textFieldOutput.text;
             if(path !=="")
             {
               myWavFileGenerator.initWavFile(pageMode1.sliderFrequency.value,pageMode1.sliderVolume.value,pageMode1.sliderDuration.value);
               myWavFileGenerator.createWavFile(path);

             }

         }
         else if (indexMode === 1)
         {
            console.log("Start 1");

             var input_path = pageMode2.textFieldInput.text;
             var output_path = mainForm.textFieldOutput.text;
             if(path !=="")
             {

                soundGenerator.createWavFileFromFile(input_path,output_path);
             }
         }
         else if (indexMode === 2)
         {

         }
         else if (indexMode === 3)
         {

         }
     }

}
