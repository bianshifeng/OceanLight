import QtQuick 2.0
import Bian 1.0
import "../../Controls"
import QtMultimedia 5.5
import Xms.Server 1.0


Item{
    id: id_root
    property alias mediaUrl: id_player.source
    implicitWidth: 960
    implicitHeight: 540

    VideoOutput{
        id: id_output
        width: 960
        height: 540
        anchors.centerIn: parent
        source: id_player
    }

    FFmpegPlayer{
        id: id_player
    }



    function play(){
        id_player.play()
    }


//    CameraFilter{
//        id: id_cameraFilter
//        objectName: "cameraFilterObject"
//    }



}


