/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import Qt.labs.folderlistmodel 2.1
import QtMultimedia 5.5
import QtGraphicalEffects 1.0
import "./Theme"
import "./Pages"
import "./XmsPage/BaseCom"
import "./Controls"
import "./Controls/UIConstants.js" as UI
import "./Fonts"
import "./Fonts/XmsIconFont.js" as FontName
import "./Models"
import "./UserControls"
import "./XmsPage/ChildPage"

AppWindow {
    id: id_app_window
    implicitHeight: 600
    implicitWidth: implicitHeight * UI.const_gold_mean
    property bool isHoverEnabled: false

    signal showFullScreen()

    TopbarComponent{
        id: id_topBar
        z:100
        XmsText{
            text: "OCEAN"
            size: 16
            color:UI.COLOR_BASE_WHITE
            font.bold: true
            opacity: 0.8
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        onEmitFullScreen: showFullScreen()
    }

    Item{
        id: id_content
        anchors.top: id_topBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        state: "showMainpage"

        Item{
            id:id_footBar
            height: 34
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Row{
                anchors.left: parent.left
                anchors.leftMargin: 0
                spacing: 1

                MainMenuButton{
                    width: 120
                    height: 34
                    size: 12
                    sizeIcon: 14
                    icon: FontName.ICON_BASE_CHART
                    isShowLine: true
                    text: qsTr("算法报价")
                    foreColor: UI.COLOR_BASE_WHITE_BASE
                    hoverColor: UI.COLOR_BASE_ORANGE
                }
                MainMenuButton{
                    width: 120
                    height: 34
                    size: 12
                    sizeIcon: 14
                    icon: FontName.ICON_ACTION_DETAIL
                    isShowLine: true
                    text: qsTr("使用文档")
                    foreColor: UI.COLOR_BASE_WHITE_BASE
                    hoverColor: UI.COLOR_BASE_ORANGE
                }
            }

            XmsText{
                text: qsTr("Impower")
                anchors.right: parent.right
                anchors.rightMargin: 5
                color: UI.COLOR_BASE_WHITE_BASE
                size: 12
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item{
            id: id_mainPage
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: id_footBar.top
            DropShadow {
                anchors.fill: id_backImage
                horizontalOffset: 0
                verticalOffset: 3
                radius: 8.0
                samples: 17
                color: "#80000000"
                source: id_backImage
            }
            Image {
                id: id_backImage
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/images/images/mainpage/albumcover.png"
                anchors.fill: parent
            }

            PageImageTheme{
                id: id_content_page
                anchors.fill: parent
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

        Column{
            id: id_child_page
            clip: true
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height
            Item{
                anchors.left: parent.left
                anchors.right: parent.right
                height: id_content.height -40
                Rectangle{
                    anchors.fill: parent
                    color:"#4c5258"
                    opacity: 0.6
                }

                ChildPageManager{
                    id: id_childPageManager
                    anchors.fill: parent
                }
            }
            NavbarComponent{
                onEmitShowPage: {
                    id_childPageManager.replace(pageSource)
                }
                onCurrentMenuChanged: {
                    if(currentMenu === "mainPage"){
                        id_content.state = "showMainpage"
                    }else{
                        id_content.state = "showChildPage"
                    }
                }
            }

        }


        states: [
            State {
                name: "showMainpage"
                PropertyChanges {
                    target: id_child_page
                    y:-(id_content.height -40)
                }
                PropertyChanges{
                    target: id_content_page
                    visible:true
                }
            },
            State {
                name: "showChildPage"
                PropertyChanges {
                    target: id_child_page
                    y:0
                }
                PropertyChanges{
                    target: id_content_page
                    visible:false
                }
            }
        ]

        transitions: [
            Transition {
                      NumberAnimation {
                          target: id_child_page
                          properties: "x,y";
                          easing.type: Easing.InOutQuad }
                  }
        ]
    }

    Component.onCompleted: {
        isHoverEnabled = touchSettings.isHoverEnabled()
    }
}
