import QtQuick 2.7
import "../../Controls"
import "../../Controls/UIConstants.js" as UI

FlatButton{
    id: id_bt
    property bool isShowLine:false
    enabled: checked? false : true
    isCheckedBt:true
    foreColor:UI.COLOR_BASE_BLACK_DARK
    hoverColor: UI.COLOR_BASE_BLACK_LIGHT
    sizeIcon: 18
    selectColor: "red"
    Rectangle{
        visible: id_bt.isShowLine
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: -1
        width: 1
        color:"black"
    }
}
