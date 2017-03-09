import QtQuick 2.8
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../UIConstants.js" as UI



XmsScrollViewStyle{
    id: id_root
    property color backGroundColor: UI.COLOR_BASE_TRANSPARENT         //滚动条背景的颜色
    property color handerColor: UI.COLOR_BASE_GRAY_DARK            //滑块的颜色
    property color handerSelectColor: UI.COLOR_BASE_GRAY_LIGHT       //滑块选中的颜色
    property color handerLineColor: "#A9C9DE"         //"#D9E7F0"//滑块线的颜色
    property color handerLineSelectColor: "#6DC6FF"   //"#B4D0E2"//滑块线选中的颜色
    property int scrollbarwidth:5                    //宽度
    property bool moveshowScrollBars: false           //设置为true移动view就会出现滚动条，不动就消失

    transientScrollBars:moveshowScrollBars


    QtObject{
        id:d_ptr
        property string qrcFlg:"qrc:/src/"    //"../../" //
    }

    scrollBarBackground:Rectangle{
        width:3
        height:id_root.height
        color: backGroundColor
    }

    handle : Item {
        implicitWidth: scrollbarwidth
        anchors.rightMargin: -1
        Rectangle {
            radius: width/2
            color: styleData.hovered === true ? handerSelectColor:handerColor
            anchors.fill: parent
        }
    }
    decrementControl:Rectangle{
        width: scrollbarwidth
        height: scrollbarwidth
        color: backGroundColor
    }
    incrementControl:Rectangle{
        width: scrollbarwidth
        height: scrollbarwidth
        color: backGroundColor

    }

 }

