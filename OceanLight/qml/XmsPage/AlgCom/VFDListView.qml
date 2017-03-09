import QtQuick 2.5
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils


Flickable{
    id: id_root
    anchors.fill: parent
    contentHeight: id_container.height
    property alias alarmCount: id_listModel.count

    function appendItem(jsonObj){

        var t_json = JSON.parse(jsonObj)

        var t_no  = id_listModel.count + 1
        var t_time =Utils.timeToDate(Date.now(),"HH:mm:ss")
        var t_name = t_json.name
        var t_imageUrl = "file:///"+t_json.imageUrl

        var t_obj = {
            itemId:t_no,
            itemTime:t_time,
            itemName:t_name,
            itemImageUrl:t_imageUrl
        }

        id_listModel.insert(0,t_obj)

    }

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
            }
        }
        ListModel{
            id: id_listModel
            ListElement{
                itemId:001
                itemTime:"001"
                itemName:"sdfsdf"
                itemImageUrl:""
            }
        }
    }


    Component.onCompleted: id_listModel.clear()

}
