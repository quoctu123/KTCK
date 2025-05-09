#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>

class SerialHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList songList READ songList NOTIFY songListChanged)
public:
    explicit SerialHandler(QObject *parent = nullptr);
    QStringList songList() const { return m_songList; }
    Q_INVOKABLE void sendCommand(const QString &command);

signals:
    void songListChanged();

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_socket;
    QStringList m_songList;
    bool m_receivingSongList = false;
};

#endif // SERIALHANDLER_H
