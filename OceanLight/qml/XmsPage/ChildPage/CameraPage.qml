import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtMultimedia 5.5

import "../BaseCom"
import "../../Controls"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as UIFont

import "../MediaCom"

BasePage{
    id:id_root
    FlatPageTitleBar{
        id: id_title_bar
        pageTitle:"Camera & IPC Manager."
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
            text: qsTr("Active")


            //onClicked: id_container.state =(id_container.state=== "expandState" ? "normalState":"expandState")
        }
    }


    Column{
        Layout.columnSpan: id_root.columns
        Layout.fillWidth: true
        ExclusiveGroup{
            id: id_itemGroup
        }

        Repeater{
            id: id_camera_repeater
            model: id_camera_list

            CameraConfigCom{
                exclusiveGroup: id_itemGroup
                anchors.left: parent.left
                anchors.right: parent.right
                cameraTitle: displayName
                cameraLogo: UIFont.ICON_DEVICE_CAMERA
                cameraInfo: ""
                isSelected: id_app_window.mediaSource === deviceId
                onEmitCameraActive: {
                    id_app_window.mediaType=100
                    id_app_window.mediaSource =deviceId
                }

            }

        }

        ListModel{
            id: id_camera_list
            ListElement{
                deviceId:""
                displayName:""
                position:0
                orientation:0
            }
        }

    }


    Component.onCompleted: {
        id_camera_list.clear()
        id_camera_list.append(QtMultimedia.availableCameras)

    }

}
