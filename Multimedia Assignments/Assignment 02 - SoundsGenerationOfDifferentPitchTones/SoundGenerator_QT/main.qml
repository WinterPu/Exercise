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
           
            var path = fileUrl.toString();
            var head = "file:///";

            path = path.substring(head.length,path.length);  
            mainForm.textFieldOutput.text = path;
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

         var output_path = mainForm.textFieldOutput.text;

         if(output_path === "")
         {
            console.log("Empty Path");
            mainForm.labelOutputStatus.text = "null path";
            return;
         }

         soundGenerator.initForQt();
         mainForm.labelOutputStatus.text = "start";
         mainForm.progressBarGeneration.value =0;

         if(indexMode === 0)
         {

           myWavFileGenerator.initWavFile(pageMode1.sliderFrequency.value,pageMode1.sliderVolume.value,pageMode1.sliderDuration.value);
           myWavFileGenerator.createWavFile(output_path);

         }
         else if (indexMode === 1)
         {
             var input_path = pageMode2.textFieldInput.text;
             soundGenerator.createWavFileFromFile(input_path,output_path);
         }
         else if (indexMode === 2)
         {
             var f1 = pageMode3.sliderFrequencyOne.value;
             var v1 = pageMode3.sliderVolumeOne.value;
             var d1 = pageMode3.sliderDurationOne.value;

             var f2 = pageMode3.sliderFrequencyTwo.value;
             var v2 = pageMode3.sliderVolumeTwo.value;
             var d2 = pageMode3.sliderDurationTwo.value;

             var diff_time = pageMode3.sliderDiffDuration.value;
             soundGenerator.createWavFileFromTwoWav(f1,v1,d1,f2,v2,d2,output_path,diff_time);
         }
         else if (indexMode === 3)
         {

            var numTone1 =pageMode4.getSelectedTone(1);
            var numTone2 =pageMode4.getSelectedTone(2);
            var context = pageMode4.textArea.text;
            var duration = pageMode4.sliderDiffDuration.value;

            var bassoTone;
            var altoTone;
             if(numTone1 <= numTone2)
             {
                bassoTone = numTone1;
                altoTone = numTone2;
             }
             else
             {
                 bassoTone = numTone2;
                 altoTone = numTone1;
             }

              soundGenerator.createWavFileFromText(context,output_path,bassoTone,altoTone,duration);
         }

          mainForm.labelOutputStatus.text = "Done";
          mainForm.progressBarGeneration.value =100;
     }

}
