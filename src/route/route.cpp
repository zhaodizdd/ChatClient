#include "route.h"
#include "../interface/momon/alert.h"
#include "../models/usermodel.h"

Route::Route(QWidget *parent)
    : QWidget(parent)
{
    this->myLoginInterface = nullptr;
    this->myMainWindowInterface = nullptr;
}

Route* Route::singleObj = NULL;

Route* Route::NewInstance(){
    if(singleObj == nullptr){
        singleObj = new Route();
    }

    return singleObj;
}

//把全局唯一的登陆界面对象设置到route的成员变量里面，api请求异步回来之后能通过成员变量操作到界面
void Route::setLoginInterface(Login *mylogin){
    this->myLoginInterface = mylogin;
}

//同上设置全局唯一的mainwindow对象
void Route::setMainWindowInterface(MainWindow *myMainWindow){
    this->myMainWindowInterface = myMainWindow;
}

void Route::distributeRecvMsg(QString msg)
{
    // 接收ChatServer转发的数据，反序列化生成json数据对象
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8().data());  // 转化为 JSON 文档
    qDebug() << msg<< endl;
    qDebug() << doc<< endl;
    if(doc.isNull() || doc.isEmpty()){
        qDebug()  << "json doc is NULL" << endl;
    }
    QJsonObject jsonObj = doc.object();
    if (jsonObj.contains("msgid")) //判断是否包含msgid 通过msgid来找到对应的回调
    {
        QJsonValue value = jsonObj.value("msgid");
        int msgType = value.toInt();
        // 单聊回调
        if (ONE_CHAT_MSG == msgType)
        {
            this->myMainWindowInterface->oneChatCallback(jsonObj);
            return;
        }
        // 群聊回调
        if (GROUP_CHAT_MSG == msgType)
        {
            this->myMainWindowInterface->GroupChatCallback(jsonObj);
            return;
        }
        // 登录回调
        if (LOGIN_MSG_ACK == msgType){
            if(ERROR_OK == jsonObj.value("errno").toInt())
            {
                this->myMainWindowInterface->apiLoginCallback(jsonObj);
            }
            else if (ERROR_LOGIN_1 == jsonObj.value("errno").toInt())
            {
                Alert alertObj;
                alertObj.setTitle("Login Failed");
                alertObj.setMsg("用户id或密码错误！");
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }else if (ERROR_LOGIN_2 == jsonObj.value("errno").toInt())
            {
                Alert alertObj;
                alertObj.setTitle("Login Failed");
                alertObj.setMsg("用户已登录请误重复登录！");
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }
            return;
        }
        // 注册回调
        if (REG_MSG_ACK == msgType){
            if(ERROR_OK == jsonObj.value("errno").toInt())
            {
                int id = jsonObj.value("id").toInt();
                QString name = jsonObj.value("name").toString();

                QString str = "用户的id:%1 名称:%2";
                QString msg = str.arg(id).arg(name);
                Alert alertObj;
                alertObj.setTitle("注册成功");
                alertObj.setMsg(msg);
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }
            if(ERROR_REG_1 == jsonObj.value("errno").toInt())
            {
                Alert alertObj;
                alertObj.setTitle("注册失败");
                alertObj.setMsg("用户已存在");
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }
            return;
        }
        // 添加好友回调
        if (ADD_FRIEND_MSG_ACK == msgType)
        {
            int id = jsonObj.value("id").toInt();
            QString name = jsonObj.value("name").toString();
            QString state = jsonObj.value("state").toString();
            Alert alertObj;
            alertObj.setTitle("用户：" + name);
            alertObj.setMsg("添加你为好友");
            alertObj.setButtonContent("OK");
            alertObj.exec();

            // 创建好友信息
            std::shared_ptr<UserProfile> firend(new UserProfile());
            firend->uid = id;
            firend->name = name;
            firend->state = state;
            // 添加好友信息到好友列表
            this->myMainWindowInterface->getFirends().push_back(firend);
            // 在好友列表窗口添加该好友的信息
            this->myMainWindowInterface->drawFriendItem(
                        myMainWindowInterface->getUId(),
                        myMainWindowInterface->getUName(),
                        firend);
            return;
        }
        // 创建群组回调
        if (CREATE_GROUP_MSG_ACK == msgType)
        {
            // 创建成功
            if(ERROR_OK == jsonObj.value("errno").toInt())
            {
                int groupId = jsonObj.value("groupid").toInt();
                QString groupName = jsonObj.value("groupname").toString();
                QString groupDesc = jsonObj.value("groupdesc").toString();
                QString str = "群组的id:%1 群组名称:%2";
                QString msg = str.arg(groupId).arg(groupName);
                Alert alertObj;
                alertObj.setTitle(msg);
                alertObj.setMsg("群组描述：" + groupDesc);
                alertObj.setButtonContent("OK");
                alertObj.exec();

                // 创建群组信息
                std::shared_ptr<Group> group(new Group());
                group->id = groupId;
                group->name = groupName;
                group->desc = groupDesc;
                // 创建的群组只可能有自己的信息
                QVector<GroupUser> groupUsers;
                GroupUser groupUser;
                groupUser.uid = this->myMainWindowInterface->getUId();
                groupUser.name = this->myMainWindowInterface->getUName();
                groupUser.state = "online";
                groupUser.role = "creator";
                groupUsers.push_back(groupUser);
                group->users = groupUsers;

                // 添加群组到群组列表
                this->myMainWindowInterface->getGroups().push_back(group);
                this->myMainWindowInterface->drawGroupItem(
                            myMainWindowInterface->getUId(),
                            myMainWindowInterface->getUName(),
                            group);
            }
            else
            {
                Alert alertObj;
                alertObj.setTitle("抱歉");
                alertObj.setMsg("创建群组失败！");
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }
            return;
        }
        // 加入群组回调
        if (ADD_GROUP_MSG_ACK == msgType)
        {
            if (ERROR_OK == jsonObj.value("errno").toInt())
            {
                Alert alertObj;
                alertObj.setTitle("加入群组成功");
                alertObj.setButtonContent("OK");
                alertObj.exec();


            }
            else
            {
                Alert alertObj;
                alertObj.setTitle("加入群组失败");
                alertObj.setButtonContent("OK");
                alertObj.exec();
            }
            return;
        }
        // 注销回调
        if (LOGINOUT_MSG_ACk == msgType)
        {
            if (ERROR_OK == jsonObj.value("errno").toInt())
            {
                this->myMainWindowInterface->close();
            }
        }
    }
}
