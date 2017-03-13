import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../BaseCom"
import "../../Controls"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as UIFont

BasePage{
    id:id_root
    FlatPageTitleBar{
        id: id_title_bar
        pageTitle:"Setting page"
        Layout.columnSpan: id_root.columns
        Layout.fillWidth: true
        Layout.preferredHeight: id_title_bar.height

        FlatButton{
            id: id_bt_more
            width: 80
            hideTextWidth: 60
            height: 44
            sizeIcon:12
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            icon:UIFont.ICON_ACTION_SPY
            text: qsTr("Detail")
            //onClicked: id_container.state =(id_container.state=== "expandState" ? "normalState":"expandState")
        }

    }

}
