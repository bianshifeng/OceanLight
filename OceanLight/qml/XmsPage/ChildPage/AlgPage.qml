import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Xms.Server 1.0

import "../../Controls"
import "../../Fonts"
import "../BaseCom"
import "../../Controls/UIConstants.js" as UI
import "../../Services"
import "../../Fonts/XmsIconFont.js" as FontName
import "./AlgPage/CPCPage"
import "../AlgCom"


Flickable {
    id: id_root
    property string algId:"bianshifeng"
    contentHeight: id_container.height

    GridLayout{
        id: id_container
        width: parent.width
        columns: 3
        columnSpacing: 2
        rowSpacing: 2
        FlatPageTitleBar{
            id: id_title_bar
            pageTitle:"Alg manaer"
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: id_title_bar.height

            FlatButton{
                id: id_bt_more
                width: 80
                hideTextWidth: 60
                height: 44
                sizeIcon:12
                anchors.right: id_bt_reset.left
                anchors.bottom: parent.bottom
                icon:FontName.ICON_ACTION_SPY
                text: qsTr("Detail")
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
                text: qsTr("Add")
            }

        }

        AlgConfigCom{
            id: id_config_ipd
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height

            algLogo: FontName.ICON_ALG_RING
            algTitle: "IPD: Indoor People Detection"
            algInfo: "This alg is for record the camera active people"
            onAlgIsActiveChanged: {
                AlgServer.setIsIpdActive(algIsActive)
            }

            Component.onCompleted: {
                id_config_ipd.algIsActive = AlgServer.isIpdActive
            }

        }
        AlgConfigCom{
            id: id_config_vfd
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height

            algLogo: FontName.ICON_ALG_PEA
            algTitle: "VFD: Video Face Detection"
            algInfo: "This alg is for record the camera active people"
            onAlgIsActiveChanged: {
                AlgServer.setIsVfdActive(algIsActive)
            }

            Component.onCompleted: {
                id_config_vfd.algIsActive = AlgServer.isVfdActive
            }


        }
        AlgConfigCom{
            id: id_config_pfr
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height

            algLogo: FontName.ICON_ALG_FACE
            algTitle: "PFR: People Face Recognition"
            algInfo: "This alg is for record the camera active people"
            Component.onCompleted: {
                id_config_pfr.algIsActive = AlgServer.isPfrActive
            }
        }
    }


    WorkerScriptAlgDetail{
        id: id_algWorker

    }


    ScrollIndicator.vertical: ScrollIndicator { }
}
