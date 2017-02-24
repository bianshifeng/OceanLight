import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

import "../../Fonts"
import "../../Controls/UIConstants.js" as UI


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
        }
    }

    Camera {
         id: id_camera
         imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
         exposure {
             exposureCompensation: -1.0
             exposureMode: Camera.ExposurePortrait
         }
         flash.mode: Camera.FlashRedEyeReduction
         imageCapture {
             onImageCaptured: {
                 AlgServer.setCameraImage(preview)
                 AlgServer.setImage(preview)
                 id_photoPreview.source = preview
             }
         }
     }


    VideoOutput {
        source: id_camera
        anchors.fill: parent
        anchors.margins: 20
        focus : visible // to receive focus and capture key events when visible
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
        width: 200
        height: 100
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin:  40
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

}
