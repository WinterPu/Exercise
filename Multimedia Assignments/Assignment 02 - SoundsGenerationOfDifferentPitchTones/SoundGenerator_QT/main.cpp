#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QLabel>
#include "WAV_Lib.h"
#include "SoundGenerator.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<MyLabel>("MyLabelLib", 1, 0, "MyLabel");

//    QQmlEngine engine01;
//        QQmlComponent component(& engine01,
//               QUrl(QStringLiteral("qrc:/main.qml")));
//        QObject * object = component.create();

//            QObject *rect =object->findChild<QObject*>("label01");
//            if (rect)
//            {
//                rect->setProperty("color","red");
//                rect->setProperty("text","HAHAHAHAH");
//            }
//            else
//                 qDebug("aaaaaaaa");





    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


//    QObject *rootObject = engine.rootObjects().first();
//    QObject *rect =rootObject->findChild<QObject *>("text201");
//    if (rect)
//    {
//        rect->setProperty("color","red");
//        rect->setProperty("text","HAHAHAHAH");
//    }
//    else
//         qDebug("aaaaaaaa");

    return app.exec();
}
