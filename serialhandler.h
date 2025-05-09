#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QSerialPort>

class SerialHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList wifiList READ wifiList NOTIFY wifiListChanged)
    Q_PROPERTY(QStringList bleList READ bleList NOTIFY bleListChanged)

    // Thêm 2 property giữ trạng thái switch Wi-Fi và Bluetooth
    Q_PROPERTY(bool wifiSwitchOn READ wifiSwitchOn WRITE setWifiSwitchOn NOTIFY wifiSwitchOnChanged)
    Q_PROPERTY(bool bleSwitchOn READ bleSwitchOn WRITE setBleSwitchOn NOTIFY bleSwitchOnChanged)

    // Thêm 2 biến giữ trạng thái kết nối
    Q_PROPERTY(bool wifiConnected READ wifiConnected NOTIFY wifiConnectedChanged)
    Q_PROPERTY(bool bleConnected READ bleConnected NOTIFY bleConnectedChanged)
    // Thêm property cho MAC address của Bluetooth
    Q_PROPERTY(QString connectedSSID READ connectedSSID NOTIFY connectedSSIDChanged)
    // Thêm property cho MAC address của Bluetooth
    Q_PROPERTY(QString connectedMAC READ connectedMAC NOTIFY connectedMACChanged)

public:
    explicit SerialHandler(QObject *parent = nullptr);
    QString connectedSSID() const { return m_connectedSSID; }
    QString connectedMAC() const { return m_connectedMAC; }  // MAC của thiết bị đang kết nối Bluetooth
    QStringList wifiList() const { return m_wifiList; }
    QStringList bleList() const { return m_bleList; }

    bool wifiSwitchOn() const { return m_wifiSwitchOn; }
    bool bleSwitchOn() const { return m_bleSwitchOn; }

    bool wifiConnected() const { return m_wifiConnected; } // Trạng thái kết nối Wi-Fi
    bool bleConnected() const { return m_bleConnected; }   // Trạng thái kết nối Bluetooth

    void setWifiSwitchOn(bool on) {
        if (m_wifiSwitchOn == on) return;
        m_wifiSwitchOn = on;
        emit wifiSwitchOnChanged();
    }

    void setBleSwitchOn(bool on) {
        if (m_bleSwitchOn == on) return;
        m_bleSwitchOn = on;
        emit bleSwitchOnChanged();
    }

    Q_INVOKABLE void sendCommand(const QString &cmd); // Gửi lệnh xuống ESP32

signals:
    void wifiListChanged();
    void bleListChanged();

    void wifiSwitchOnChanged();  // Signal trạng thái Wi-Fi switch
    void bleSwitchOnChanged();   // Signal trạng thái BLE switch

    // Thêm tín hiệu cho việc thay đổi trạng thái kết nối
    void wifiConnectedChanged();
    void bleConnectedChanged();

    void connectedSSIDChanged();  // Signal khi SSID thay đổi
    void connectedMACChanged();   // Signal khi MAC address Bluetooth thay đổi

    void wifiPasswordError();
private slots:
    void readSerial();

private:
    void parseLine(const QString &line);  // Hàm parse từng dòng text
    QString m_connectedSSID;
    QString m_connectedMAC;  // MAC address của thiết bị Bluetooth

    QSerialPort serial;
    QString buffer;

    QStringList m_wifiList;
    QStringList m_bleList;

    // Trạng thái switch Wi-Fi/Bluetooth
    bool m_wifiSwitchOn = false;
    bool m_bleSwitchOn = false;

    // Trạng thái kết nối Wi-Fi/Bluetooth
    bool m_wifiConnected = false;
    bool m_bleConnected = false;
};

#endif // SERIALHANDLER_H
