import QtQuick 2.7
import QtQuick.Controls 2.1

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


        }
    }

    Component{
        id: id_CameraPage
        MainCameraPage{

        }
    }

    Component{
        id: id_Page_webinfo
        MainPageWebInfo{

        }
    }


    function showHomePage(){
        id_root.replace(id_HomePage)
    }
    function showCameraPage(){
        id_root.replace(id_CameraPage)
    }

    function show_webinfo_page(){
        id_root.replace(id_Page_webinfo)
    }

}
