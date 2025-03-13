#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngineExtensionPlugin>


int main(int argc, char * argv[])
{
#ifdef Q_OS_IOS
    Q_IMPORT_QML_PLUGIN(MyItem)
#endif
    qputenv("QML_IMPORT_TRACE", "1");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.addImportPath(QStringLiteral(PLUGIN_IMPORT_PATH));
    //engine.addImportPath(":/");
    //const QUrl url(QStringLiteral("qrc:/example.qml"));
    //engine.load(url);
    engine.loadFromModule("ExampleProject", "Example");

    return app.exec();
}
