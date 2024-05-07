#include "firenditem.h"
#include "../momon/alert.h"

FirendItem::FirendItem(QWidget *parent)
    : Item(parent)
    , oneChatPtr(nullptr)
{}

FirendItem::~FirendItem(){}

// 设置FirendItem的单击事件
void FirendItem::mousePressEvent(QMouseEvent *)
{
    if(oneChatPtr.isNull())
    {
        oneChatPtr = QPointer<OneChat>(new OneChat);

        // 设置单聊窗口的信息
        oneChatPtr->setUId(uid);
        oneChatPtr->setUName(uname);
        oneChatPtr->setFirendid(firendId);
        oneChatPtr->setFirendName(firendName);
        oneChatPtr->setWindowTitle("好友名称：" + firendName);

        for (auto &msg : firendMsg)
        {
            oneChatPtr->recvMsg(firendName, msg);
        }

        oneChatPtr->show();
        // 设置当指向的对象窗口关闭时,同时释放掉资源
        oneChatPtr->setAttribute(Qt::WA_DeleteOnClose);

        // 将单聊窗口传递给父窗口MainWindow
        emit sendPage(firendId,oneChatPtr);
    }
    else
    {
        Alert alertObj;
        alertObj.setTitle("该聊天窗口已打开!");
        alertObj.setButtonContent("ok");
        alertObj.exec();
    }
}
