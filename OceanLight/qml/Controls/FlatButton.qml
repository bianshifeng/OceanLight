import QtQuick 2.4
import "../Controls/UIConstants.js" as UI
import "../Fonts/XmsIconFont.js" as FontName
import "../Fonts"


ControlCard{
    id: id_root
    property int size:14
    property int sizeIcon:16
    property int hideTextWidth:120
    property color foreColor:UI.COLOR_BASE_WHITE_LIGHT
    property string text:""
    property string icon:""
    property string toolTip:""
    normalColor: UI.COLOR_BASE_TRANSPARENT

    signal clicked

    Item{
        anchors.fill: parent

        Row{
            anchors.centerIn: parent
            spacing: 10
            XmsIcon{
                text: id_root.icon
                size: id_root.sizeIcon
                color:id_root.foreColor
                anchors.verticalCenter: parent.verticalCenter
                tooltip: id_root.toolTip
            }
            XmsText{
                visible: id_root.width >=id_root.hideTextWidth ? true:false
                text: id_root.text
                anchors.verticalCenter: parent.verticalCenter
                color:id_root.foreColor
                size: id_root.size
                tooltip: id_root.toolTip
            }
        }

        XmsMouseArea{
            anchors.fill: parent
            hoverEnabled:false

            onClicked: {
                if(isCheckedBt){
                    id_root.checked = !id_root.checked
                }else{
                    id_root.checked = false
                }


                id_root.clicked()
            }
        }
    }
}
