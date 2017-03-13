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

    property alias algLogo: id_title_bar.logo
    property alias algTitle:id_title_bar.title
    property alias algInfo:id_title_bar.info
    property alias algIsActive: id_ck_active.checked


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
        title:qsTr("人数统计算法001")
        info: "算法id：001；配置时间：2016-12-09；参数信息如下："
        Layout.columnSpan: id_container.columns
        Layout.fillWidth: true
        Layout.preferredHeight: height

        Row{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            spacing: 2
            FlatButton{
                id: id_ck_active
                isCheckedBt:true
                height: parent.height
                width: 70
                hideTextWidth: 70
                icon:checked ? FontName.ICON_ACTION_CHECK:FontName.ICON_ACTION_CHECKUN
                normalColor: UI.COLOR_BASE_WHITE
                selectColor: UI.COLOR_BASE_RED
                text: checked ? qsTr("run"):qsTr("stop")
            }
            FlatButton{
                id: id_bt_getconfig
                height: parent.height
                width: 70
                hideTextWidth: 70

                icon:FontName.ICON_ACTION_DETAIL
                normalColor: UI.COLOR_BASE_WHITE
                text: qsTr("Check")
                onClicked: {
                    id_algWorker.getAlgConfig()
                }
            }
            FlatButton{
                id: id_bt_saveConfig
                height: parent.height
                width: 70
                hideTextWidth: 70
                icon:FontName.ICON_ACTION_SAVE
                normalColor: UI.COLOR_BASE_WHITE
                text: qsTr("Save")
                onClicked: {
                    id_algWorker.setAlgConfig()
                }
            }
            FlatButton{
                id: id_bt_deleteConfig
                height: parent.height
                width: 70
                hideTextWidth: 70
                icon:FontName.ICON_ACTION_DELETE
                normalColor: UI.COLOR_BASE_WHITE
                foreColor:UI.COLOR_BASE_RED

                text: qsTr("Delete")
            }

        }

    }
    FlatCheckButton{
        visible: false
        exclusiveGroup: id_check_group
        title: qsTr("Start Alg")
        Layout.fillWidth: true
        onClicked: {
            emitAlgStart()
        }
    }
    FlatCheckButton{
        visible: false
        exclusiveGroup: id_check_group
        title: qsTr("Stop Alg")
        Layout.fillWidth: true
        onClicked: {
            id_algWorker.stopAlg()
        }
    }
}
