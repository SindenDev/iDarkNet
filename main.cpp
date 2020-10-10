#include "mainwindow.h"
#include <QQuickStyle>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "AVDefine.h"
#include "AVPlayer.h"
#include "AVOutput.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);
    qmlRegisterType<AVDefine>("qtavplayer", 1, 0, "AVDefine");
    qmlRegisterType<AVPlayer>("qtavplayer", 1, 0, "AVPlayer");
    qmlRegisterType<AVOutput>("qtavplayer", 1, 0, "AVOutput");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
