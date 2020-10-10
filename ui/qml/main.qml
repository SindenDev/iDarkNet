import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

import qtavplayer 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Material.theme: Material.Dark
    Material.accent: Material.Purple


//    AVOutput{
//        source: avplayer
//        width: 100
//        height: 100
//    }

    AVOutput{ //可以同时在多个窗口上播放一个视频
        source: avplayer
        anchors.fill: parent
    }
    AVPlayer{
        id : avplayer
//        source :"rtmp://202.69.69.180:443/webcast/bshdlive-pc"// "rtmp://52.83.75.119/live/1"
//        source: "rtmp://58.200.131.2:1935/livetv/hunantv"
        source: "C:/Users/Sinden/Videos/ch1_20201010135755.mp4"
//        autoPlay: true
//        autoLoad: true
    }
    Column{
        Button{
            text: "Play"
            onClicked: {
                avplayer.play()
            }
        }
        Button{
            text: "Restart"
            onClicked: {
                avplayer.restart()
            }
        }
        Button{
            text: "Stop"
            onClicked: {
                avplayer.stop()
            }
        }
    }






//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width
//        externalLanguageSwitchEnabled: true
//        active: true

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}
