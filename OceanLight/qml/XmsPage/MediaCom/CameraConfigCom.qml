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
    property color cameraTitleColor: UI.COLOR_BASE_YELLOW_DARK
    property alias cameraTitle:id_title_bar.title
    property alias cameraInfo:id_title_bar.info
    property alias exclusiveGroup: id_bt_getconfig.exclusiveGroup
    property alias isSelected: id_bt_getconfig.checked



    implicitWidth: 600
    columns: 3
    columnSpacing: 2
    rowSpacing: 2

    signal emitCameraActive()

    FlatItemTitleBar{
        id: id_title_bar
        logo: FontName.ICON_ALG_CPC
        fontColor:id_container.cameraTitleColor
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
                isCheckedBt: true
                height: parent.height
                width: 100
                hideTextWidth: 70
                icon: checked ?  FontName.ICON_ACTION_CHECK: FontName.ICON_ACTION_CHECKUN
                foreColor: id_container.cameraTitleColor
                text: qsTr("Active")
                opacitySelect: 0.1
                onClicked: {
                    emitCameraActive()
                }
            }
        }

    }
}
