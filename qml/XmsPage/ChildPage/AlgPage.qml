import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "../../Controls"
import "../../Fonts"
import "../BaseCom"
import "../../Controls/UIConstants.js" as UI
import "../../Services"
import "../../Fonts/XmsIconFont.js" as FontName
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
        }
        FlatItemTitleBar{
            logo: FontName.ICON_ALG_CPC
            title:qsTr("人数统计算法001")
            info: "算法id：001；配置时间：2016-12-09；参数信息如下："
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height
        }

        Repeater{
            model: 10
            FlatCheckButton{
                text: qsTr("cpc config" + index)
                Layout.fillWidth: true
                onClicked: {
                    id_algWorker.requestAlgConfig()
                }
            }

        }


    }


    WorkerScriptAlgDetail{
        id: id_algWorker

    }


    Component.onCompleted: {
        id_algWorker.requestAlgConfig()

    }


    ScrollIndicator.vertical: ScrollIndicator { }
}
