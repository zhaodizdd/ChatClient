#ifndef RESPONSESTRUCT_H
#define RESPONSESTRUCT_H
// 服务器返回的信息的各种类型
// 返回的信息中都会有msgid 因route会提前提前出他来选择不同的业务
// 故下面的消息结构都剔除掉了msgid
#include <QString>
#include <QVector>


// 个人信息结构体
struct UserProfile
{
    int uid;
    QString name;
    QString state = "offline";
};

// 群组用户结构
struct GroupUser : public UserProfile
{
    QString role; //群组角色（创建者/组员）
};

// 群组结构
struct Group
{
    int id;             // 群组id
    QString name;       // 群组名称
    QString desc;       // 群组的描述
    QVector<GroupUser> users;   // 群组成员
};

// 一对一聊天消息
struct responseChat{
    int uid; //发送者
    int toid; // 接受者
    QString uname; // 发送者名称
    QString msg; // 发送内容
};

// 群聊消息
struct responseGroupChat : public responseChat{
    int groupid;    // 群组id
};

// 用户登录成功返回的信息
struct responseUserInfo{
    int errno;
    int uid;
    QString username;
    QVector<responseChat> offlinemsg; //离线消息
    QVector<UserProfile> friends; // 好友信息 存储的是json序列后的string
    QVector<Group> groups; // 群组
};

// 注册返回的信息
struct responseReg{
    int errno;
    int id;
};


#endif // RESPONSESTRUCT_H
