import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI


Item {
    id: id_root
    implicitWidth: 500
    implicitHeight: 44
    property alias pageTitle:id_title_text.text
    Rectangle{
        anchors.fill: parent
        color:UI.app_color_page_window_backcolor
    }

    Flickable{
        id: id_content
        ScrollIndicator.vertical: ScrollIndicator { }
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        contentHeight: id_title_text.height

        XmsText{
            id: id_title_text
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.right: parent.right
            anchors.rightMargin: 30
            opacity: 0.8
            size: 12
            text:qsTr("ipc 相机是一种可以集成智能算法的相机，/n /\r你可以用来显示和设置算法。")
            color:UI.COLOR_BASE_WHITE
        }

    }

    FlatButton{
        id: id_bt_more
        width: 70
        hideTextWidth: 60
        height: 44
        sizeIcon:12
        anchors.right: id_bt_reset.left
        anchors.bottom: parent.bottom
        icon:FontName.ICON_ACTION_SPY
        text: qsTr("详情")
        onClicked: id_root.state =(id_root.state=== "expandState" ? "normalState":"expandState")
    }
    FlatButton{
        id: id_bt_reset
        width: 70
        hideTextWidth: 60
        height: 44
        sizeIcon:12
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        icon:FontName.ICON_ACTION_REDO
        text: qsTr("重置")
    }



    states: [
        State {
            name: "normalState"
            PropertyChanges {
                target: id_root
                height:44
            }
            PropertyChanges {
                target: id_title_text
                wrapMode:Text.NoWrap
            }
            PropertyChanges {
                target: id_content
                anchors.bottomMargin: 10
            }
        },
        State {
            name: "expandState"
            PropertyChanges {
                target: id_root
                height:150
            }
            PropertyChanges {
                target: id_title_text
                wrapMode:Text.WordWrap
            }
            PropertyChanges {
                target: id_content
                anchors.bottomMargin: 56
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                target: id_root
                properties: "x,y";
                easing.type: Easing.InOutQuad
            }
        }
    ]
}

