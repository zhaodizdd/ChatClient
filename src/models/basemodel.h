#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "../net/clientnet.h"

class BaseModel
{
public:
    BaseModel();
    ~BaseModel();
    // 将Qjson转为string
    std::string convertQJsonObjToString(QJsonObject);

protected:
    ClientNet *net;
};

#endif // BASEMODEL_H
