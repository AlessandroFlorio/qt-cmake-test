#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlextensionplugin.h>

int main(int argc, char * argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral(PLUGIN_IMPORT_PATH));
    engine.addImportPath(":/");
    const QUrl url(QStringLiteral("qrc:/example.qml"));
    engine.load(url);

    return app.exec();
}
