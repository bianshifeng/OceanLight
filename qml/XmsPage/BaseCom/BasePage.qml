import QtQuick 2.7
import QtQuick.Controls 2.0
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../BaseCom"
import QtQuick.Layouts 1.3

Flickable {
    id: flickable
    ScrollIndicator.vertical: ScrollIndicator { }
    contentHeight: pane.height

    Rectangle{
        anchors.fill: parent
        color:UI.app_color_page_child_backcolor
    }



    GridLayout{

        columns: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        FlatPageTitleBar{
            Layout.fillWidth: true
            Layout.preferredHeight: 48
        }

        XmsPanel{
            width: 433
            height: 300
        }
        XmsPanel{
            width: 433
            height: 300
        }
        XmsPanel{
            width: 433
            height: 300
        }

    }





}
