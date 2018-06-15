import QtQuick 2.7
import QtMultimedia 5.5
import Xms.Server 1.0

import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls/UIConstants.js" as UI
import "../BaseCom"
import "../AlgCom"
import "../ChildPage"
import "../../Controls"

//import "./CameraCanvas"
//    CanvasFrame{
//        anchors.fill: parent
//    }


Rectangle {
    id: id_root
    implicitHeight: 500
    implicitWidth: 600
    color:"black"

    Loader{
        id: id_player_loader
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onLoaded: {
            if(id_player_loader.item){
                item.play()
            }
        }
    }


    function loadCamera(cameraId){
        id_player_loader.setSource( "qrc:/qml/XmsPage/BaseCom/QtPlayer.qml",{"cameraId":cameraId})
    }

    function loadRtsp(rtspUrl){
        id_player_loader.setSource("qrc:/qml/XmsPage/BaseCom/AvPlayer.qml",{"mediaUrl":rtspUrl})
    }


    Component{
        id: id_loader_emptyPlayer_com
        Item{
            function play(){
                id_root.changePlayerSource()
            }



            Rectangle{
                height: 2
                width: id_root.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 16
                color: UI.COLOR_BASE_YELLOW_LIGHT
            }

            XmsText {
                text: qsTr("PLEASE ADD MEDIA SOURCE")
                anchors.centerIn: parent
                color: UI.COLOR_BASE_YELLOW_LIGHT
            }



        }
    }


    Row{
        id: id_alg_message
        spacing: 1
        anchors.right:  parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // alg ipd
        Row{
            id: id_ipd_result_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 1
            Item{
                visible: id_info_ipd.isChecked
                width: 160
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                clip: true
                Rectangle{
                    anchors.fill: parent
                    opacity: 0.2
                }
                IPDListView{
                    id: id_ipd_listView
                    anchors.fill: parent
                    onEmitShowDetailInfo: {
                        //nameStr,var imageUrl,var timeStr
                        id_image_loader.showItem(nameStr,imageUrl,timeStr,metaNameStr,metaImageUrl)
                    }
                }
            }
            FlatItemTitleBar_Vertical{
                id: id_info_ipd
                logo: FontName.ICON_ALG_RING
                logoColor:  id_ipd_listView.isWarning ? UI.COLOR_BASE_RED_LIGHT:UI.COLOR_BASE_YELLOW_LIGHT
                fontColor: id_ipd_listView.isWarning ? UI.COLOR_BASE_RED_LIGHT:UI.COLOR_BASE_YELLOW_LIGHT
                anchors.top: parent.top
                height: 60
                info: id_ipd_listView.alarmCount
                MouseArea{
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    onClicked:id_info_ipd.isChecked = id_info_ipd.isChecked ? false : true
                }
            }
        }
        //alg vfd
        Row{
            id:id_vfd_result_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 1
            Item{
                visible: id_info_vfd.isChecked
                width: 160
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                clip: true
                Rectangle{
                    anchors.fill: parent
                    opacity: 0.2
                }
                VFDListView{
                    id: id_vfd_listView
                    anchors.fill: parent
                    onEmitShowDetailInfo: {
                        //nameStr,var imageUrl,var timeStr
                        id_image_loader.showItem(nameStr,imageUrl,timeStr,metaNameStr,metaImageUrl)

                    }
                }

            }
            FlatItemTitleBar_Vertical{
                id: id_info_vfd
                logo: FontName.ICON_ALG_FACE
                logoColor:  UI.COLOR_BASE_YELLOW_LIGHT
                fontColor: UI.COLOR_BASE_YELLOW_LIGHT
                info: id_vfd_listView.alarmCount
                anchors.top: parent.top
                height: 60
                MouseArea{
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    onClicked:id_info_vfd.isChecked = id_info_vfd.isChecked ? false : true
                }

            }
        }


    }


    Loader{
        id: id_image_loader
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: id_alg_message.left
        property string loaderItemName
        property string loaderItemInfo
        property string itemUrl

        function showItem(imgName,imgUrl,imgInfo,metaImgName,metaImgUrl){
            id_image_loader.sourceComponent = undefined;

            id_image_loader.sourceComponent = id_image_com
            id_image_loader.item.itemName = imgName
            id_image_loader.item.itemImageUrl = imgUrl
            id_image_loader.item.itemInfo = imgInfo
            id_image_loader.item.itemMetaName = metaImgName
            id_image_loader.item.itemMetaImageUrl = metaImgUrl

        }

        Component{
            id: id_image_com
            PageImageShow{
                onEmitClose: {
                    id_image_loader.sourceComponent = undefined;
                }
            }
        }
    }





    Connections{
        id: id_cnt
        target: AlgServer
        ignoreUnknownSignals: true
        onSig_alg_test_data:{
            //id_txt_image.text = message;
            //id_camera.imageCapture.capture()
        }

        onSig_alg_ipd_data:{
            id_ipd_listView.appendItem(message)
        }

        onSig_alg_vfd_data:{
            id_vfd_listView.appendItem(message)
        }
        onIsIpdActiveChanged: {
            id_ipd_result_panel.visible = AlgServer.isIpdActive
        }
        onIsVfdActiveChanged: {
            id_vfd_result_panel.visible = AlgServer.isVfdActive
        }
    }


    function changePlayerSource(){
        if(id_app_window.mediaType===100){
            id_root.loadCamera(id_app_window.mediaSource)
        }
        if(id_app_window.mediaType===200){
            id_root.loadRtsp(id_app_window.mediaSource)
        }
    }
    Component.onCompleted: {
        id_ipd_result_panel.visible = AlgServer.isIpdActive
        id_vfd_result_panel.visible = AlgServer.isVfdActive
        id_player_loader.sourceComponent = id_loader_emptyPlayer_com
    }
}
