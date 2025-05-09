#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QDir>
#include <QMediaFormat>
#include <QMimeType>

#include <algorithm>

using namespace Qt::Literals::StringLiterals;

// Cấu trúc để lưu trữ các bộ lọc tên
struct NameFilters
{
    QStringList filters;
    int preferred = 0;
};

// Hàm trả về danh sách các bộ lọc tên tệp
static NameFilters nameFilters()
{
    QStringList result;
    QString preferredFilter;
    const auto formats = QMediaFormat().supportedFileFormats(QMediaFormat::Decode);
    for (qsizetype m = 0, size = formats.size(); m < size; ++m) {
        const auto format = formats.at(m);
        QMediaFormat mediaFormat(format);
        const QMimeType mimeType = mediaFormat.mimeType();
        if (mimeType.isValid()) {
            QString filter = QMediaFormat::fileFormatDescription(format) + " ("_L1;
            const auto suffixes = mimeType.suffixes();
            for (qsizetype i = 0, size = suffixes.size(); i < size; ++i) {
                if (i)
                    filter += u' ';
                filter += "*."_L1 + suffixes.at(i);
            }
            filter += u')';
            result.append(filter);
            if (mimeType.name() == "video/mp4"_L1)
                preferredFilter = filter;
        }
    }
    std::sort(result.begin(), result.end());
    const int preferred = preferredFilter.isEmpty() ? 0 : int(result.indexOf(preferredFilter));
    return { result, preferred };
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);



    // Cài đặt thông tin ứng dụng
    QCoreApplication::setApplicationName("MediaPlayer Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // Xử lý dòng lệnh
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Qt Quick MediaPlayer Example"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", QCoreApplication::translate("main", "The URL(s) to open."));
    parser.process(app);

    // Tạo engine QML
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);

    // Đọc đường dẫn URL nếu có từ dòng lệnh
    QUrl source;
    if (!parser.positionalArguments().isEmpty())
        source = QUrl::fromUserInput(parser.positionalArguments().at(0), QDir::currentPath());

    // Lấy bộ lọc tên tệp
    const auto filters = nameFilters();

    // Tạo các thuộc tính ban đầu để truyền vào QML
    QVariantMap initialProperties{
        {"source", source},
        {"nameFilters", filters.filters},
        {"selectedNameFilter", filters.preferred}
    };

    // Thiết lập các thuộc tính ban đầu cho engine QML
    engine.setInitialProperties(initialProperties);

    // THÊM CÁC ĐƯỜNG DẪN IMPORT CHO MODULE MediaControls
    engine.addImportPath("qrc:/");
    engine.addImportPath(QCoreApplication::applicationDirPath() + "/MediaControls");

    // Tải ứng dụng QML từ tài nguyên qrc:/main.qml
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
