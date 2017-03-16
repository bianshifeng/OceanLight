import QtQuick 2.7
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI


Item{
    id: id_root
    width: 48
    implicitHeight: 500
    property alias fontColor:id_detail_text.color
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

        showBackgroud:false
        XmsIcon{
            id: id_logo
            anchors.top:  parent.top
            anchors.topMargin:  14
            anchors.horizontalCenter: parent.horizontalCenter
            size: 22
            text: FontName.ICON_DEVICE_CAMERA
            tooltip: id_root.tooltip
            opacity: id_main_body.isHovered ? 1: 0.8

            Rectangle{
                width: 36
                height: width
                radius: width/2
                border.width: 1
                border.color: id_logo.color
                color:UI.COLOR_BASE_TRANSPARENT
                anchors.centerIn: parent
                antialiasing: true
                smooth: true
            }

        }
        Column{
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            XmsText{
                id: id_title_text
                text:qsTr("NO")
                size: 12
                anchors.horizontalCenter: parent.horizontalCenter
                visible: false
            }
            XmsText{
                id: id_detail_text
                size: 16
                font.bold: true
                text:qsTr("12")
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

}
