#include "serialhandler.h"
#include <QDebug>

SerialHandler::SerialHandler(QObject *parent)
    : QObject(parent)
{
    serial.setPortName("COM3");    // Chỉnh cho đúng cổng ESP32
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.open(QIODevice::ReadWrite)) {
        connect(&serial, &QSerialPort::readyRead, this, &SerialHandler::readSerial);
        qDebug() << "Serial connected!";
    } else {
        qDebug() << "Serial open failed!";
    }
}

void SerialHandler::sendCommand(const QString &cmd) {
    QString fullCmd = cmd + "\n";  // Gửi lệnh có xuống dòng
    serial.write(fullCmd.toUtf8());
}

void SerialHandler::readSerial() {
    buffer += serial.readAll();

    while (buffer.contains('\n')) {
        int index = buffer.indexOf('\n');
        QString line = buffer.left(index).trimmed();
        buffer = buffer.mid(index + 1);

        parseLine(line);
    }
}

void SerialHandler::parseLine(const QString &line) {
    qDebug() << "Received:" << line;

    if (line.startsWith("WiFi:")) {
        m_wifiConnected = line.contains("connected");
        emit wifiConnectedChanged();
    }
    else if (line.contains("Failed to connect")) {
        // Nếu mật khẩu WiFi sai
        emit wifiPasswordError();  // Phát tín hiệu lỗi mật khẩu WiFi
    }
    else if (line.startsWith("Playing song:")) {
        m_currentSong = line.mid(QString("Playing song:").length()).trimmed();
        emit currentSongChanged();  // Cập nhật bài hát đang phát
    }
    else if (line.startsWith("Stopped song:")) {
        m_currentSong.clear();
        emit currentSongChanged();  // Xóa bài hát khi dừng
    }
}
