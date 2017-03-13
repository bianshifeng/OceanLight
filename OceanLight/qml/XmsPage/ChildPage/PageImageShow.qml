import QtQuick 2.5
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import Xms.Server 1.0

import "../../Controls"
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as UIFont
import "../../Fonts"
import "../BaseCom"



Item {
    id: id_root
    property alias itemName: id_txt_name.text
    property alias itemImageUrl:id_alg_image.source
    property alias itemInfo: id_txt_info.text


    signal emitClose()

    Rectangle{
        anchors.fill: parent
        opacity: 0.7
        color:UI.app_color_page_window_backcolor
    }

    signal emitShowHomePage()
    signal emitShowCameraPage()
    signal emitShowPricePage()
    signal emitShowHelpPage()

    BaseBorder{
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 520
        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 20
            XmsText{
                id: id_txt_name
                size: 32
                XmsText{
                    id: id_txt_info
                    anchors.left: parent.right
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 20
                    size: 20
                }
            }
            Image {
                id: id_alg_image
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.fillHeight: true
            }




            Row{
                spacing: 1
                anchors.horizontalCenter: parent.horizontalCenter


                MainMenuButton{
                    enabled: AlgServer.isPfrActive
                    isCheckedBt:false
                    opacityHover: 0.5
                    opacityClick: 0.8
                    opacityNormal:0.3
                    width: 120
                    height: 34
                    size: 12
                    sizeIcon: 14
                    icon: UIFont.ICON_ALG_FACE
                    isShowLine: true
                    text: qsTr("Register")
                    normalColor:UI.COLOR_BASE_ORANGE
                    foreColor: UI.COLOR_BASE_WHITE_BASE
                    hoverColor: UI.COLOR_BASE_RED
                    onClicked: {
                        //注册                        
                         AlgServer.push_pfr_imageFrame(id_root.itemName,id_root.itemImageUrl,0);
                    }
                }
                MainMenuButton{
                    isCheckedBt:false
                    opacityHover: 0.5
                    opacityClick: 0.8
                    opacityNormal:0.3
                    width: 120
                    height: 34
                    size: 12
                    sizeIcon: 14
                    icon: UIFont.ICON_ACTION_SAVE
                    isShowLine: true
                    text: qsTr("Save")

                    normalColor:UI.COLOR_BASE_ORANGE
                    foreColor: UI.COLOR_BASE_WHITE_BASE
                    hoverColor: UI.COLOR_BASE_RED
                    onClicked: {
                        emitShowCameraPage()
                    }
                }
            }
        }



        FlatButton{
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 8
            width: 40
            height: 30
            icon:UIFont.ICON_ACTION_CLOSE
            sizeIcon: 18
            onClicked: {
                emitClose()
            }

        }
    }


}
