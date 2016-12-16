import QtQuick 2.7
import QtQuick.Controls 2.0
import "../../Controls"
import "../../Fonts"
import "../../Controls/UIConstants.js" as UI

ControlCard {
    id: id_root
    isCheckedBt:true
    implicitHeight: 64
    implicitWidth: 170
    property alias title:id_title.text
    property alias detail:id_detail.text
    property int value:1
    onValueChanged: {
        id_root.refreshLevelValue()
    }

    signal clicked()
    Column{
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 3
        anchors.verticalCenter: parent.verticalCenter
        XmsText{
            id: id_title
            color:UI.COLOR_BASE_WHITE
            text:"title"
        }
        XmsText{
            id: id_detail
            color:UI.COLOR_BASE_WHITE
            size: id_title.size - 2
            opacity: 0.7
            text:"detial sdsdfsdfs"
        }
    }



    Row{
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 1

        FlatCheckButton{
            id: id_level_01
            state: stateSimply
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            isCheckedBt: true
            width: 30
            title: "1"
            onClicked: id_root.value = 1
            normalColor: UI.COLOR_BASE_BLUE_LIGHT
            hoverColor: UI.COLOR_BASE_BLUE_LIGHT
            selectColor:  UI.COLOR_BASE_BLUE_LIGHT

        }
        FlatCheckButton{
            id: id_level_02
            state: stateSimply
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            isCheckedBt: true
            width: 30
            title: "2"
            onClicked: id_root.value = 2
            normalColor: UI.COLOR_BASE_YELLOW_LIGHT
            hoverColor: UI.COLOR_BASE_YELLOW_LIGHT
            selectColor:  UI.COLOR_BASE_YELLOW_LIGHT
        }
        FlatCheckButton{
            id: id_level_03
            state: stateSimply
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            isCheckedBt: true
            width: 30
            title: "3"
            onClicked: id_root.value = 3
            normalColor: UI.COLOR_BASE_RED
            hoverColor: UI.COLOR_BASE_RED
            selectColor:  UI.COLOR_BASE_RED
        }
    }

    function refreshLevelValue(){
        if(id_root.value === 1){
            id_level_01.checked = true
            id_level_02.checked = false
            id_level_03.checked = false
        }
        if(id_root.value === 2){
            id_level_01.checked = true
            id_level_02.checked = true
            id_level_03.checked = false
        }
        if(id_root.value === 3){
            id_level_01.checked = true
            id_level_02.checked = true
            id_level_03.checked = true
        }
    }

    Component.onCompleted: id_root.refreshLevelValue()
}
