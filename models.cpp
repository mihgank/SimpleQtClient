#include "models.h"
#include <QString>
#include <QVector>

class Request{
public:
    QString username = "Oleg";
    quint64 time = 10000;
    QVector<quint8> resource = {1,0,1,0};

    QString toJsonString();
};

