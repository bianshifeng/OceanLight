import QtQuick 2.7
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"


StackView {
    id: id_root
    anchors.fill: parent
    initialItem: id_HomePage

    Component{
        id: id_HomePage
        PageImageTheme{
            onCurrentInfoChanged: {
                id_info_txt.text = currentInfo
            }
            DropShadow {
                anchors.fill: id_title_txt
                horizontalOffset: 0
                verticalOffset: 3
                radius: 8.0
                samples: 17
                color: "#80000000"
                source: id_title_txt
            }

            XmsText{
                id: id_title_txt
                text: "CPC"
                size: 50
                color:UI.COLOR_BASE_WHITE
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 60
                XmsText{
                    id: id_info_txt
                    text: "The alg is for people collection for the ai computer."
                    color: parent.color
                    anchors.left: parent.left
                    anchors.top: parent.bottom
                    anchors.topMargin: 10
                }
            }
        }
    }

    Component{
        id: id_CameraPage
        MainCameraPage{
        }
    }


    function showHomePage(){
        id_root.push(id_HomePage)
    }
    function showCameraPage(){
        id_root.push(id_CameraPage)
    }

}
