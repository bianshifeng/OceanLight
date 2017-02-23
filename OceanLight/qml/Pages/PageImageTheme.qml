import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
    id: id_root
    property alias backImageUrl: id_backImage.source
    property string currentInfo:""
    implicitHeight: 500
    implicitWidth: 1000

    Image {
        id: id_backImage
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
    }

    ListModel{
        id: id_listModel
        ListElement{
            imgTitle:"The alg can give you a future for sale."
            imgUrl:"qrc:/images/images/mainpage/wall000-1680x1050.jpg"
        }
        ListElement{
            imgTitle:"From here you can konw ------- ocean have the power for wolrd, the Ai is the my company."
            imgUrl:"qrc:/images/images/mainpage/wall001-1680x1050.jpg"
        }
        ListElement{
            imgTitle:"In the future cpc can been setting all of the shop  and home."
            imgUrl:"qrc:/images/images/mainpage/wall004-1920x1200.jpg"
        }

        ListElement{
            imgTitle:"World have the dream"
            imgUrl:"qrc:/images/images/mainpage/albumcover.png"
        }
    }

    Timer{
        id: id_timer
        property int currentIndex:0
        interval: 5000
        repeat: true
        running: true
        onTriggered: {


            if(currentIndex < id_listModel.count){

                var item = id_listModel.get(currentIndex)
                id_backImage.source = item["imgUrl"]
                id_root.currentInfo = item["imgTitle"]
                console.log(item["imgUrl"])
                currentIndex++;
            }else{
                currentIndex = 0
                var item = id_listModel.get(currentIndex)
                id_backImage.source = item["imgUrl"]
                id_root.currentInfo = item["imgTitle"]
            }

        }
    }

}

