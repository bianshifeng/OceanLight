import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

VideoOutput {
    id: id_root
    implicitWidth: 960
    implicitHeight: 540
    source: id_camera
    property alias cameraId: id_camera.deviceId
    focus : visible // to receive focus and capture key events when visible
    Camera{
         id: id_camera
         captureMode: Camera.CaptureViewfinder
         viewfinder.resolution:"960x540"     //"1920x1080"
     }

//    CameraFilter{
//        id: id_cameraFilter
//        objectName: "cameraFilterObject"
//    }

    function play(){
        id_root.filters = [id_cameraFilter]
    }


}
