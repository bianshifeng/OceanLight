import QtQuick 2.5
import "../../Controls/UIConstants.js" as UI
import "../../Controls"
import "../../Fonts"
import "../../Utils/Calculations.js" as Utils
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Item{
    id: id_root
    implicitWidth: 200
    implicitHeight: 120

    property alias imageUrl : id_alarm_image.source
    property alias nameStr:id_txt_name.text
    property alias timeStr:id_txt_time.text
    property alias peopleName: id_reg_name.text
    property bool peopleIsReg:false


    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(id_root)
    }

    signal emitClick()

    Item{
        id: id_item_container
        anchors.fill: parent
        Rectangle{
            id: id_back_ground
            anchors.fill: parent
            opacity: id_mouseArea.containsMouse ? 1:0.8
        }


        ColumnLayout{
              id: id_col
              anchors.fill: parent
              anchors.topMargin: 2
              anchors.bottomMargin: 2
              anchors.rightMargin: 8
              anchors.leftMargin: 8
              spacing: 2
              XmsText{
                  id: id_txt_name
                  size: 16
                  color:UI.COLOR_BASE_WHITE
                  anchors.left: parent.left
                  XmsText{
                      id: id_txt_time
                      size: 12
                      color:UI.COLOR_BASE_WHITE
                      anchors.left: parent.right
                      anchors.bottom: parent.bottom
                      anchors.leftMargin: 8
                  }

              }

              Image{
                  id: id_alarm_image
                  fillMode: Image.PreserveAspectFit
                  Layout.fillWidth: true
                  Layout.fillHeight: true
              }

              XmsText{
                  id: id_reg_name
                  color:UI.COLOR_BASE_WHITE
                  text: ""
                  anchors.left: parent.left
              }

          }


        Rectangle{
            anchors.fill: parent
            visible: id_root.checked ? true: false
            border.color: UI.COLOR_BASE_WHITE
            border.width: 1
            color:UI.COLOR_BASE_TRANSPARENT
            opacity: 0.8
            anchors.margins: 1
        }


    }



    MouseArea{
        id: id_mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            id_root.checked = true
            emitClick()
        }

    }



    states: [
        State {
            name: "face_handle"
            when: !id_root.peopleName
            PropertyChanges {
                target: id_back_ground
                color:UI.COLOR_BASE_YELLOW //"#24374c"
            }

        },
        State {
            name: "face_know"
            when: id_root.peopleName && id_root.peopleIsReg
            PropertyChanges {
                target: id_back_ground
                color:UI.COLOR_BASE_GREEN
            }
        },
        State {
            name: "face_unknow"
            when: id_root.peopleName && !id_root.peopleIsReg
            PropertyChanges {
                target: id_back_ground
                color:UI.COLOR_BASE_RED_BASE
            }
        }
    ]

}
