import QtQuick 2.4
import "./UIConstants.js" as UI
import QtQuick.Controls 1.2

Item {
    id: id_root
    implicitHeight: 80
    implicitWidth: 240
    default property alias content: id_container.children
    property double opacityNormal:0.1
    property double opacityHover:0.3
    property double opacityClick:0.3
    property double opacitySelect:0.5

    property alias showBackgroud:id_back.visible

    property string stateNormal:"normal"
    property string stateHover:"hover"
    property string stateSelect:"select"
    property string stateDisable:"disable"
    property string stateChecked:"checked"
    property color normalColor:"white"
    property color hoverColor:"white"
    property color selectColor:"white"

    property bool isCheckedBt:false
    property color disableColor:UI.COLOR_BASE_GRAY_DARK
    property bool isHovered: id_root.state === stateHover ? true : false
    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(id_root)
    }

    onCheckedChanged: {
        if(checked){
            id_root.state = id_root.stateChecked
        }else{
            id_root.state = id_root.stateNormal
        }

    }




    Item{
        id: id_back
        anchors.fill: parent
        Rectangle{
            id: id_back_normal
            anchors.fill: parent
            opacity: id_root.opacityNormal
            color:normalColor
        }
        Rectangle{
            id: id_back_hover
            opacity: 0
            anchors.fill: parent
            color:hoverColor
        }
        Rectangle{
            id: id_back_select
            opacity: 0
            color:selectColor
            anchors.fill: parent
        }
        Rectangle{
            id: id_back_disable
            opacity: 0
            color:disableColor
            anchors.fill: parent
        }
    }

    XmsMouseArea{
        anchors.fill: parent
        onEntered:{
            if(!id_root.checked)id_root.state = id_root.stateHover
        }
        onExited: {
            if(!id_root.checked)id_root.state = id_root.stateNormal
        }
        onPressed: {
            if(!id_root.checked)id_root.state = id_root.stateSelect
        }
        onReleased: {
            if(!id_root.checked)id_root.state = id_root.stateHover
        }
        Item{
            id: id_container
            anchors.fill: parent
        }
    }
    states: [
        State {
            name: id_root.stateNormal
        },
        State {
            name: id_root.stateHover

            PropertyChanges {
                target: id_back_hover
                opacity: id_root.opacityHover
            }
        },
        State {
            name: id_root.stateSelect

            PropertyChanges {
                target: id_back_select
                opacity: id_root.opacityClick
            }
        },
        State {
            name: id_root.stateDisable

            PropertyChanges {
                target: id_back_disable
                opacity: id_root.opacitySelect
            }
        },
        State {
            name: id_root.stateChecked

            PropertyChanges {
                target: id_back_select
                opacity: id_root.opacitySelect
            }
        }

    ]
    transitions: Transition {
         NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad }
    }


}

