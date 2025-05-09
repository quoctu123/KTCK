#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
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

    // Tạo đối tượng QSettings để lưu các thiết lập (nếu cần)
    QSettings settings("MyCompany", "MediaPlayer");

    // Tạo đối tượng xử lý serial kết nối với ESP32
    SerialHandler serialHandler;

    QQmlApplicationEngine engine;

    // Truyền C++ object sang QML
    engine.rootContext()->setContextProperty("settings", &settings);
    engine.rootContext()->setContextProperty("serialHandler", &serialHandler);

    // Load file QML chính
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
