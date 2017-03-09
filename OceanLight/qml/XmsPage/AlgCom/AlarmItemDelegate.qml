import QtQuick 2.5
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils

Item{
    implicitWidth: 200
    implicitHeight: 120

    property alias imageUrl : id_alarm_image.source
    property alias nameStr:id_txt_name.text
    property alias timeStr:id_txt_time.text
    Rectangle{
        anchors.fill: parent
        color:UI.COLOR_BASE_YELLOW_DARK
    }

    Column{
        id: id_col
        anchors.fill: parent
        anchors.margins: 2
        spacing: 2
        Image{
            id: id_alarm_image
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.right: parent.right
            height: 80
        }

        XmsText{
            id: id_txt_name
            color:UI.COLOR_BASE_WHITE
            anchors.left: parent.left
            anchors.right: parent.right
        }
        XmsText{
            id: id_txt_time
            color:UI.COLOR_BASE_WHITE
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
