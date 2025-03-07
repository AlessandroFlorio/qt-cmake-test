#include "myitem.h"
#include "testimageprovider.h"

#include <QQmlEngine>

#ifdef REGISTER_STATIC_PLUGIN
extern void REGISTER_STATIC_PLUGIN();
#endif

MyItem::MyItem(QObject * parent)
    : QQmlExtensionPlugin(parent)
{
#ifdef REGISTER_STATIC_PLUGIN
    // see https://bugreports.qt.io/browse/QTBUG-83402
    // this is needed to register qml types in statically linked library (iOS)
    volatile auto registration = &REGISTER_STATIC_PLUGIN;
    Q_UNUSED(registration)
#endif
}

void MyItem::registerTypes(const char * uri)
{
    qDebug() << "MyItem called registerTypes";
}

void MyItem::initializeEngine(QQmlEngine * engine, const char * /*uri*/)
{
    qDebug() << "MyItem called initializeEngine";

    engine->addImageProvider("testimage", new TestImageProvider());
}
