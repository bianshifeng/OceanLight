import QtQuick 2.7
import QtQuick.Controls 2.1
import QtMultimedia 5.5
import "../BaseCom"

Pane {
    id: pane
    readonly property int itemWidth: Math.max(slider.implicitWidth, Math.min(slider.implicitWidth * 2, pane.availableWidth / 3))

    Rectangle{
        anchors.fill: parent
        anchors.margins: 20

        QtPlayer{

        }

    }

}
