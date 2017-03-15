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

    property string itemMetaName:itemName
    property string itemMetaImageUrl:itemImageUrl


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




            Item{
                Layout.fillWidth: true
                height: 70

                Rectangle{
                    radius: 2
                    anchors.fill:id_input
                    anchors.margins: -8
                    Rectangle{
                        radius: 2
                        anchors.fill: parent
                        border.width: 1
                        border.color: UI.COLOR_BASE_BLACK_BASE
                        anchors.margins: 1
                    }
                }

                XmsText{
                    text: "Name Tag:"
                    anchors.left: id_input.left
                    anchors.bottom: id_input.top
                    anchors.leftMargin: -8
                    anchors.bottomMargin: 12
                    size: 16

                }

                TextInput{
                    id: id_input
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin:  8
                    anchors.rightMargin:  8

                    font.pixelSize: 16
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20

                }
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

                        if(id_input.text){
                            id_reg_busying.running = true
                             AlgServer.push_pfr_imageFrame(id_input.text,id_root.itemImageUrl,0);
                        }


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



        Item{
            anchors.fill: parent
            anchors.margins: 2
            visible: id_reg_busying.running
            Rectangle{
                anchors.fill: parent
                color:UI.COLOR_BASE_GREY_ACTIVE
                opacity: 0.5
            }

            BusyIndicator{
                id: id_reg_busying
                running: false
                anchors.centerIn: parent
            }
        }


        Rectangle{
            id: id_info_page
            opacity:0
            width: 200
            height: 80
            Rectangle{
                anchors.fill: parent
                anchors.margins: 1
                color:UI.COLOR_BASE_TRANSPARENT
                border.color: UI.COLOR_BASE_WHITE_LIGHT
                border.width: 1
            }

            anchors.centerIn: parent
            XmsText{
                id: id_reg_info
                size: 16
                anchors.centerIn: parent
            }
            Timer{
                id:id_timer
                repeat: false
                interval: 3000
                onTriggered: {
                    id_info_page.opacity = 0
                }
            }
            function showInfo(message){
                if(message === "1"){
                    id_reg_info.text = "Register Success"
                    id_info_page.color = UI.COLOR_BASE_GREEN
                }else{
                    id_reg_info.text = "register Failture"
                    id_info_page.color = UI.COLOR_BASE_RED
                }

                id_timer.restart()
                id_info_page.opacity = 1

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

    Connections{
        id: id_algserver_cnt
        target: AlgServer
        ignoreUnknownSignals: true
        onSig_alg_pfr_reg_data: {
            id_reg_busying.running = false
            id_info_page.showInfo(message)
        }

    }


}
