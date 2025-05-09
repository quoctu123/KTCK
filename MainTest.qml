import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: qsTr("Serial WiFi + DFPlayer Demo")

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: serialHandler.wifiConnected ? "WiFi: Connected to " + serialHandler.connectedSSID
                                              : "WiFi: Not connected"
            font.pixelSize: 18
        }

        Button {
            text: "Play (DFPlayer)"
            onClicked: serialHandler.sendCommand("p")
        }

        Button {
            text: "Stop (DFPlayer)"
            onClicked: serialHandler.sendCommand("s")
        }

        ListView {
            width: parent.width * 0.9
            height: 100
            model: serialHandler.wifiList
            delegate: Text {
                text: modelData
                font.pixelSize: 14
            }
            header: Text {
                text: "WiFi Scan Results"
                font.bold: true
                font.pixelSize: 16
            }
        }
    }

    Connections {
        target: serialHandler
        function onWifiPasswordError() {
            Qt.callLater(() => {
                console.log("⚠️ Mật khẩu WiFi sai!");
            });
        }
    }
}
