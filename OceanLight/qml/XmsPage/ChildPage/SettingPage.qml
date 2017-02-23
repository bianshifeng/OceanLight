import QtQuick 2.7
import QtQuick.Controls 2.0

Pane {
    id: pane

    readonly property int itemWidth: Math.max(slider.implicitWidth, Math.min(slider.implicitWidth * 2, pane.availableWidth / 3))

    Column {
        spacing: 40
        anchors.fill: parent

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "Slider is used to select a value by sliding a handle along a track."
        }

        Slider {
            id: slider
            value: 0.5
            width: itemWidth
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Slider {
            orientation: Qt.Vertical
            value: 0.5
            height: itemWidth
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
