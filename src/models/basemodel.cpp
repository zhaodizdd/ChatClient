#include "basemodel.h"

#include <QJsonObject>
#include <QJsonDocument>

BaseModel::BaseModel()
{
    // 获取socket连接
    this->net = ClientNet::NewInstance();
}
BaseModel::~BaseModel()
{
    if (net != nullptr)
    {
        // 断开socket连接
        delete net;
        net = nullptr;
    }
}

std::string BaseModel::convertQJsonObjToString(QJsonObject jsonObj){
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    QString jsonStr(byteArray);
    std::string jsonStrStd = jsonStr.toStdString();

    return jsonStrStd;
}
