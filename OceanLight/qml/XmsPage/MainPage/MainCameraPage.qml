import QtQuick 2.7
import QtMultimedia 5.5

Item {
    id: id_root
    implicitHeight: 500
    implicitWidth: 600

    Rectangle{
        anchors.fill: parent
        color:"black"
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
         }
     }


    VideoOutput {
        source: id_camera
        anchors.fill: parent
        anchors.margins: 20
        focus : visible // to receive focus and capture key events when visible
    }
    Image {
        id: id_photoPreview
    }

}
