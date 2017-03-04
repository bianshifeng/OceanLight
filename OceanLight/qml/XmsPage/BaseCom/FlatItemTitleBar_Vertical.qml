import QtQuick 2.7
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI


Item{
    id: id_root
    width: 48
    implicitHeight: 500
    property color fontColor: UI.COLOR_BASE_WHITE_LIGHT
    property string tooltip:""
    property alias isChecked:id_main_body.checked
    property alias title:id_title_text.text
    property alias info:id_detail_text.text
    property alias logo:id_logo.text
    property alias logoColor:id_logo.color
    ControlCard {
        id: id_main_body
        anchors.left: parent.left
        anchors.right:parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        XmsIcon{
            id: id_logo
            anchors.top:  parent.top
            anchors.topMargin:  14
            anchors.horizontalCenter: parent.horizontalCenter
            size: 20
            text: FontName.ICON_DEVICE_CAMERA
            tooltip: id_root.tooltip

        }
        Column{
            anchors.bottom:  parent.bottom
            anchors.bottomMargin:  30
            anchors.horizontalCenter: parent.horizontalCenter
            XmsText{
                id: id_title_text
                text:qsTr("NO")
                size: 12
                color:id_root.fontColor
                anchors.horizontalCenter: parent.horizontalCenter
            }
            XmsText{
                id: id_detail_text
                size: 14
                font.bold: true
                text:qsTr("12")
                color:id_root.fontColor
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

}
