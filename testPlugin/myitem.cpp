#include "myitem.h"
#include "testimageprovider.h"

#include <QQmlEngine>

#include <QtCore/qtsymbolmacros.h>

#ifdef REGISTER_STATIC_PLUGIN
extern void REGISTER_STATIC_PLUGIN();
#else
QT_DECLARE_EXTERN_RESOURCE(qmlcache_Tol)
QT_DECLARE_EXTERN_RESOURCE(qmake_TOL)
QT_DECLARE_EXTERN_RESOURCE(Tol_raw_qml_0)
QT_DECLARE_EXTERN_SYMBOL_VOID(qml_register_types_TOL)
#endif

MyItem::MyItem(QObject * parent)
    : QQmlExtensionPlugin(parent)
{
#ifdef REGISTER_STATIC_PLUGIN
    // see https://bugreports.qt.io/browse/QTBUG-83402
    // this is needed to register qml types in statically linked library (iOS)
    volatile auto registration = &REGISTER_STATIC_PLUGIN;
    Q_UNUSED(registration)
#else
    QT_KEEP_SYMBOL(qml_register_types_TOL)
    QT_KEEP_RESOURCE(qmlcache_Tol)
    QT_KEEP_RESOURCE(qmake_TOL)
    QT_KEEP_RESOURCE(Tol_raw_qml_0)
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
