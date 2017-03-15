import QtQuick 2.7
import QtQuick.Controls 2.0



Item {
    id: id_root
    property alias backImageUrl: id_backImage.source
    property string currentInfo:""
    property string currentAlg:""

    property string _backImagePwd:"file:///"+g_root_path+"/etc/docroot/www/images/mainpage/"

    //property string _backImagePwd:"http://localhost:8080/"+"www/images/mainpage/"


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



}

