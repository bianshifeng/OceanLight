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


        if(t_json.status === "warning"){
            var t_no  = id_listModel.count + 1
            var t_time =Utils.timeToDate(Date.now(),"HH:mm:ss")
            var t_name = t_json.name

            var t_obj = {
                itemId:t_no,
                itemTime:t_time,
                itemName:t_name
            }

            id_listModel.insert(0,t_obj)

        }



    }

    Column{
        id: id_container
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 3
        Repeater{
            id: id_repeater
            model: id_listModel

            Item{

                width: 100
                height: 40
                Rectangle{
                    anchors.fill: parent
                    color:UI.COLOR_BASE_YELLOW_DARK
                }

                Column{
                    anchors.fill: parent
                    anchors.margins: 2
                    spacing: 2
                    XmsText{
                        text: itemName
                        color:UI.COLOR_BASE_WHITE
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                    XmsText{
                        text:itemTime
                        color:UI.COLOR_BASE_WHITE
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                }
            }
        }

    }

    ListModel{
        id: id_listModel
        ListElement{
            itemId:001
            itemTime:"001"
            itemName:"sdfsdf"
        }
    }

    Component.onCompleted: id_listModel.clear()

}
