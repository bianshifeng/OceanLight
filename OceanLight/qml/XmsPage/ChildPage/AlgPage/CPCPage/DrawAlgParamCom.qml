import QtQuick 2.7
import "../../../../Controls"
import "../../../../Controls/UIConstants.js" as UI
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item{
    id: id_root
    implicitWidth:  400
    implicitHeight: 300

    RowLayout{
        anchors.fill: parent
        spacing: 2
        ControlCard{
            Layout.fillHeight: true
            Layout.preferredWidth: 60
        }
        ControlCard{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Canvas{
                anchors.fill: parent
                anchors.margins: 10
                onPaint: {
                     var ctx = getContext("2d");
                     ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
                     ctx.fillRect(0, 0, width, height);
                 }
            }
        }
    }


}
