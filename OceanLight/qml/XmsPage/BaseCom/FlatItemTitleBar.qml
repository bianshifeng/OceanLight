import QtQuick 2.7
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI


Item{
    id: id_root
    height: 48
    implicitWidth: 500
    property color fontColor: UI.COLOR_BASE_YELLOW_LIGHT
    property alias title:id_title_text.text
    property alias info:id_detail_text.text
    property alias logo:id_logo.text
    ControlCard {
        id: id_main_body
        anchors.left: parent.left
        anchors.right:parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        normalColor:"#3c4349"
        opacityNormal:1

        XmsIcon{
            id: id_logo
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            color: id_root.fontColor
            size: 24
            text: FontName.ICON_DEVICE_CAMERA
        }
        Column{
            anchors.left: id_logo.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            spacing: 2
            XmsText{
                id: id_title_text
                text:qsTr("Camera1")
                font.bold: true
                size: 14
                color:id_root.fontColor
            }
            XmsText{
                id: id_detail_text
                size: 10
                text:qsTr("sdsfsfsfdddddddddddddddddd")
                color:id_root.fontColor
            }
        }
    }

}

