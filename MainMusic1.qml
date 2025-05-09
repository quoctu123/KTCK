import QtQuick
import QtQuick.Controls
import QtMultimedia
import Qt.labs.platform 1.1
import Qt.labs.settings 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Multimedia Player"
    color: "#0B1022"

    // Đảm bảo Settings được khởi tạo đúng cách
    Settings {
        id: settings
        property var recentFiles: []  // Danh sách các tệp gần đây
    }

    MediaPlayer {
        id: player
        videoOutput: videoOutput
        audioOutput: AudioOutput {}
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        anchors.margins: 40
        fillMode: VideoOutput.PreserveAspectFit
    }

    FileDialog {
        id: fileDialog
        title: "Chọn media file"
        onAccepted: {
            player.source = fileDialog.file
            player.play()

            // Lưu tệp đã chọn vào danh sách gần đây
            if (!settings.recentFiles.includes(fileDialog.file)) {
                settings.recentFiles.unshift(fileDialog.file);  // Thêm vào đầu danh sách
                if (settings.recentFiles.length > 5) {
                    settings.recentFiles.pop();  // Giới hạn danh sách 5 tệp gần đây
                }
            }
            // Lưu lại danh sách vào Settings
            settings.recentFiles = settings.recentFiles;
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Click <a href=\"#\" style=\"color:#00ff88\">here</a> to open media file."
        color: "white"
        font.pixelSize: 20
        textFormat: Text.RichText
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: fileDialog.open()
        }
    }

    // Thanh điều khiển dưới cùng
    Rectangle {
        height: 80
        width: parent.width
        color: "#111c33"
        anchors.bottom: parent.bottom
        radius: 10

        Row {
            anchors.centerIn: parent
            spacing: 30

            Button {
                text: "⏪"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: {
                    // Tua ngược lại 10 giây
                    if (player.position - 10000 >= 0) {
                        player.position -= 10000;
                    } else {
                        player.position = 0;  // Đảm bảo không vượt qua vị trí 0
                    }
                }
            }

            Button {
                text: player.playbackState === MediaPlayer.PlayingState ? "⏸" : "▶"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: player.playbackState === MediaPlayer.PlayingState ? player.pause() : player.play()
            }

            Button {
                text: "⏩"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: {
                    // Tua tới 10 giây
                    if (player.position + 10000 <= player.duration) {
                        player.position += 10000;
                    } else {
                        player.position = player.duration;  // Đảm bảo không vượt quá tổng thời gian
                    }
                }
            }

            Button {
                text: "🔁"
                font.pixelSize: 24
                width: 60; height: 60
                onClicked: player.playbackRate = 1.0
            }
        }

        Slider {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 20
            value: player.position / player.duration
            onMoved: player.seek(value * player.duration)
        }

        Slider {
            id: volumeSlider
            width: 100
            height: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            value: player.audioOutput.volume
            onValueChanged: player.audioOutput.volume = value
        }
    }

    // Thêm nút để hiển thị danh sách tệp gần đây
    Button {
        text: "Show Recent Files"
        width: 150
        height: 40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottomMargin:  100
        onClicked: {
            recentFilesListView.visible = !recentFilesListView.visible;  // Hiện/ẩn danh sách
        }
    }

    // ListView để hiển thị danh sách các tệp gần đây
    ListView {
        id: recentFilesListView
        width: parent.width
        height: 150
        anchors.bottom: parent.top
        visible: false  // Mặc định ẩn danh sách
        model: ListModel {
            // Tạo danh sách các tệp gần đây từ settings
            Component.onCompleted: {
                // Lấy lại danh sách các tệp đã lưu trong settings
                for (var i = 0; i < settings.recentFiles.length; ++i) {
                    append({name: settings.recentFiles[i]})
                }
            }
        }

        delegate: Item {
            width: parent.width
            height: 40

            Rectangle {
                width: parent.width
                height: 40
                color: "#333"
                border.color: "#555"
                radius: 5

                Text {
                    anchors.centerIn: parent
                    text: model.name
                    color: "white"
                    font.pixelSize: 18
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        // Khi nhấn vào tên tệp gần đây, phát lại
                        player.source = model.name
                        player.play()
                    }
                }
            }
        }
    }

    onClosing: {
        player.stop();  // Dừng phát video hoặc âm thanh khi cửa sổ bị đóng
    }
}
