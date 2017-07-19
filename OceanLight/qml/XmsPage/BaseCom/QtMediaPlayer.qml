import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0
import Bian 1.0

VideoOutput {
    id: id_root
    implicitWidth: 960
    implicitHeight: 540
    property alias mediaUrl: id_player.source
    focus : visible // to receive focus and capture key events when visible
    source: id_player
    MediaPlayer{
         id: id_player
         autoLoad: true
     }

    function play(){
        id_root.filters = [id_cameraFilter]
        id_player.play()
    }

    VideoOutput{
        width: 300
        height: 200
        anchors.centerIn: parent
        source: id_player
    }

    CameraFilter{
        id: id_cameraFilter
        objectName: "cameraFilterObject"
    }


}
