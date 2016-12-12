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
    property alias text:id_title.text
    signal clicked()

    XmsText{
        id: id_title
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color:UI.COLOR_BASE_WHITE
        text:"title"
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
