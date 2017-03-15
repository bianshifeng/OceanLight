import QtQuick 2.5
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils
import QtQuick.Controls 1.2


Flickable{
    id: id_root
    anchors.fill: parent
    contentHeight: id_container.height
    property alias alarmCount: id_listModel.count



    signal emitShowDetailInfo(var nameStr,var imageUrl,var timeStr,var metaNameStr,var metaImageUrl)

    Column{
        id: id_container
        spacing: 3
        ExclusiveGroup{
            id: id_itemGroup
        }

        Repeater{
            id: id_repeater
            model: id_listModel
            AlarmItemDelegate{

                exclusiveGroup: id_itemGroup
                width: id_root.width
                nameStr: itemName
                timeStr: itemTime
                imageUrl: itemImageUrl
                onEmitClick: {
                    emitShowDetailInfo(nameStr,imageUrl,timeStr,itemMetaImageName,itemMetaImageUrl)
              }
            }

        }

        ListModel{
            id: id_listModel
            ListElement{
                itemId:001
                itemTime:"001"
                itemName:"sdfsdf"
                itemImageUrl:""
                itemMetaImageName:""
                itemMetaImageUrl:""
            }
     }

    }


    Component.onCompleted: id_listModel.clear()



    function appendItem(jsonObj){

        var t_json = JSON.parse(jsonObj)


        if(t_json.status === "warning"){
            var t_no  = id_listModel.count + 1
            var t_time =Utils.timeToDate(Date.now(),"HH:mm:ss")
            var t_name = t_json.name
            var t_imageUrl = "file:///"+t_json.imageUrl
            var t_metaImageUrl = t_json.name
            var t_metaImageName = "file:///"+t_json.imageUrl

            var t_obj = {
                itemId:t_no,
                itemTime:t_time,
                itemName:t_name,
                itemImageUrl:t_imageUrl,
                itemMetaImageName:t_metaImageName,
                itemMetaImageUrl:t_metaImageUrl
            }

            id_listModel.insert(0,t_obj)

        }



    }

}
