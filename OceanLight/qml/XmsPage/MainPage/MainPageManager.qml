import QtQuick 2.7
import QtQuick.Controls 2.1

import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../BaseCom"


StackView {
    id: id_root
    anchors.fill: parent
    initialItem: id_HomePage


    Component{
        id: id_HomePage
        PageImageTheme{


        }
    }

    Component{
        id: id_CameraPage
//        MainCameraPage{

//        }
        QtPlayer{

        }
    }


    function showHomePage(){
        id_root.replace(id_HomePage)
    }
    function showCameraPage(){
        id_root.replace(id_CameraPage)
    }

}
