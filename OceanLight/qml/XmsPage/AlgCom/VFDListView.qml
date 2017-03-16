import QtQuick 2.5
import QtQuick.Controls 2.1
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils
import Xms.Server 1.0


Flickable{
    id: id_root
    anchors.fill: parent
    contentHeight: id_container.height
    property alias alarmCount: id_listModel.count


    signal emitShowDetailInfo(var nameStr,var imageUrl,var timeStr,var metaNameStr,var metaImageUrl)

    Column{
        id: id_container
        spacing: 3
        Repeater{
            id: id_repeater
            model: id_listModel
            AlarmItemDelegate{
                width: id_root.width
                nameStr: itemName
                timeStr: itemTime
                imageUrl: itemImageUrl
                peopleName:itemPeopleName
                peopleIsReg:itemPeopleIsReg
                onEmitClick: {
                    emitShowDetailInfo(nameStr,imageUrl,timeStr,itemMetaImageName,itemMetaImageUrl)
                }
            }
        }
        ListModel{
            id: id_listModel
            ListElement{
                itemId:0
                itemTime:"001"
                itemName:"sdfsdf"
                itemImageUrl:""
                itemMetaImageName:"name2"
                itemMetaImageUrl:""
                itemPeopleName:""
                itemPeopleIsReg:false
            }
        }
    }


    Component.onCompleted: id_listModel.clear()

    function appendItem(jsonObj){

        var t_json = JSON.parse(jsonObj)

        var t_no  = id_listModel.count + 1
        var t_time =Utils.timeToDate(Date.now(),"HH:mm:ss")
        var t_name = t_json.name
        var t_imageUrl = "file:///"+t_json.imageUrl
        var t_metaImageUrl = "file:///"+t_json.metaImageUrl
        var t_metaImageName = t_json.metaImageName

        var t_obj = {
            itemId:t_no,
            itemTime:t_time,
            itemName:t_name,
            itemImageUrl:t_imageUrl,
            itemMetaImageName:t_metaImageName,
            itemMetaImageUrl:t_metaImageUrl,
            itemPeopleName:"",
            itemPeopleIsReg:false
        }

        id_listModel.insert(0,t_obj)
        AlgServer.push_pfr_imageFrame(t_metaImageName,t_metaImageUrl,1)

    }

    function modifyItem(jsonObj){
        try{
            var t_obj = JSON.parse(jsonObj)

            var t_imageName = ""
            t_imageName = t_obj.imageName
            var t_peopleName = t_obj.peopleName
            var t_peolpleIsReg = t_obj.isRegister

            for(var index = 0; index < id_listModel.count; index ++){
                if(t_imageName.indexOf(id_listModel.get(index).itemMetaImageName)>=0){
                    id_listModel.get(index).itemPeopleName = t_peopleName
                    id_listModel.get(index).itemPeopleIsReg =t_peolpleIsReg
                    break
                }
            }

        }catch(e){

        }

    }

    Connections{
        id: id_algServer_cnt
        target: AlgServer
        ignoreUnknownSignals: true
        onSig_alg_pfr_data: {
            id_root.modifyItem(message)

        }

    }



    Button{
        text: "add data"
        anchors.centerIn: parent
        visible: false

        onClicked: {

//            itemId:0
//            itemTime:"001"
//            itemName:"sdfsdf"
//            itemImageUrl:"name1"
//            itemMetaImageName:"name2"
//            itemMetaImageUrl:"name3"
//            itemPeopleName:"name4"

            var t_obj = {
                imageName:"name2.jpg",
                peopleName:"bianshifeng"
            }


            id_root.modifyItem(JSON.stringify(t_obj))


        }

    }


}
