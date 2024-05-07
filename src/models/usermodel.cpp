#include "usermodel.h"
#include "../route/msg.h"

#include <QJsonObject>

//静态变量的初始化必须定义在外面
UserModel* UserModel::singleObj = NULL;

UserModel::UserModel()
{}

UserModel::~UserModel()
{
    //qDebug() << "user析构" << endl;
    if (net != nullptr)
    {
        //qDebug() << "net析构" << endl;
        delete net;
        net = nullptr;
    }
}

UserModel* UserModel::NewInstance(){
    if(singleObj == NULL){
        singleObj = new UserModel();
    }
    return singleObj;
}

// 发送消息api
bool UserModel::sendMag(QJsonObject &json)
{
    std::string jsonStrStd = this->convertQJsonObjToString(json);

    //发送请求，
    qDebug() << json << endl;
    // 判断是否已创建连接
    if(net != nullptr)
    {
        // 已创建连接，发送消息
        if(this->net->sendMsg(jsonStrStd)){
            // 发送成功
            return true;
        }
        else
            qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
    }
    else
        qDebug() << "客户端和服务端未连接" << endl;
    return false;
}

//登陆api
bool UserModel::login(int id, QString password)
{
    QJsonObject json;
    json.insert("msgid", LOGIN_MSG);
    json.insert("id", id);
    json.insert("password", password);

    std::string jsonStrStd = this->convertQJsonObjToString(json);

    if (net != nullptr)
    {
        //发送请求，执行登陆
        if(this->net->sendMsg(jsonStrStd)){

            return true;
        }
        else
            qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
    }
    else
        qDebug() << "客户端和服务端未连接" << endl;
    return false;
}

// 注册api
bool UserModel::reg(QString name, QString password)
{
    QJsonObject json;
    json.insert("msgid", REG_MSG);
    json.insert("name", name);
    json.insert("password", password);
    std::string jsonStrStd = this->convertQJsonObjToString(json);

    if (net != nullptr)
    {
        //发送请求，执行注册
        if(this->net->sendMsg(jsonStrStd)){
            return true;
        }
        qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
    }
    qDebug() << "客户端和服务端未连接" << endl;
    return false;
}

// 注销用户
void  UserModel::loginOut(int id)
{
    QJsonObject json;
    json.insert("msgid", LOGINOUT_MSG);
    json.insert("id", id);
    std::string jsonStrStd = this->convertQJsonObjToString(json);

    //发送请求，执行注销用户
    qDebug() << json << endl;
    if(!this->net->sendMsg(jsonStrStd)){
        qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
    }
}

// 添加好友api
bool UserModel::addFriend(int friendId)
{
    QJsonObject json;
    json.insert("msgid", ADD_FRIEND_MSG);
    json.insert("id", uid);
    json.insert("name", username);
    json.insert("friendid", friendId);
    std::string jsonStrStd = this->convertQJsonObjToString(json);

    //发送请求，执行添加好友
    qDebug() << json << endl;
    if(!this->net->sendMsg(jsonStrStd)){
        qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
        return false;
    }


    return true;
}

// 创建群组api
bool UserModel::createGroup(QString name, QString desc)
{
     QJsonObject json;
     json.insert("msgid", CREATE_GROUP_MSG);
     json.insert("id", uid);
     json.insert("groupname", name);
     json.insert("groupdesc", desc);
     std::string jsonStrStd = this->convertQJsonObjToString(json);

     //发送请求，执行创建群组
     qDebug() << json << endl;
     if(!this->net->sendMsg(jsonStrStd)){
         qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
         return false;
     }
     return true;
}

// 加入群组
bool UserModel::addGroup(int groupId)
{
    QJsonObject json;
    json.insert("msgid", ADD_GROUP_MSG);
    json.insert("id", uid);
    json.insert("groupid", groupId);
    std::string jsonStrStd = this->convertQJsonObjToString(json);

    //发送请求，执行创建群组
    qDebug() << json << endl;
    if(!this->net->sendMsg(jsonStrStd)){
        qDebug() << "发送失败，请检查网络或者服务器未开启" << endl;
        return false;
    }
    return true;
}
