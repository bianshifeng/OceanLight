import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import "../BaseCom"
import "../../Controls"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as UIFont
import "../../Fonts"
import "../MediaCom"


BasePage{
    id:id_root
    FlatPageTitleBar{
        id: id_title_bar
        pageTitle:"Video Manager Page"
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
            icon:UIFont.ICON_ACTION_ADD
            text: qsTr("Add")
            onClicked: id_dlg.open()
            //onClicked: id_container.state =(id_container.state=== "expandState" ? "normalState":"expandState")
        }

        Dialog{
            id: id_dlg
            standardButtons: StandardButton.Save | StandardButton.Cancel
            modality: Qt.ApplicationModal
            title: qsTr("Add media url")
            width: 400
            height: 150

            XmsFontLoader{
                id: id_fonter

            }

            Item{
                anchors.fill: parent
                anchors.margins: 5


                Text {
                    id: id_rtsp_name_txt
                    text: qsTr("RTSP Name:")
                    font.family: id_fonter.name
                    font.pixelSize: id_fonter.fontSize
                    anchors.top: parent.top
                    anchors.topMargin: 16

                }

                Item{
                    anchors.left: id_rtsp_name_txt.right
                    anchors.right: parent.right
                    anchors.verticalCenter: id_rtsp_name_txt.verticalCenter
                    height: 30
                    Rectangle{
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1
                    }

                    TextInput{
                        id: id_rtsp_name_input
                        font.family: id_fonter.name
                        font.pixelSize: id_fonter.fontSize
                        anchors.fill: parent
                        anchors.margins: 3
                        text: "bianshifeng"
                    }

                }

                Text {
                    id: id_rtsp_url_txt
                    text: qsTr("RTSP Url:")
                    font.family: id_fonter.name
                    font.pixelSize: id_fonter.fontSize
                    anchors.right: id_rtsp_name_txt.right
                    anchors.top: id_rtsp_name_txt.bottom
                    anchors.topMargin: 30


                }

                Item{
                    anchors.left: id_rtsp_url_txt.right
                    anchors.right: parent.right
                    anchors.verticalCenter: id_rtsp_url_txt.verticalCenter
                    height: 30
                    Rectangle{
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1
                    }

                    TextInput{
                        id: id_rtsp_url_input
                        font.family: id_fonter.name
                        font.pixelSize: id_fonter.fontSize
                        anchors.fill: parent
                        anchors.margins: 3
                        text: "rtsp://localhost:8554/url"
                    }

                }


            }

            onAccepted:  {

                if(id_rtsp_name_input.text && id_rtsp_url_input.text)
                {
                    console.log("00000000000000000000000000000000000")
                    var jsonObj ={}
                    jsonObj.itemName=id_rtsp_name_input.text
                    jsonObj.itemId="rtsp_001"
                    jsonObj.itemValue=id_rtsp_url_input.text
                    id_app_data.addMedia(jsonObj)

                }

            }

        }
    }


    Column{
        Layout.columnSpan: id_root.columns
        Layout.fillWidth: true
        spacing: 2
        ExclusiveGroup{
            id: id_itemGroup
        }

        Repeater{
            id: id_camera_repeater
            model: id_app_data.videoListModel

            CameraConfigCom{
                exclusiveGroup: id_itemGroup
                anchors.left: parent.left
                anchors.right: parent.right
                cameraTitle: itemName
                cameraLogo: UIFont.ICON_BASE_VIDEOCAM
                cameraTitleColor:UI.COLOR_BASE_BLUE_LIGHT
                cameraInfo: itemValue
                isSelected: id_app_window.mediaSource === itemValue
                onEmitCameraActive: {
                    id_app_window.mediaType=200
                    id_app_window.mediaSource =itemValue
                }

            }

        }


    }


}
