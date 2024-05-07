#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>

namespace Ui {
class ChatItem;
}

class ChatItem : public QWidget
{
    Q_OBJECT

// 这里使用signals必须有Q_OBJECT 这个宏定义
signals:
    void sendPage(int id);


public:
    explicit ChatItem(QWidget *parent = nullptr);
    ~ChatItem();

    void setChatTyep(int type) { chatType = type; }

    void setType(QString type);
    void setId(int id);
    void setMsg(QString msg);
    void setSum(int n);

    // 单击事件回调
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::ChatItem *ui;
    int id; // 存放聊天消息的id（群组或好友）
    int chatType; // 聊天类型
};

#endif // CHATITEM_H
