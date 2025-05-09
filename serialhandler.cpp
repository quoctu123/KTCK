#include "SerialHandler.h"
#include <QDebug>

SerialHandler::SerialHandler(QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &SerialHandler::onReadyRead);

    QString esp32Ip = "192.168.1.20"; // Đổi thành IP thực tế của ESP32
    quint16 esp32Port = 5000;

    m_socket->connectToHost(esp32Ip, esp32Port);
    if (!m_socket->waitForConnected(3000)) {
        qDebug() << "Failed to connect to ESP32 at" << esp32Ip << ":" << esp32Port;
    } else {
        qDebug() << "Connected to ESP32 at" << esp32Ip << ":" << esp32Port;
    }
}

void SerialHandler::sendCommand(const QString &command)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = command.toUtf8();
        if (!data.endsWith('\n')) data.append('\n');
        m_socket->write(data);
        m_socket->flush();
        qDebug() << "Send command:" << command;
    } else {
        qDebug() << "Socket not connected, cannot send command:" << command;
    }
}

void SerialHandler::onReadyRead()
{
    while (m_socket->canReadLine()) {
        QString line = QString::fromUtf8(m_socket->readLine()).trimmed();
        qDebug() << "TCP received:" << line;
        if (line == "SONG_LIST_START") {
            m_songList.clear();
            m_receivingSongList = true;
        } else if (line == "SONG_LIST_END") {
            m_receivingSongList = false;
            emit songListChanged();
        } else if (m_receivingSongList) {
            m_songList << line;
        }
    }
}
