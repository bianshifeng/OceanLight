import QtQuick 2.7
import QtGraphicalEffects 1.0
import "./UIConstants.js" as UI

MouseArea {
    id: id_root
    implicitHeight: 300
    implicitWidth: 500
    hoverEnabled: true

    Rectangle{
        id: id_panel
        anchors.fill: parent
        anchors.margins: 6
        color:UI.COLOR_BASE_TRANSPARENT
        border.color: UI.COLOR_BASE_WHITE
        border.width: 1
        Rectangle{
            anchors.fill: parent
            color:UI.COLOR_BASE_WHITE
            opacity: id_root.containsMouse ? 0.5: 0.2
        }

    }

}
