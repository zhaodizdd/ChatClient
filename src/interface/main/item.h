#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT


public:
    Item(QWidget *parent = nullptr);
    ~Item();

    // 设置用户信息
    void setUId(int id) { uid = id; }
    void setUName(QString name) { uname = name; }

    // 设置item窗口显示的内容
    void setIdType(QString IdType);
    void setNameType(QString nameType);
    void setId(int id);
    void setName(QString name);
    virtual void setState(QString state);
    virtual void addMsg(QString name, QString msg){};

protected:
    Ui::Item *ui;
    int uid;    // 记录用户自己的id
    QString uname;     // 用户名
};

#endif // ITEM_H
