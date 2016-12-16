import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "../../Controls"
import "../../Fonts"
import "../BaseCom"
import "../../Controls/UIConstants.js" as UI
import "../../Services"
import "../../Fonts/XmsIconFont.js" as FontName
import "./AlgPage/CPCPage"
import Xms.Alg 1.0

Flickable {
    id: id_root
    property string algId:"bianshifeng"
    contentHeight: id_container.height

    AlgCPC{
        id: id_alg

    }
    GridLayout{
        id: id_container
        width: parent.width
        columns: 3
        columnSpacing: 2
        rowSpacing: 2
        FlatPageTitleBar{
            id: id_title_bar
            pageTitle:"CPC算法是一种在室内进行人数统计的算法：能够完成人员出入统计工作。"
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: id_title_bar.height

            FlatButton{
                id: id_bt_more
                width: 70
                hideTextWidth: 60
                height: 44
                sizeIcon:12
                anchors.right: id_bt_reset.left
                anchors.bottom: parent.bottom
                icon:FontName.ICON_ACTION_SPY
                text: qsTr("详情")
                onClicked: id_container.state =(id_container.state=== "expandState" ? "normalState":"expandState")
            }
            FlatButton{
                id: id_bt_reset
                width: 100
                hideTextWidth: 60
                height: 44
                sizeIcon:12
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                icon:FontName.ICON_ACTION_ADD
                text: qsTr("添加算法")
            }

        }
        FlatItemTitleBar{
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
                    id: id_bt_getconfig
                    height: parent.height
                    width: 70
                    hideTextWidth: 70
                    icon:FontName.ICON_ACTION_DETAIL
                    normalColor: UI.COLOR_BASE_WHITE
                    text: qsTr("查看")
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
                    text: qsTr("保存")
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

                    text: qsTr("删除")
                }

            }

        }
        FlatCheckButton{
            title: qsTr("获取算法参数")
            Layout.fillWidth: true
            onClicked: {
                id_algWorker.getAlgConfig()
            }
        }
        FlatCheckButton{
            title: qsTr("修改算法参数")
            Layout.fillWidth: true
            onClicked: {
                id_algWorker.setAlgConfig()
            }
        }
        FlatCheckButton{
            title: qsTr("启动算法")
            Layout.fillWidth: true
            onClicked: {
                id_algWorker.startAlg()
            }
        }
        FlatCheckButton{
            title: qsTr("停止算法")
            Layout.fillWidth: true
            onClicked: {
                id_algWorker.stopAlg()
            }
        }

        FlatLevelSelectCtrl{
            title: qsTr("miangandu")
            detail: qsTr("the density is for alg no")
            Layout.fillWidth: true
        }

        DrawAlgParamCom{
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.fillHeight: true
        }





    }


    WorkerScriptAlgDetail{
        id: id_algWorker

    }


    ScrollIndicator.vertical: ScrollIndicator { }
}
