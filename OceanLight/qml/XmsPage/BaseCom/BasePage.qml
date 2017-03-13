import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as UIFont
import "../../Controls"
import "../../Fonts"

Flickable {
    id: flickable
    property alias columns: id_container.columns
    default property alias content:id_container.children
    contentHeight: id_container.height
    ScrollIndicator.vertical: ScrollIndicator { }
//    Rectangle{
//        anchors.fill: parent
//        color:UI.app_color_page_child_backcolor
//    }

    GridLayout{
        id: id_container
        width: parent.width
        columns: 3
        columnSpacing: 2
        rowSpacing: 2
    }
}
