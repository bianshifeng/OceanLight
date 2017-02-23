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
        anchors.leftMargin: 0
        anchors.rightMargin: 0

        QtPlayer{
            Layout.columnSpan: id_container.columns
            Layout.fillWidth: true
            Layout.fillHeight:true
            //mediaUrl: "http://anhui.vtime.cntv.cloudcdn.net/cache/anhuihls.m3u8?ptype=1&AUTH=LCKODVoLaQIx4TkNf2RPHeNWMYciQB167/KPN3qVTmhz3ykMEWDBd3h5KBS+Sf6xEmiigYcX9q7TTDYVFDvLKQ=="

            mediaUrl:  "file:///e:/pjl.MKV"
            mediaAutoPlay: true
        }

//        FlatPageTitleBar{
//            id: id_title_bar

//            Layout.fillWidth: true
//            Layout.preferredHeight: id_title_bar.height
//        }

//        FlatItemTitleBar{
//            Layout.columnSpan: id_container.columns
//            Layout.fillWidth: true
//            Layout.preferredHeight: height

//        }

//        QtPlayer{
//            Layout.fillWidth: true
//            Layout.preferredHeight:200
//            mediaUrl: "http://202.108.17.129/v.cctv.com/flash/mp4video54/TMS/2016/08/20/29759cb329ea49aaafc174365ad7b9b0_h264200000nero_aac16-2.mp4"
//            mediaAutoPlay: true
//        }


//        QtPlayer{
//            Layout.fillWidth: true
//            Layout.preferredHeight:600
//            mediaUrl: "http://btv1.live.cntv.dnion.com/live/btv1hls_/index.m3u8?ptype=1&AUTH=owstkHDP2wDUbzZmqH3nDZBbYUuR1SxMx4u/68wGReXGfNY4HUUGdnrLxy0uTu8PINJ421qeHNl/Xqs6Y7bo6w=="
//            mediaAutoPlay: true
//        }

    }

}
