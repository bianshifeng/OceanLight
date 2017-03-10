import QtQuick 2.7
import QtQuick.Controls 2.0
import "../../Controls"
import "../../Fonts"
import "../../Controls/UIConstants.js" as UI


Item{
    id: id_root
    implicitHeight: 64
    implicitWidth: 170
    property alias title:id_title.text
    property alias detail:id_detail.text
    property string stateSimply:"simply"
    property string stateNormal:"normal"
    property alias isCheckedBt:id_back.isCheckedBt
    property alias checked:id_back.checked

    property alias normalColor:id_back.normalColor
    property alias hoverColor:id_back.hoverColor
    property alias selectColor:id_back.selectColor

    property alias exclusiveGroup: id_back.exclusiveGroup

    state: "normal"
    signal clicked()
    ControlCard {
        id: id_back
        isCheckedBt:true
        anchors.fill: parent

    }

    Column{
        id: id_content
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
        }
    }


    XmsText{
        id: id_only_title
        text: id_root.title
        color:UI.COLOR_BASE_WHITE
        anchors.centerIn: parent
    }

    Rectangle{
        id: id_radio
        width: 12
        height: 12
        radius: 6
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        border.color: UI.COLOR_BASE_WHITE
        border.width: 1
        color:id_root.checked ? UI.COLOR_BASE_WHITE : UI.COLOR_BASE_TRANSPARENT
    }

    states: [
        State {
            name: id_root.stateSimply
            PropertyChanges {
                target: id_radio
                visible:false
            }
            PropertyChanges {
                target: id_content
                visible:false
            }
            PropertyChanges {
                target: id_only_title
                visible:true
            }
        },
        State {
            name: id_root.stateNormal
            PropertyChanges {
                target: id_radio
                visible:true
            }
            PropertyChanges {
                target: id_content
                visible:true
            }
            PropertyChanges {
                target: id_only_title
                visible:false
            }
        }
    ]


    XmsMouseArea{
        anchors.fill: parent
        hoverEnabled:false
        onClicked: {
            if(isCheckedBt){
                id_root.checked = true
            }else{
                id_root.checked = false
            }
            id_root.clicked()

        }
    }


}

