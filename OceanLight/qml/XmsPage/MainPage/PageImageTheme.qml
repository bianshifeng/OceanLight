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
            imgAlg:"IPD"
            imgTitle:"The alg can give you a future for sale."
            imgUrl:"alg_ipd_img_001.jpg"
        }
        ListElement{
            imgAlg:"IPD"
            imgTitle:"From here you can konw ------- ocean have the power for wolrd, the Ai is the my company."
            imgUrl:"alg_ipd_img_002.jpg"
        }
        ListElement{
            imgAlg:"IPD"
            imgTitle:"In the future cpc can been setting all of the shop  and home."
            imgUrl:"alg_ipd_img_003.jpg"
        }

        ListElement{
            imgAlg:"VFD"
            imgTitle:"World have the dream"
            imgUrl:"alg_vfd_img_001.jpg"
        }
        ListElement{
            imgAlg:"VFD"
            imgTitle:"World have the dream"
            imgUrl:"alg_vfd_img_002.jpg"
        }
        ListElement{
            imgAlg:"VFD"
            imgTitle:"World have the dream"
            imgUrl:"alg_vfd_img_003.jpg"
        }
        ListElement{
            imgAlg:"VIP"
            imgTitle:"World have the dream"
            imgUrl:"alg_vip_img.jpg"
        }

        ListElement{
            imgAlg:"AFS"
            imgTitle:"World have the dream"
            imgUrl:"alg_afd_img_001.jpg"
        }

        ListElement{
            imgAlg:"AI"
            imgTitle:"World have the dream"
            imgUrl:"alg_ai_img_001.jpg"
        }
        ListElement{
            imgAlg:"CCC"
            imgTitle:"World have the dream"
            imgUrl:"alg_ccc_img_001.png"
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

