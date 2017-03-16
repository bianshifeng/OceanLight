import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

VideoOutput {
    id: id_root
    implicitWidth: 960
    implicitHeight: 540
    source: id_camera
    focus : visible // to receive focus and capture key events when visible
    filters: [id_cameraFilter]
//        fillMode: VideoOutput.Stretch


//        MediaPlayer{
//            id: id_mediaPlayer
//            autoLoad: true
//            autoPlay: true
//            source:"file:///g:/video2.mp4"
//        }
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
