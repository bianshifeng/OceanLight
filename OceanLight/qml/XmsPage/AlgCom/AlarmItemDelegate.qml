import QtQuick 2.5
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Item{
    id: id_root
    implicitWidth: 200
    implicitHeight: 120

    property alias imageUrl : id_alarm_image.source
    property alias nameStr:id_txt_name.text
    property alias timeStr:id_txt_time.text


    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(id_root)
    }


    signal emitClick()
    Rectangle{
        anchors.fill: parent
        color:id_mouseArea.containsMouse?UI.COLOR_BASE_YELLOW_LIGHT:UI.COLOR_BASE_YELLOW_DARK
    }

    Rectangle{
        anchors.fill: parent
        visible: id_root.checked ? true: false
        border.color: UI.COLOR_BASE_WHITE
        border.width: 1
        color:UI.COLOR_BASE_TRANSPARENT
        opacity: 0.8
        anchors.margins: 1
    }

    ColumnLayout{
        id: id_col
        anchors.fill: parent
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.rightMargin: 8
        anchors.leftMargin: 8
        spacing: 2
        XmsText{
            id: id_txt_name
            color:UI.COLOR_BASE_WHITE
            anchors.left: parent.left
            anchors.right: parent.right

        }
        Image{
            id: id_alarm_image
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
            Layout.fillHeight: true
        }


        XmsText{
            id: id_txt_time
            color:UI.COLOR_BASE_WHITE
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }



    MouseArea{
        id: id_mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            id_root.checked = true
            emitClick()
        }

    }
}
