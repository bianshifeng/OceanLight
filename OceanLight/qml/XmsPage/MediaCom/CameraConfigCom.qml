import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import "../../Controls"
import "../../Fonts"
import "../BaseCom"
import "../../Controls/UIConstants.js" as UI
import "../../Services"
import "../../Fonts/XmsIconFont.js" as FontName


GridLayout{
    id: id_container

    property alias cameraLogo: id_title_bar.logo
    property alias cameraTitle:id_title_bar.title
    property alias cameraInfo:id_title_bar.info
    property alias cameraIsActive: id_ck_active.checked


    implicitWidth: 600
    columns: 3
    columnSpacing: 2
    rowSpacing: 2

    ExclusiveGroup{
        id: id_check_group
    }

    FlatItemTitleBar{
        id: id_title_bar
        logo: FontName.ICON_ALG_CPC
        title:qsTr("camera")
        info: "1920x1080"
        Layout.columnSpan: id_container.columns
        Layout.fillWidth: true
        Layout.preferredHeight: height

        Row{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            spacing: 2
            FlatButton{
                id: id_bt_getconfig
                height: parent.height
                width: 70
                hideTextWidth: 70
                icon:FontName.ICON_ACTION_DETAIL
                normalColor: UI.COLOR_BASE_WHITE
                text: qsTr("Info")
                onClicked: {
                    id_algWorker.getAlgConfig()
                }
            }


        }

    }
}
