import QtQuick 2.7
import QtQuick.Controls 2.0
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../BaseCom"
import QtQuick.Layouts 1.3
import QtMultimedia 5.5

Flickable {
    id: flickable
    ScrollIndicator.vertical: ScrollIndicator { }
    contentHeight: id_container.height


//    Rectangle{
//        anchors.fill: parent
//        color:UI.app_color_page_child_backcolor
//    }

    GridLayout{
        id:id_container
        columns: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        FlatPageTitleBar{
            id: id_title_bar
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: id_title_bar.height
        }

        FlatItemTitleBar{
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height

        }


        Item{

            height: 500
            Layout.fillWidth: true
             Layout.columnSpan: id_container.columns


                VideoOutput{
                    id: id_output
                    width: 500
                    height: 300
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: id_player
                    XmsIcon{
                        anchors.centerIn: parent
                        text:FontName.ICON_PLAYER_PLAY
                        size:25

                    }
                    Camera {
                           id: id_player
                    }




                }



                Rectangle{
                    width: 600
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: id_output.bottom
                    anchors.topMargin: 10
                    height: 1
                    color:UI.COLOR_BASE_WHITE

                }



        }



    }







}
