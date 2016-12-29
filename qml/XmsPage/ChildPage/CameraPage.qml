import QtQuick 2.7
import QtQuick.Controls 2.0
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Fonts/XmsIconFont.js" as FontName
import "../BaseCom"
import QtQuick.Layouts 1.3
//import QtAV 1.7
import QtMultimedia 5.5

Flickable {
    id: flickable
    ScrollIndicator.vertical: ScrollIndicator { }
    contentHeight: id_container.height

    GridLayout{
        id:id_container
        columns: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 2
        anchors.rightMargin: 2

        FlatPageTitleBar{
            id: id_title_bar
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: id_title_bar.height
        }

        FlatItemTitleBar{
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.preferredHeight: height

        }
//        QtPlayer{
//            Layout.fillWidth: true
//            Layout.preferredHeight:200
//            mediaUrl: "http://cctv1.vtime.cntv.wscdns.com/live/no/13_/seg0/index.m3u8?uid=default&AUTH=9F0TuDQ4bEafPc6oswSFnYQYBEL+Fd1iDJ4JWHRUvsmTwJh6C+qzyZnRtasPh0NGlS0K0KiDqWqCyHCve0eemw=="

//            mediaAutoPlay: true
//        }
        QtPlayer{
            Layout.fillWidth: true
            Layout.preferredHeight:200
            mediaUrl: "http://202.108.17.129/v.cctv.com/flash/mp4video54/TMS/2016/08/20/29759cb329ea49aaafc174365ad7b9b0_h264200000nero_aac16-2.mp4"

            mediaAutoPlay: true


        }


//        QtPlayer{
//            Layout.fillWidth: true
//            Layout.preferredHeight:600
//            mediaUrl: "http://cctv2.live.cntv.dnion.com/live/cctv2hls_/index.m3u8?ptype=1&AUTH=WHum47ZcUVwuB5EfYgjjTo52RqCkct+cUL8yvO4QAHi2KtFaJPUWZkx/CAayvHHgXITBTlg0YlAOkvzXSWussQ=="

//            mediaAutoPlay: true
//        }



        Item{

            height: 500
            Layout.fillWidth: true
             Layout.columnSpan: id_container.columns
//             MediaPlayer{
//                 id: id_player
//                 //source: "file:///e:/haiyang.mp4"
//                 source:"http://cctv1.vtime.cntv.wscdns.com/live/no/13_/seg0/index.m3u8?uid=default&AUTH=9F0TuDQ4bEafPc6oswSFnYQYBEL+Fd1iDJ4JWHRUvsmTwJh6C+qzyZnRtasPh0NGlS0K0KiDqWqCyHCve0eemw=="
//                 //source: "pa://cctv_p2p_hdbtv1"
//                 autoPlay: true
//             }

//             VideoOutput{
//                    id: id_output
//                    width: 520
//                    height: 360
//                    anchors.top: parent.top
//                    anchors.topMargin: 30
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    source: id_player
//                    XmsIcon{
//                        anchors.centerIn: parent
//                        text:FontName.ICON_PLAYER_PLAY
//                        size:25

//                    }

//                    Item{
//                        width: 200
//                        height: 200
//                        anchors.top: parent.top
//                        anchors.right: parent.right
//                        clip: true
////                        VideoOutput{
////                            width: 1200
////                            height: 1200
////                            anchors.centerIn: parent
////                            source: id_player
////                        }
//                    }

//                    function xxx(){
//                        id_output.mapRectToSourceNormalized(Qt.rect(10,10,120,120))
//                    }

//                    Component.onCompleted: xxx()




//                }



//                Rectangle{
//                    width: 600
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    anchors.top: id_output.bottom
//                    anchors.topMargin: 10
//                    height: 1
//                    color:UI.COLOR_BASE_WHITE

//                }



        }

    }

}
