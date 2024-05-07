#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../login/login.h"
#include "../../route/responsestruct.h"
#include "../chat/onechat.h"
#include "../chat/groupchat.h"
#include "item.h"

#include <QMainWindow>
#include <QJsonObject>
#include <QVector>
#include <QMap>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum ChatType // 聊天消息的类型
    {
        ONECHAT, // 单聊
        GROUPCHAT //群聊
    };

    using OneChatMsgs = QVector<std::shared_ptr<responseChat>>;
    using Firends = QVector<std::shared_ptr<UserProfile>>;
    using GroupChatMsgs = QVector<std::shared_ptr<responseGroupChat>>;
    using Groups = QVector<std::shared_ptr<Group>>;
    using OneChatPtr = QPointer<OneChat>;
    using GroupChatPtr = QPointer<GroupChat>;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void setLogin(Login* mylogin){ login = mylogin;}
    int getUId() {return uid; }
    QString getUName() {return uname; }

    // 获取群组信息
    Groups& getGroups() { return groups; }
    // 获取好友信息
    Firends& getFirends() { return firends; }
    // 登陆回调
    void apiLoginCallback(QJsonObject &jsonObj);
    // 单聊回调
    void oneChatCallback(QJsonObject &jsonObj);
    // 群聊回调
    void GroupChatCallback(QJsonObject &jsonObj);

public:
    void drawFriendList(); //画好友列表
    void drawFriendItem(int uid, QString uname, std::shared_ptr<UserProfile> user);
    void drawGroupList(); // 画群组列表
    void drawGroupItem(int uid, QString uname, std::shared_ptr<Group> group);
    void drawChatList(); // 画聊天消息列表
    void drawChatItem(int senderId, OneChatMsgs oneMsgs);  // 画聊天消息列表的每一项
    void drawChatItem(int senderId, GroupChatMsgs groupChatMsgs);
    void mousePressEvent(QMouseEvent *event);//单击鼠标，可以判断左右键
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标点击后的释放

private slots:
    // 存储已经打开的好友聊天窗口
    void pushOneChatPage(int id, QPointer<OneChat> oneChatPtr);
    // 存储已经打开的群组聊天窗口
    void pushGroupChatPage(int id, QPointer<GroupChat> groupchatPtr);

    void on_btnMin_clicked();

    void on_btnClose_clicked();

    void on_chat_clicked();

    void on_contacts_clicked();

    void on_group_clicked();

    void on_but1_clicked();

    void on_but2_clicked();

    void on_but3_clicked();

    void on_but4_clicked();

private:
    Ui::MainWindow *ui;
    Login *login;

    //当前login界面是否有被鼠标选中后移动
    bool m_moving = false;

    //当前login界面移动的距离
    QPoint m_lastPos;

private:
    int uid;            // 用户id
    QString uname;       // 用户名
    Firends firends;   // 好友信息
    Groups groups; // 群组信息
    QMap<int, OneChatMsgs> oneChatMsgs; //好友离线消息
    QMap<int, GroupChatMsgs> groupChatMsgs; //群聊离线消息
    QMap<int, OneChatPtr> oneChatPages;       // 存储打开的单聊窗口 <好友id，单聊页面>
    QMap<int, GroupChatPtr> groupChatPages;   // 存储打开的群聊窗口 <群组id, 群聊页面>
    QMap<int, Item*> items; // 存储好友和群组列表 (参数一是好友或者群组id的负数）
};

#endif // MAINWINDOW_H
