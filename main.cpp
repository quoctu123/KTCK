#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <QDir>
#include <QMediaFormat>
#include <QMimeType>
#include <QSettings>
#include "serialhandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("Media Serial Player");
    QCoreApplication::setOrganizationName("MyCompany");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // Sử dụng QSettings để lưu danh sách tệp gần đây
    QSettings settings("MyCompany", "MediaPlayer");

    QQmlApplicationEngine engine;

    // Truyền QSettings vào QML
    engine.rootContext()->setContextProperty("settings", &settings);

    // Tạo đối tượng SerialHandler và đưa vào QML
    SerialHandler serialHandler;
    engine.rootContext()->setContextProperty("serialHandler", &serialHandler);

    // Load QML
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
