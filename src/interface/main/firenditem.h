#ifndef FIRENDITEM_H
#define FIRENDITEM_H

#include "item.h"
#include "../chat/onechat.h"

#include <QWidget>
#include <QPointer>

class FirendItem : public Item
{
// 自定义类使用Q_OBJECT必须修改一下pro 重新make一下， 就会重新qmake  pro文件
    Q_OBJECT
public:
    FirendItem(QWidget *parent = nullptr);
    ~FirendItem();

public:
    void setFirendId(int id) { firendId = id; }
    void setFirendName(QString name) { firendName = name; }
    void addMsg(QString name, QString msg) { qDebug() << "Frienditem"; firendMsg.push_back(msg);}
    // 单击事件回调
    void mousePressEvent(QMouseEvent *event);

// 这里使用signals必须有Q_OBJECT 这个宏定义
signals:
    void sendPage(int id, QPointer<OneChat> oneChatPtr);

private:
    int firendId;     // 好友 id
    QString firendName; // 好友 名称
    QVector<QString> firendMsg; // 好友消息

    // 使用QPointer解决指针悬挂问题,当指针指向的对象析构时, 他会自动将其设置为nullptr
    QPointer<OneChat> oneChatPtr;
};

#endif // FIRENDITEM_H
