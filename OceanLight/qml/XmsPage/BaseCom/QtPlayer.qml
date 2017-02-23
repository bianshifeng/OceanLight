import QtQuick 2.7
import QtMultimedia 5.5

VideoOutput {
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
