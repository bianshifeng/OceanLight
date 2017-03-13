import QtQuick 2.5
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

    function appendItem(jsonObj){

        var t_json = JSON.parse(jsonObj)

        var t_no  = id_listModel.count + 1
        var t_time =Utils.timeToDate(Date.now(),"HH:mm:ss")
        var t_name = t_json.name
        var t_imageUrl = "file:///"+t_json.imageUrl
        var t_bigImageUrl = "file:///"+t_json.bigImageUrl
        var t_bigImageName = t_json.bigImageName

        var t_obj = {
            itemId:t_no,
            itemTime:t_time,
            itemName:t_name,
            itemImageUrl:t_imageUrl,
            itemBigImageUrl:t_bigImageUrl,
            itemBigImageName:t_bigImageName
        }

        id_listModel.insert(0,t_obj)
        AlgServer.push_pfr_imageFrame(t_bigImageName,t_bigImageUrl,1)

    }

    signal emitShowDetailInfo(var nameStr,var imageUrl,var timeStr)

    Column{
        id: id_container
        spacing: 3
        Repeater{
            id: id_repeater
            model: id_listModel
            AlarmItemDelegate{
                width: id_root.width
                nameStr: itemBigImageName
                timeStr: itemTime
                imageUrl: itemBigImageUrl
                onEmitClick: {
                    emitShowDetailInfo(nameStr,imageUrl,timeStr)
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
                itemBigImageUrl:""
                itemBigImageName:""
            }
        }
    }


    Component.onCompleted: id_listModel.clear()

}
