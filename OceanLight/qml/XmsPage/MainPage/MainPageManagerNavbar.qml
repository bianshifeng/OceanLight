import QtQuick 2.0
import QtQuick.Controls 1.2
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as FontName
import "../BaseCom"

Row{
    id: id_root
    spacing: 1

    signal emitShowHomePage()
    signal emitShowCameraPage()
    signal emitShowPricePage()
    signal emitShowHelpPage()
    signal emitShowWebInfoPage()

    ExclusiveGroup{
        id: id_group
    }

    MainMenuButton{
        exclusiveGroup: id_group
        checked: true
        width: 120
        height: 34
        size: 12
        sizeIcon: 14
        icon: FontName.ICON_BASE_HOME
        isShowLine: true
        text: qsTr("HOME")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
             emitShowHomePage()
        }
    }
    MainMenuButton{
        id: id_bt_monitor
        exclusiveGroup: id_group
        width: 120
        height: 34
        size: 12
        sizeIcon: 14
        icon: FontName.ICON_ALG_SPY
        isShowLine: true
        text: qsTr("MONITOR")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
            emitShowCameraPage()
        }
    }
    MainMenuButton{
        visible: false
        exclusiveGroup: id_group
        width: 120
        height: 34
        size: 12
        sizeIcon: 14
        icon: FontName.ICON_BASE_CHARTBAR
        isShowLine: true
        text: qsTr("PRICE")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
            emitShowPricePage()
        }
    }
    MainMenuButton{
        visible: true
        exclusiveGroup: id_group
        width: 120
        height: 34
        size: 12
        sizeIcon: 14
        icon: FontName.ICON_BASE_PEOPLE
        isShowLine: true
        text: qsTr("WEB")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
            emitShowWebInfoPage()
        }
    }

    function showMonitorPage(){
        id_bt_monitor.checked = true
        emitShowCameraPage()
    }
}
