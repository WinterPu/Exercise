#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QLabel>
#include <QQmlContext>
#include "WAV_Lib.h"
#include "SoundGenerator.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//  [Just For Practice]
//  [#1 ]Exposing C++  to QML
//    qmlRegisterType<MyLabel>("MyLabelLib", 1, 0, "MyLabel");


//  [#2] Exposing QML Objects to C++ [Way 1]
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




// <class> -> [import lib name] [qml name]
    qmlRegisterType<WavFile>("WAV_Lib", 1, 0, "WavFileGenerator");
   // qmlRegisterType<SoundGenerator>("SoundGenerator", 1, 0, "SoundGenerator");


 //  [#3] Exposing QML Objects to C++ [Way 2]
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    SoundGenerator soundGenerator;
    engine.rootContext()->setContextProperty("soundGenerator",&soundGenerator);

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
