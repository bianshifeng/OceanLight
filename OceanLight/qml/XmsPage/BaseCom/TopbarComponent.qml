import QtQuick 2.7
import "../../Controls"
import "../../Fonts"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as FontName

Item {
    id: id_root
    anchors.left: parent.left
    anchors.right: parent.right
    implicitHeight: 40
    z:100
    signal emitFullScreen()

    XmsText{
        text: "OCEAN"
        size: 16
        color:UI.COLOR_BASE_WHITE
        font.bold: true
        opacity: 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 20
    }
    MouseArea {
        id: id_dragArea
        property point clickPos: "0,0"
        anchors.fill: parent
        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            //鼠标偏移量
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            //如果mainwindow继承自QWidget,用setPos
            g_window.setX(g_window.x+delta.x)
            g_window.setY(g_window.y+delta.y)
            //如果g_window是继承自QWindow，用moveWindow
            //g_window.moveWindow(g_window.x+delta.x,g_window.y+delta.y)
        }

    }


    Row{
        id: id_row
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 1
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 1
        FlatButton{
            width: 40
            height: 30
            icon:FontName.ICON_ACTION_SUB
            sizeIcon: 18
            onClicked: {
                g_window.showMinimized()
            }
        }
        FlatButton{
            id: id_normal_to_max
            width: 40
            height: 30
            visible: true
            icon:FontName.ICON_CAMERA_FULLSCREEM
            onClicked: {
                g_window.showMaximized()
                id_max_to_normal.visible = true
                id_normal_to_max.visible = false
            }

        }
        FlatButton{
            id:id_max_to_normal
            width: 40
            height: 30
            visible: false
            icon:FontName.ICON_CAMERA_FULLSCREEM
            onClicked: {
                //g_window.showNormal()
                //
                g_window.showFullScreen()
                id_max_to_normal.visible = false
                id_normal_to_max.visible = true
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
