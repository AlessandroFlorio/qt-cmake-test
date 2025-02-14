#include "myitem.h"
#include "testimageprovider.h"

#include <QQmlEngine>

MyItem::MyItem(QObject * parent)
    : QQmlExtensionPlugin(parent)
{
}

void MyItem::registerTypes(const char * uri)
{
    // not reached in Android
    qDebug() << "MyItem called registerTypes";
}

void MyItem::initializeEngine(QQmlEngine * engine, const char * /*uri*/)
{
    // not reached in Android
    qDebug() << "MyItem called initializeEngine";

    engine->addImageProvider("testimage", new TestImageProvider());
}
