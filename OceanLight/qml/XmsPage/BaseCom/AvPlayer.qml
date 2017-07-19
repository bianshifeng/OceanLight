import QtQuick 2.7
import Xms.Server 1.0
import QtAV 1.7
import "../../Fonts"
import "../../Controls/UIConstants.js" as UI

VideoOutput2 {
    id: id_root
    property alias mediaUrl: id_mediaPlayer.source
    implicitWidth: 960
    implicitHeight: 540
    source: id_mediaPlayer
    focus : visible // to receive focus and capture key events when visible
//    filters: [id_filter]
    MediaPlayer{
        id: id_mediaPlayer
        autoLoad: true
        onError: {
            if (error != MediaPlayer.NoError) {
                id_name.visible = true
            }else{
                id_name.visible = false

            }
        }
        videoCapture.async: true
        videoCapture.onImageCaptured: {
            if(id_mediaPlayer.error === MediaPlayer.NoError){
                AlgServer.setImageFrame(image)
            }
        }
    }

    Item{
        width: 80
        height: 40
        x:10
        y:20
        Rectangle{
            anchors.fill: parent
            opacity: 0.5
        }
        MouseArea{
            onClicked: {
                //AlgServer.resetVFD()
                id_mediaPlayer.videoCapture.capture()
            }
            anchors.fill: parent
            Text {
                text: qsTr("暂停vfd")
                font.pixelSize: 14
                anchors.centerIn: parent
                color: "white"
            }

        }
    }

    Timer{
        id: id_timer
        interval: 100000
        repeat: true
        onTriggered: {} //id_mediaPlayer.videoCapture.capture()
    }

    function play(){
        id_mediaPlayer.play()
        id_timer.start()
    }


    VideoOutput2{
        width: 300
        height: 200
        anchors.centerIn: parent
        source: id_mediaPlayer
    }


    Item {
        id: id_name

        visible:false

        anchors.centerIn: parent
        width: id_root.width

        Rectangle{
            height: 2
            width: id_root.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 16
            color: UI.COLOR_BASE_RED_BASE
        }

        XmsText {
            text: qsTr("PLAYER ERROR")
            anchors.centerIn: parent
            color: UI.COLOR_BASE_RED_BASE
        }

    }

    Component.onDestruction: {
        id_timer.stop()
        id_mediaPlayer.stop()
    }
}


//VideoFilter {
//    id: negate
//    type: VideoFilter.GLSLFilter
//    shader: Shader {
//        postProcess: "gl_FragColor.rgb = vec3(1.0-gl_FragColor.r, 1.0-gl_FragColor.g, 1.0-gl_FragColor.b);"
//    }

//}
//VideoFilter {
//    id: hflip
//    type: VideoFilter.GLSLFilter
//    shader: Shader {
//        sample: "vec4 sample2d(sampler2D tex, vec2 pos, int p) { return texture(tex, vec2(1.0-pos.x, pos.y));}"
//    }
//}
