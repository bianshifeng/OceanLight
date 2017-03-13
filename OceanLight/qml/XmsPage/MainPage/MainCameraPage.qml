import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI
import "../BaseCom"
import "../AlgCom"
import "../ChildPage"
import "../../Controls"

//import "./CameraCanvas"
//    CanvasFrame{
//        anchors.fill: parent
//    }


Item {
    id: id_root
    implicitHeight: 500
    implicitWidth: 600

    Rectangle{
        anchors.fill: parent
        color:"black"
    }







    VideoOutput {
        id: id_camera_output
        source: id_mediaPlayer
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: id_alg_message.left
        focus : visible // to receive focus and capture key events when visible
        filters: [id_cameraFilter]
//        fillMode: VideoOutput.Stretch


        MediaPlayer{
            id: id_mediaPlayer
            autoLoad: true
            autoPlay: true
            source:"file:///g:/video2.mp4"
        }
        Camera {
             id: id_camera
             captureMode: Camera.CaptureViewfinder
             viewfinder.resolution:"960x540"     //"1920x1080"
         }

        CameraFilter{
            id: id_cameraFilter
            objectName: "cameraFilterObject"
        }

    }


    Image {
        id: id_photoPreview
        width: 150
        height: 100
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        visible: false

        MouseArea{
            anchors.fill: parent
            onClicked: id_camera.imageCapture.capture()
        }


        XmsText{
            id: id_txt_image
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -(id_txt_image.contentHeight+6)
            color: "white"
        }
    }




    Row{
        id: id_alg_message
        spacing: 1
        anchors.right:  parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // alg ipd
        Row{
            id: id_ipd_result_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 1
            Item{
                visible: id_info_ipd.isChecked
                width: 200
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                clip: true
                Rectangle{
                    anchors.fill: parent
                    opacity: 0.2
                }
                IPDListView{
                    id: id_ipd_listView
                    anchors.fill: parent

                    onEmitShowDetailInfo: {
                        //nameStr,var imageUrl,var timeStr
                        id_image_loader.showItem(nameStr,imageUrl,timeStr)

                    }
                }

            }
            FlatItemTitleBar_Vertical{
                id: id_info_ipd
                logo: FontName.ICON_ALG_RING
                logoColor:  id_ipd_listView.alarmCount >0 ? UI.COLOR_BASE_RED_LIGHT:UI.COLOR_BASE_YELLOW_BASE
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                info: id_ipd_listView.alarmCount
                MouseArea{
                    anchors.fill: parent
                    onClicked:id_info_ipd.isChecked = id_info_ipd.isChecked ? false : true

                    FlatButton{
                        text: "add"
                        visible: false
                        anchors.left: parent.left
                        anchors.right: parent.right
                        onClicked:{
                            id_ipd_listView.appendItem("{\"name\":\"IPD\",\"status\":\"warning\"}")
                        }
                        anchors.centerIn: parent
                    }
                }


            }
        }
        //alg vfd
        Row{
            id:id_vfd_result_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 1
            Item{
                visible: id_info_vfd.isChecked
                width: 200
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                clip: true
                Rectangle{
                    anchors.fill: parent
                    opacity: 0.2
                }
                VFDListView{
                    id: id_vfd_listView
                    anchors.fill: parent

                    onEmitShowDetailInfo: {
                        //nameStr,var imageUrl,var timeStr
                        id_image_loader.showItem(nameStr,imageUrl,timeStr)

                    }
                }

            }
            FlatItemTitleBar_Vertical{
                id: id_info_vfd
                logo: FontName.ICON_ALG_FACE

                logoColor:  UI.COLOR_BASE_YELLOW_BASE
                info: id_vfd_listView.alarmCount
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                MouseArea{
                    anchors.fill: parent
                    onClicked:id_info_vfd.isChecked = id_info_vfd.isChecked ? false : true
                }

            }
        }


    }





    Loader{
        id: id_image_loader
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: id_alg_message.left
        property string loaderItemName
        property string loaderItemInfo
        property string itemUrl

        function showItem(imgName,imgUrl,imgInfo){
            id_image_loader.sourceComponent = id_image_com
            id_image_loader.item.itemName = imgName
            id_image_loader.item.itemImageUrl = imgUrl
            id_image_loader.item.itemInfo = imgInfo

        }

        Component{
            id: id_image_com
            PageImageShow{
                onEmitClose: {
                    id_image_loader.sourceComponent = undefined;
                }
            }
        }
    }


    Connections{
        id: id_cnt
        target: AlgServer
        onSig_alg_test_data:{
            //id_txt_image.text = message;
            //id_camera.imageCapture.capture()
        }

        onSig_alg_ipd_data:{
            id_ipd_listView.appendItem(message)
        }

        onSig_alg_vfd_data:{
            id_vfd_listView.appendItem(message)
        }
        onIsIpdActiveChanged: {
            id_ipd_result_panel.visible = AlgServer.isIpdActive
        }
        onIsVfdActiveChanged: {
            id_vfd_result_panel.visible = AlgServer.isVfdActive
        }
    }

    Component.onCompleted: {
        id_ipd_result_panel.visible = AlgServer.isIpdActive
        id_vfd_result_panel.visible = AlgServer.isVfdActive
    }

}
