﻿import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0
import Bian 1.0

VideoOutput {
    id: id_root
    implicitWidth: 960
    implicitHeight: 540
    property alias cameraId: id_camera.deviceId
    focus : visible // to receive focus and capture key events when visible
    source: id_camera
    Camera{
         id: id_camera
         captureMode: Camera.CaptureViewfinder
         viewfinder.resolution:"960x540"     //"1920x1080"
     }

    function play(){
        id_root.filters = [id_cameraFilter]
    }

    CameraFilter{
        id: id_cameraFilter
        objectName: "cameraFilterObject"
    }


}
