import QtQuick 2.7
import QtAV 1.7

VideoOutput2 {
    id: id_root
    implicitHeight: 300
    implicitWidth: 400

    source: id_player
    property alias mediaAutoPlay: id_player.autoPlay
    property alias mediaUrl:id_player.source
    MediaPlayer{
        id: id_player
    }

}
