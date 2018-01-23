#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QVariant>
class MyLabel : public QObject
{
    Q_OBJECT

public:

    // Object pointer
    QObject* myObject;
    explicit MyLabel(QObject *parent = nullptr);

    // Must call Q_INVOKABLE so that this function can be used in QML
    Q_INVOKABLE void SetMyObject(QObject* obj);

};

#endif // MYLABEL_H
