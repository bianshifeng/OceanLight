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
        icon: FontName.ICON_BASE_CHART
        isShowLine: true
        text: qsTr("首页")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
             emitShowHomePage()
        }
    }
    MainMenuButton{
        exclusiveGroup: id_group
        width: 120
        height: 34
        size: 12
        sizeIcon: 14
        icon: FontName.ICON_ACTION_DETAIL
        isShowLine: true
        text: qsTr("监控")
        foreColor: UI.COLOR_BASE_WHITE_BASE
        hoverColor: UI.COLOR_BASE_ORANGE
        onClicked: {
            emitShowCameraPage()
        }
    }

}
