import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../../Controls/UIConstants.js" as UI
import "../../Fonts/XmsIconFont.js" as FontName
import "../../Controls"

FocusScope{
    id: id_root
    property string currentMenu:"mainPage"
    height: 40
    anchors.left: parent.left
    anchors.right: parent.right


    DropShadow {
        anchors.fill: id_backrect
        horizontalOffset: 0
        verticalOffset: -3
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: id_backrect
    }


    LinearGradient {
        id: id_backrect
        anchors.fill: parent
        source: undefined
        start: Qt.point(0, 0)
        end: Qt.point(id_root.width, 0)
        gradient: Gradient {
            GradientStop {
                   position: 0.000
                   color: "#9d9fa2"
                }
            GradientStop {
                   position: 0.267
                   color: "#9d9fa2"
                }
            GradientStop {
               position: 0.500
               color: "#ffffff"
            }
            GradientStop {
               position: 0.733
               color: "#9d9fa2"
            }
            GradientStop {
               position: 1.000
               color: "#9d9fa2"
            }
          }
    }
    ExclusiveGroup{
        id: id_navGroup

    }
    MainMenuButton{
        id: id_main_bt
        isShowLine:true
        visible: !checked
        exclusiveGroup: id_navGroup
        checked:true
        icon:FontName.ICON_BASE_HOME
        height: id_root.height
        width: 50
        onClicked: {
            id_root.currentMenu = "mainPage"
        }
    }

    RowLayout{
        anchors.left: id_main_bt.visible ? id_main_bt.right:parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 1
        Repeater{
            model: id_menuList
            MainMenuButton{
                property string btName:itemName
                property string btSource:pageSource
                isShowLine: index < 4 ? true : false
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.minimumHeight: id_root.height
                Layout.preferredHeight: id_root.height
                exclusiveGroup: id_navGroup
                icon:itemIcon
                text: itemTitle
                onClicked: {
                    id_root.currentMenu = btName
                    emitShowPage(btName,btSource)
                }


            }

        }
    }
    ListModel{
        id: id_menuList
        ListElement{
            itemName:"camera"
            itemTitle:"Camera"
            itemIcon:"\u00cd"
            pageSource:"qrc:/qml/XmsPage/ChildPage/CameraPage.qml"
        }
        ListElement{
            itemName:"video"
            itemTitle:"Video"
            itemIcon:"\u00c4";
            pageSource:"qrc:/qml/XmsPage/ChildPage/VideoPage.qml"
        }
        ListElement{
            itemName:"alg"
            itemTitle:"Algorithm"
            itemIcon:"\u0091"
            pageSource:"qrc:/qml/XmsPage/ChildPage/AlgPage.qml"
        }
        ListElement{
            itemName:"alram"
            itemTitle:"Alarm"
            itemIcon:"\u00c0"
            pageSource:"qrc:/qml/XmsPage/ChildPage/AlarmPage.qml"
        }
        ListElement{
            itemName:"setting"
            itemTitle:"Setting"
            itemIcon:"\u00c6"
            pageSource:"qrc:/qml/XmsPage/ChildPage/SettingPage.qml"
        }
    }


    signal emitShowPage(var pageName, var pageSource)
}
