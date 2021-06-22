#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>
#include <QQuickStyle>

#include "readfile.h"

#ifdef Q_OS_ANDROID
#include <QtAndroid>
bool checkPermission() {
    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    if(r == QtAndroid::PermissionResult::Denied) {
        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
        r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
        if(r == QtAndroid::PermissionResult::Denied) {
            return false;
        }
    }
    return true;
}
bool checkPermission2() {
    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.READ_EXTERNAL_STORAGE");
    if(r == QtAndroid::PermissionResult::Denied) {
        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.READ_EXTERNAL_STORAGE" );
        r = QtAndroid::checkPermission("android.permission.READ_EXTERNAL_STORAGE");
        if(r == QtAndroid::PermissionResult::Denied) {
            return false;
        }
    }
    return true;
}
#endif
int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    checkPermission();
    checkPermission2();
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    getlist getlist;
    getlist.run();
    getlist.fileinfolist=getlist.cachefileinfolist;
    for (int i=0;i<getlist.cachefileinfolist.count();i++) getlist.filelist.append(getlist.cachefileinfolist[i].fileName());
    readlyric readlyric;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("readlyric",&readlyric);
    engine.rootContext()->setContextProperty("getlist",&getlist);




    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
