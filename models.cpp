#include "models.h"



QString Request::toJsonString(){
    QJsonObject jsonObj;

    jsonObj["username"] = this->username;
    jsonObj["time"] = this->time;

    QJsonDocument doc(jsonObj);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    return strJson;
};
