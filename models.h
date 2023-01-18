#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>

class Request{
public:
    QString username = "Oleg";
    QString time = "10000";
    QVector<quint8> resource = {1,0,1,0};

    QString toJsonString();
};

#endif // MODELS_H
