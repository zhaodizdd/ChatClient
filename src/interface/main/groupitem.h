#ifndef GROUPITEM_H
#define GROUPITEM_H

#include "item.h"
#include "../../route/responsestruct.h"
#include "../chat/groupchat.h"

#include <memory>

#include <QWidget>
#include <QPointer>

struct GroupMsg
{
    QString name;
    QString msg;
};

class GroupItem : public Item
{
    Q_OBJECT
public:
    GroupItem(QWidget *parent = nullptr);
    ~GroupItem();

    void setGroup(Group *group){ this->group = group; }
    void addMsg(QString name, QString msg);
    // 单击事件回调
    void mousePressEvent(QMouseEvent *event);


// 这里使用signals必须有Q_OBJECT 这个宏定义
signals:
    void sendPage(int id, QPointer<GroupChat> GroupChatPtr);

private:
    // 使用QPointer解决指针悬挂问题,当指针指向的对象析构时, 他会自动将其设置为nullptr
    QPointer<GroupChat> groupChatPtr;

    Group *group; // 群组信息
    QVector<std::shared_ptr<GroupMsg>> groupMsgs;
};

#endif // GROUPITEM_H
