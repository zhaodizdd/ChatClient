#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../route/msg.h"
#include "../../models/usermodel.h"
#include "../momon/inputpopup.h"
#include "../momon/alert.h"
#include "firenditem.h"
#include "groupitem.h"
#include "chatitem.h"

#include <QPainter>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        m_moving = true;
        //鼠标按下时，鼠标相对屏幕的位置减去窗口相对屏幕的位置
        //event->globalPos()和pos()返回(x, y)，x相对于屏幕左下角距离。y相对于屏幕左上角距离
        m_lastPos = event->globalPos() - pos();
    }
    return QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (m_moving  && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_moving = false;
    return QMainWindow::mouseReleaseEvent(event);
}

// 画好友列表
void MainWindow::drawFriendList()
{
    for (auto &user : firends)
    {
        drawFriendItem(uid, uname, user);
    }
}
// 画好友列表中每一列的信息 参数：用户id 名称 好友信息
void MainWindow::drawFriendItem(int uid, QString uname, std::shared_ptr<UserProfile> user)
{
    // 创建好友项窗口显示
    FirendItem *firItem = new FirendItem(ui->contactsListW);
    firItem->setIdType("id: ");
    firItem->setId(user->uid);
    firItem->setNameType("用户名：");
    firItem->setName(user->name);
    QString state = user->state == "online" ? "[在线]" : "[离线]";
    firItem->setState(state);

    // 设置好友项的成员信息
    firItem->setUId(uid);
    firItem->setUName(uname);
    firItem->setFirendId(user->uid);
    firItem->setFirendName(user->name);

    if (oneChatMsgs.count(user->uid) == 1)
    {
        if (!oneChatMsgs.empty())
        {
            for(auto &responseChat : oneChatMsgs[user->uid])
            {
                firItem->addMsg("", responseChat->msg);
            }
        }
    }

    // 创建QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->contactsListW);
    // 设置管理项，item每一项的宽高
    item->setSizeHint(QSize(280,60));
    // 将自定义的Qwidget Item 设置为item的小部件
    ui->contactsListW->setItemWidget(item, firItem);

    // 将该好友项存储
    int itemId = user->uid;
    items[itemId] = firItem;

    // 这里的参数必须是一样的不能是别名 即uing 设置的
    connect(firItem, SIGNAL(sendPage(int, QPointer<OneChat>)), this, SLOT(pushOneChatPage(int, QPointer<OneChat>)));
}

// 画群组列表
void MainWindow::drawGroupList()
{
    for (auto &group : groups)
    {
        drawGroupItem(uid, uname, group);
    }
}
// 画群组列表的每一项
void MainWindow::drawGroupItem(int uid, QString uname, std::shared_ptr<Group> group)
{
    // 创建群组项
    GroupItem *groupItem = new GroupItem(ui->groupW);
    // 设置窗口显示信息
    groupItem->setIdType("群id: ");
    groupItem->setId(group->id);
    groupItem->setNameType("群名称：");
    groupItem->setName(group->name);

    // 设置groupItem成员信息
    groupItem->setGroup(group.get());
    groupItem->setUId(uid);
    groupItem->setUName(uname);

    // 先判断是否有该群组的消息
    if (groupChatMsgs.count(group->id) == 1)
    {
        if (!groupChatMsgs[group->id].empty())
        {
            // 有消息读取消息
            for(auto &groupChatMsg : groupChatMsgs[group->id])
            {
                groupItem->addMsg(groupChatMsg->uname, groupChatMsg->msg);
            }
        }
    }

    // 创建QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->groupListW);
    // 设置管理项，item每一项的宽高
    item->setSizeHint(QSize(280,60));
    // 将自定义的Qwidget Item 设置为item的小部件
    ui->groupListW->setItemWidget(item, groupItem);

    // 将该群组项存储
    int itemId = -group->id;
    items[itemId] = groupItem;
    connect(groupItem, SIGNAL(sendPage(int, QPointer<GroupChat>)), this, SLOT(pushGroupChatPage(int, QPointer<GroupChat>)));
}

// 画消息列表
void MainWindow::drawChatList()
{
    // 先显示好友离线消息
    for (const auto &key : oneChatMsgs.keys())
    {
        drawChatItem(key, oneChatMsgs[key]);
    }
    // 再显示群组离线消息
    for (const auto &key : groupChatMsgs.keys())
    {
        qDebug() << groupChatMsgs[key].size();
        drawChatItem(key, groupChatMsgs[key]);
    }
}
// 画聊天消息列表的每一项
void MainWindow::drawChatItem(int senderId, OneChatMsgs oneChatMsgs)
{
    // 创建好友离线项
    ChatItem *chatItem = new ChatItem(ui->chatW);
    chatItem->setChatTyep(ONECHAT);
    chatItem->setType("好友id：");
    chatItem->setId(senderId);

    //显示好友第一条离线消息
    // 获取第一条离线消息 读取信息结构体中的msg;
    QString str = oneChatMsgs[0]->msg;
    chatItem->setMsg(str);
    chatItem->setSum(oneChatMsgs.size());

    // 创建QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->chatListW);
    // 设置管理项，item每一项的宽高
    item->setSizeHint(QSize(280,60));
    // 将自定义的Qwidget Item 设置为item的小部件
    ui->chatListW->setItemWidget(item, chatItem);
}
void MainWindow::drawChatItem(int senderId, GroupChatMsgs groupChatMsgs)
{
    // 创建群组消息项
    ChatItem *chatItem = new ChatItem(ui->chatW);
    chatItem->setChatTyep(GROUPCHAT);
    chatItem->setType("群组id：");
    chatItem->setId(senderId);

    //显示群组第一条消息
    // 获取第一条离线消息 读取信息结构体中的msg;
    QString str = groupChatMsgs[0]->msg;
    chatItem->setMsg(str);
    chatItem->setSum(groupChatMsgs.size());

    // 创建QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->chatListW);
    // 设置管理项，item每一项的宽高
    item->setSizeHint(QSize(280,60));
    // 将自定义的Qwidget Item 设置为item的小部件
    ui->chatListW->setItemWidget(item, chatItem);
}

//登陆回调
void MainWindow::apiLoginCallback(QJsonObject &jsonObj)
{
    // 设置主界面用户的个人信息
    uid = jsonObj.value("id").toInt();
    uname = jsonObj.value("name").toString();
    ui->useridtext->setNum(uid);
    ui->usernametext->setText(uname);

    // 设置usermodel的信息
    UserModel* user = UserModel::NewInstance();
    user->setid(uid);
    user->setName(uname);

    // 获取离线消息列表
    if (jsonObj.contains("offlinemsg")) // 判断是否有"offlinemsg" 即判断是否有离线消息
    {
        QJsonArray vec = jsonObj.value("offlinemsg").toArray();
        for (int m = 0; m < vec.size(); ++m)
        {
            // QJsonArray 存放的是json的string类型需对其反序列化
            QString objStr = vec[m].toString();
            qDebug() << objStr <<endl;
            QJsonDocument doc = QJsonDocument::fromJson(objStr.toUtf8().data());
            QJsonObject obj = doc.object();
            qDebug() << obj << endl;

            if (ONE_CHAT_MSG == obj.value("msgid").toInt())
            {
                auto msg = std::make_shared<responseChat>();
                msg->uid = obj.value("id").toInt();
                msg->msg = obj.value("msg").toString();

                // 判断好友离线消息中是否已有该好友的消息
                if (!oneChatMsgs.contains(msg->uid))
                {
                    // 没有 初始化该好友的消息
                    OneChatMsgs tmp;
                    this->oneChatMsgs[msg->uid] = tmp;
                }
                // 根据好友uid 插入消息
                this->oneChatMsgs[msg->uid].push_back(msg);
            }
            else if(GROUP_CHAT_MSG == obj.value("msgid").toInt())
            {
                auto msg = std::make_shared<responseGroupChat>();
                msg->groupid = obj.value("groupid").toInt();
                msg->uid = obj.value("id").toInt();
                msg->msg = obj.value("msg").toString();
                msg->uname = obj.value("name").toString();
                // 判断群组离线消息中是否已有该群组的消息
                if (!groupChatMsgs.contains(msg->groupid))
                {
                    // 没有 初始化该群组的消息
                    GroupChatMsgs tmp;
                    this->groupChatMsgs[msg->groupid] = tmp;
                }
                // 根据群组id 插入消息
                this->groupChatMsgs[msg->groupid].push_back(msg);
            }
        }
    }
    // 获取好友列表
    if (jsonObj.contains("friends"))
    {
        QJsonArray vec = jsonObj.value("friends").toArray();
        //qDebug() << vec << endl;
          for (int m = 0; m < vec.size(); ++m)
          {
              // QJsonArray 存放的是json的string类型需对其反序列化
              QString objStr = vec[m].toString();
              QJsonDocument doc = QJsonDocument::fromJson(objStr.toUtf8().data());
              //qDebug() << doc << endl;

              QJsonObject obj = doc.object();
              qDebug() << obj << endl;
              auto user = std::make_shared<UserProfile>(); // 好友信息
              user->uid = obj.value("id").toInt();
              user->name = obj.value("name").toString();
              user->state = obj.value("state").toString();
              firends.push_back(user);
          }
    }
    // 获取群组列表
    if (jsonObj.contains("groups"))
    {
        QJsonArray vec = jsonObj.value("groups").toArray();
          for (int m = 0; m < vec.size(); ++m)
          {
              // QJsonArray 存放的是json的string类型需对其反序列化
              QString objStr = vec[m].toString();
              QJsonDocument doc = QJsonDocument::fromJson(objStr.toUtf8().data());
              QJsonObject obj = doc.object();

              auto group = std::make_shared<Group>(); // 群组信息
              group->id = obj.value("id").toInt();
              group->name = obj.value("groupname").toString();
              group->desc = obj.value("groupdesc").toString();

              QJsonArray vec1 = obj.value("users").toArray();
              for (int n = 0; n < vec1.size(); ++n)
              {
                  // QJsonArray 存放的是json的string类型需对其反序列化
                  QString objStr = vec1[n].toString();
                  QJsonDocument doc = QJsonDocument::fromJson(objStr.toUtf8().data());
                  QJsonObject obj1 = doc.object();

                  // 群组成员信息
                  GroupUser groupUser;
                  groupUser.role = obj1.value("role").toString();
                  groupUser.uid = obj1.value("id").toInt();
                  groupUser.name = obj1.value("name").toString();
                  groupUser.state = obj1.value("state").toString();
                  group->users.push_back(groupUser);
              }
              // 群组列表添加当前一个群组信息
              groups.push_back(group);
          }
    }

    this->login->apiLoginCallback();
    this->drawFriendList();
    this->drawGroupList();
    this->drawChatList();
}

// 单聊回调
void MainWindow::oneChatCallback(QJsonObject &jsonObj)
{
    int firId = jsonObj.value("id").toInt(); // 发信息人的id
    QString firName = jsonObj.value("name").toString(); // 发消息人的名称
    QString msg = jsonObj.value("msg").toString(); // 消息
    OneChatPtr page = oneChatPages[firId]; // 查看已打开的单聊窗口
    if (page.isNull())
    {
        // 收到消息的一方还没打开单聊窗口
       qDebug() << "收到消息,没打开单聊窗口" << endl;
       Alert alertobj;
       QString title("好友Id: %1消息");
       alertobj.setTitle(title.arg(firId));
       alertobj.setButtonContent("ok");
       alertobj.exec();

       // 将收到的消息发送给相对应的好友项
       items[firId]->addMsg(firName, msg);
    }
    else
    {
        // 收到消息的一方已经打开 显示信息
        qDebug() << "收到消息,打开聊天窗口" << endl;
        QString name = jsonObj.value("name").toString();
        QString msg = jsonObj.value("msg").toString();
        page->recvMsg(name, msg);
    }

}
// 群聊回调
void MainWindow::GroupChatCallback(QJsonObject &jsonObj)
{
    int groupId = jsonObj.value("groupid").toInt(); // 群组id
    QString name = jsonObj.value("name").toString(); // 群组发送消息的成员名称
    QString msg = jsonObj.value("msg").toString(); // 消息
    GroupChatPtr page = groupChatPages[groupId];
    if (page.isNull())
    {
        // 收到消息的一方还没打开群聊窗口
       qDebug() << "收到消息,没打开单聊窗口" << endl; 
       Alert alertobj;
       QString title("群组id: %1消息");
       alertobj.setTitle(title.arg(groupId));
       alertobj.setButtonContent("ok");
       alertobj.exec();

       // 将收到的消息存储
        items[-groupId]->addMsg(name, msg);
    }
    else
    {
        // 收到消息的一方已经打开 显示信息
        page->recvMsg(name, msg);
    }
}


// 存储已经打开的好友聊天窗口
void MainWindow::pushOneChatPage(int id, QPointer<OneChat> oneChatPtr)
{
    oneChatPages[id] = oneChatPtr;
    qDebug() << id << endl;
}
// 存储已经打开的群组聊天窗口
void MainWindow::pushGroupChatPage(int id, GroupChatPtr groupchatPtr)
{
    groupChatPages[id] = groupchatPtr;
}
void MainWindow::on_btnMin_clicked()
{
    // 最小化窗口
    this->showMinimized();
}

void MainWindow::on_btnClose_clicked()
{
    // 释放用户资源，关闭客户端与服务器连接
    delete UserModel::NewInstance();
    // 关闭窗口
    this->close();
}

void MainWindow::on_chat_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_contacts_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_group_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}
// 添加好友
void MainWindow::on_but1_clicked()
{
    InputPopup inputObj;
    inputObj.setinputText1("好友id：");
    inputObj.hideInput2();
    inputObj.setButtonContent("确定");
    inputObj.exec();

    UserModel* user = UserModel::NewInstance();
    if (inputObj.id > 0)
    {
        user->addFriend(inputObj.id);
    }
}

// 创建群聊
void MainWindow::on_but2_clicked()
{
    InputPopup inputObj;
    inputObj.setinputText1("群组名称：");
    inputObj.setinputText2("群组描述：");
    inputObj.setButtonContent("创建");
    inputObj.exec();

    UserModel* user = UserModel::NewInstance();
    QString groupName = inputObj.input1;
    QString groupDesc = inputObj.input2;
    if (!groupName.isEmpty())
    {
        user->createGroup(groupName,groupDesc);
    }
}

// 加入群聊
void MainWindow::on_but3_clicked()
{
    InputPopup inputObj;
    inputObj.setinputText1("群组id：");
    inputObj.hideInput2();
    inputObj.setButtonContent("确定加入");
    inputObj.exec();

    UserModel* user = UserModel::NewInstance();
    int id = inputObj.id;
    qDebug() << id <<endl;
    if (id>0)
    {
        user->addGroup(inputObj.id);
    }
}

// 注销用户
void MainWindow::on_but4_clicked()
{
    UserModel* user = UserModel::NewInstance();
    user->loginOut(uid);
}
