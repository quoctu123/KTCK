#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentSong READ currentSong NOTIFY currentSongChanged)
    Q_PROPERTY(bool wifiConnected READ wifiConnected NOTIFY wifiConnectedChanged)

public:
    explicit SerialHandler(QObject *parent = nullptr);

    QString currentSong() const { return m_currentSong; }
    bool wifiConnected() const { return m_wifiConnected; }

    Q_INVOKABLE void sendCommand(const QString &cmd);

signals:
    void currentSongChanged();
    void wifiConnectedChanged();
    void wifiPasswordError();  // Thêm tín hiệu cho lỗi mật khẩu WiFi

private slots:
    void readSerial();

private:
    void parseLine(const QString &line);

    QSerialPort serial;
    QString m_currentSong;
    bool m_wifiConnected = false;  // Thêm biến trạng thái WiFi
    QByteArray buffer;
};
