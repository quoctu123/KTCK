import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Multimedia Player"
    color: "#0B1022"

    property int currentTrack: 1

    // Số bài ở góc trên trái
    Text {
        text: "Số bài: " + serialHandler.songList.length
        color: "yellow"
        font.pixelSize: 18
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 20
    }

    // Nút lấy danh sách nhạc ở góc trên phải
    Button {
        text: "Lấy danh sách nhạc"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.rightMargin: 20
        z: 2
        onClicked: serialHandler.sendCommand("list")
    }

    // Danh sách nhạc ở giữa
    Rectangle {
        width: 400
        height: 320
        color: "#222"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 70

        ListView {
            anchors.fill: parent
            anchors.margins: 10
            model: serialHandler.songList
            delegate: Item {
                width: parent.width
                height: 40
                Rectangle {
                    anchors.fill: parent
                    color: ListView.isCurrentItem ? "#444" : "transparent"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            currentTrack = index + 1
                            serialHandler.sendCommand("play:" + currentTrack)
                        }
                    }
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                        color: "white"
                        font.pixelSize: 18
                    }
                }
            }
        }
    }

    // Thanh điều khiển ở dưới cùng
    Rectangle {
        height: 80
        width: parent.width
        color: "#111c33"
        radius: 10
        anchors.bottom: parent.bottom

        Row {
            anchors.centerIn: parent
            spacing: 30

            // Tua lùi
            Button {
                text: "⏪"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: {
                    serialHandler.sendCommand("prev")
                    if (currentTrack > 1) currentTrack--
                }
            }

            // Play bài đang chọn
            Button {
                text: "▶"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: serialHandler.sendCommand("play:" + currentTrack)
            }

            // Pause
            Button {
                text: "⏸"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: serialHandler.sendCommand("pause")
            }

            // Tua tới
            Button {
                text: "⏩"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: {
                    serialHandler.sendCommand("next")
                    if (currentTrack < serialHandler.songList.length) currentTrack++
                }
            }

            // Điều chỉnh âm lượng
            Slider {
                id: volumeSlider
                width: 200
                height: 20
                from: 0; to: 30
                value: 20
                anchors.verticalCenter: parent.verticalCenter
                onValueChanged: serialHandler.sendCommand("volume:" + Math.round(value))
            }
        }
    }
    onClosing: {
            serialHandler.sendCommand("pause")
        }
}
