import QtQuick 2.7
import "../../Controls"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as FontName

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    implicitHeight: 33
    signal emitFullScreen()

    Row{
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 2
        spacing: 1
        FlatButton{
            width: 40
            height: 30
            icon:FontName.ICON_ACTION_SUB
            sizeIcon: 18
        }
        FlatButton{
            width: 40
            height: 30
            icon:FontName.ICON_CAMERA_FULLSCREEM
            onClicked: {
                emitFullScreen()
            }

        }
        FlatButton{
            width: 40
            height: 30
            icon:FontName.ICON_ACTION_CLOSE
            sizeIcon: 18
            onClicked: {
                Qt.quit()
            }

        }

    }



}
