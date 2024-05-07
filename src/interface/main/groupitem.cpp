#include "groupitem.h"
#include "../momon/alert.h"

GroupItem::GroupItem(QWidget *parent)
    : Item(parent)
    , groupChatPtr(nullptr)
{
}

GroupItem::~GroupItem()
{
}

void GroupItem::addMsg(QString name, QString msg)
{
    qDebug() << "Groupitem";
    std::shared_ptr<GroupMsg> groupMsg(new GroupMsg());
    groupMsg->name = name;
    groupMsg->msg = msg;

    groupMsgs.push_back(groupMsg);

}

// 设置GroupItem的单击事件
void GroupItem::mousePressEvent(QMouseEvent *event)
{
    if(groupChatPtr.isNull())
    {
        groupChatPtr = QPointer<GroupChat>(new GroupChat());
        // 将new的单聊窗口传递给父窗口MainWindow
        emit sendPage(group->id, groupChatPtr);

        // 设置群聊窗口的信息
        groupChatPtr->setUid(uid);
        groupChatPtr->setUName(uname);
        groupChatPtr->setGroup(group);
        groupChatPtr->setWindowTitle("群组名称：" + group->name);

        for(const auto &groupMsg : groupMsgs)
        {
            groupChatPtr->recvMsg(groupMsg->name, groupMsg->msg);
        }

        groupChatPtr->show();
        // 设置当指向的对象窗口关闭时,同时释放掉资源
        groupChatPtr->setAttribute(Qt::WA_DeleteOnClose);

        // 将单聊窗口传递给父窗口MainWindow
        emit sendPage(group->id,groupChatPtr);
    }
    else
    {
        Alert alertObj;
        alertObj.setTitle("该聊天窗口已打开!");
        alertObj.setButtonContent("ok");
        alertObj.exec();
    }
}
