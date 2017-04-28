import QtQuick 2.7
import QtQuick.Controls 2.0

import QtGraphicalEffects 1.0

import "../../Fonts"
import "../../Controls/UIConstants.js" as  UI



Item {
    id: id_root
    property alias backImageUrl: id_backImage.source
    property string currentInfo:""
    property string currentAlg:""

    property string _backImagePwd:"file:///"+g_root_path+"/etc/docroot/www/images/mainpage/"

    //property string _backImagePwd:"http://localhost:8080/"+"www/images/mainpage/"



    onCurrentInfoChanged: {
        id_info_txt.text = currentInfo
    }
    onCurrentAlgChanged: {
        id_title_txt.text = currentAlg
    }

    implicitHeight: 500
    implicitWidth: 1000

    Image {
        id: id_backImage
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
        source: "qrc:/images/images/mainpage/albumcover.png"
    }

    ListModel{
        id: id_listModel
        ListElement{
            imgAlg:"Ocean"
            imgTitle:"The earth power is deep in ocean."
            imgUrl:"ocean_home.jpg"
        }
        ListElement{
            imgAlg:"AI"
            imgTitle:"World have the dream"
            imgUrl:"alg_ai_img_001.jpg"
        }
        ListElement{
            imgAlg:"IPD"
            imgTitle:"Indoor People Detection."
            imgUrl:"alg_ipd_img_002.jpg"
        }
        ListElement{
            imgAlg:"VFD"
            imgTitle:"Video Face Detection."
            imgUrl:"alg_vfd_img_001.jpg"
        }
        ListElement{
            imgAlg:"PFR"
            imgTitle:"People Face Recognition."
            imgUrl:"alg_pfr_img_001.jpg"
        }
    }

    Timer{
        id: id_timer
        property int currentIndex:0
        interval: 5000
        repeat: true
        running: true
        onTriggered: {
            var item;
            if(currentIndex < id_listModel.count){
                item = id_listModel.get(currentIndex)
                currentIndex++;
            }else{
                currentIndex = 0
                item = id_listModel.get(currentIndex)
            }
            id_root.currentAlg = item["imgAlg"]
            id_backImage.source = id_root._backImagePwd + item["imgUrl"]
            id_root.currentInfo = item["imgTitle"]
        }
    }


    DropShadow {
        anchors.fill: id_title_txt
        horizontalOffset: 0
        verticalOffset: 3
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: id_title_txt
    }

    XmsText{
        id: id_title_txt
        size: 50
        color:UI.COLOR_BASE_WHITE
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60
        XmsText{
            id: id_info_txt
            color: parent.color
            anchors.left: parent.left
            anchors.top: parent.bottom
            anchors.topMargin: 10
        }
    }



}

