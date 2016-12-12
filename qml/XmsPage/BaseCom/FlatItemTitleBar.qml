import QtQuick 2.7
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI


Item{
    id: id_root
    height: 48
    implicitWidth: 500
    property color fontColor: UI.COLOR_BASE_WHITE_LIGHT
    property alias title:id_title_text.text
    property alias info:id_detail_text.text
    property alias logo:id_logo.text
    ControlCard {
        id: id_main_body
        anchors.left: parent.left
        anchors.right:id_title_bt.visible ? id_title_bt.left:parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        XmsIcon{
            id: id_logo
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: parent.verticalCenter
            size: 20
            text: FontName.ICON_DEVICE_CAMERA
        }
        Column{
            anchors.left: id_logo.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            XmsText{
                id: id_title_text
                text:qsTr("Camera1")
                font.bold: true
                size: 12
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
    FlatButton{
        id: id_title_bt
        width: 70
        hideTextWidth: 70
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        icon:FontName.ICON_ACTION_SPY
        normalColor: id_main_body.normalColor
        text: qsTr("查看")
    }
}

