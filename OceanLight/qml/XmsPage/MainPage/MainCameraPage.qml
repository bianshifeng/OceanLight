import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI
import "../BaseCom"

import "./CameraCanvas"


Item {
    id: id_root
    implicitHeight: 500
    implicitWidth: 600

    Rectangle{
        anchors.fill: parent
        color:"black"
    }

    Connections{
        id: id_cnt
        target: AlgServer
        onSig_alg_test_data:{
            id_txt_image.text = message;
            id_camera.imageCapture.capture()
        }
    }

    Camera {
         id: id_camera
         //deviceId: QtMultimedia.availableCameras[1].deviceId
         imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
         exposure {
             exposureCompensation: -1.0
             exposureMode: Camera.ExposurePortrait
         }
         captureMode: Camera.CaptureVideo
         flash.mode: Camera.FlashRedEyeReduction
         imageCapture{
             onImageCaptured: {
                 id_photoPreview.source = preview
             }
         }
     }

    CameraFilter{
        id: id_cameraFilter
        objectName: "cameraFilterObject"
    }


    VideoOutput {
        id: id_camera_output
        source: id_camera
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: id_alg_message.left
        anchors.margins: 20
        focus : visible // to receive focus and capture key events when visible
        filters: [id_cameraFilter]
    }
    Rectangle{
        anchors.fill: id_photoPreview
        border.color: "white"
        border.width: 2
        color:UI.COLOR_BASE_TRANSPARENT
        anchors.margins: -2
    }

    Image {
        id: id_photoPreview
        width: 150
        height: 100
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        onSourceChanged: {
            console.log(id_photoPreview.data)
        }

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
        spacing: 2
        anchors.right:  parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 2
        Item{
            visible: id_info_pea.isChecked
            width: 100
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Rectangle{
                anchors.fill: parent
                opacity: 0.2
            }
        }
        FlatItemTitleBar_Vertical{
            id: id_info_pea
            logo: FontName.ICON_ALG_PEA
            logoColor:  UI.COLOR_BASE_YELLOW_BASE
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            MouseArea{
                anchors.fill: parent
                onClicked:id_info_pea.isChecked = id_info_pea.isChecked ? false : true
            }
        }
        Item{
            visible: id_info_ring.isChecked
            width: 100
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Rectangle{
                anchors.fill: parent
                opacity: 0.2
            }
        }
        FlatItemTitleBar_Vertical{
            id: id_info_ring
            logo: FontName.ICON_ALG_RING
            logoColor:  UI.COLOR_BASE_YELLOW_BASE
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            MouseArea{
                anchors.fill: parent
                onClicked:id_info_ring.isChecked = id_info_ring.isChecked ? false : true
            }
        }

        Item{
            visible: id_info_face.isChecked
            width: 200
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            clip: true
            Rectangle{
                anchors.fill: parent
                opacity: 0.2
            }

            Flickable{
                anchors.fill: parent
                contentHeight: id_container.height

                Column{
                    id: id_container
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Repeater{
                        model: 20
                        Image{
                            width: 160
                            height: 120

                            source: id_photoPreview.source

                            XmsText{
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin:- contentHeight - 2
                                color:UI.COLOR_BASE_WHITE

                                text:"bianshifeng"
                            }
                        }

                    }
                }
            }
        }

        FlatItemTitleBar_Vertical{
            id: id_info_face
            logo: FontName.ICON_ALG_FACE

            logoColor:  UI.COLOR_BASE_YELLOW_BASE
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            MouseArea{
                anchors.fill: parent
                onClicked:id_info_face.isChecked = id_info_face.isChecked ? false : true
            }

        }
    }

    CanvasFrame{
        anchors.fill: parent
    }
}
