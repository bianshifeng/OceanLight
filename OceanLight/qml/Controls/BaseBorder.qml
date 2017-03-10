import QtQuick 2.0
import "./UIConstants.js" as UI

Rectangle{
    border.color:UI.app_page_base_color_border
    border.width: 1
    color:UI.app_page_base_color_border
    Rectangle{
        anchors.fill: parent
        anchors.margins: 1
        border.color: UI.app_page_base_color_border_inner
        border.width: 1
        color:UI.COLOR_BASE_TRANSPARENT
    }

}
