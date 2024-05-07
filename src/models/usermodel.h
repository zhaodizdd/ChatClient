#ifndef USERMODEL_H
#define USERMODEL_H

#include "basemodel.h"
#include <QMap>

class UserModel : protected BaseModel
{
public:
    ~UserModel();
    static UserModel* NewInstance();

    void setid(int id) { uid = id; }
    void setName(QString name) { username = name; }

    // 功能区
    bool sendMag(QJsonObject &json);
    bool login(int id, QString password);
    bool reg(QString name, QString password);
    bool addFriend(int friendId);
    bool oneChat();
    void loginOut(int id);
    bool createGroup(QString name, QString desc);
    bool addGroup(int groupId);
    bool groupChat();

private:
    UserModel();
    static UserModel *singleObj;
    int uid; // 当前登录用户的id
    QString username; // 当前登录用户的name;
};

#endif // USERMODEL_H
