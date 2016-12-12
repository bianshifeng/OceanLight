import QtQuick 2.4
import "./UIConstants.js" as UI
import QtQuick.Controls 1.2

Item {
    id: id_root
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



    implicitHeight: 80
    implicitWidth: 240
    default property alias content: id_container.children
    Item{
        anchors.fill: parent
        Rectangle{
            id: id_back_normal
            anchors.fill: parent
            opacity: 0.1
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
                opacity: 0.3
            }
        },
        State {
            name: id_root.stateSelect

            PropertyChanges {
                target: id_back_select
                opacity: 0.3
            }
        },
        State {
            name: id_root.stateDisable

            PropertyChanges {
                target: id_back_disable
                opacity: 0.5
            }
        },
        State {
            name: id_root.stateChecked

            PropertyChanges {
                target: id_back_select
                opacity: 0.5
            }
        }

    ]
    transitions: Transition {
         NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad }
    }


}

