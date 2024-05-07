#ifndef GROUPCAHT_H
#define GROUPCAHT_H

#include "../../route/responsestruct.h"

#include <QWidget>

namespace Ui {
class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChat(QWidget *parent = nullptr);
    ~GroupChat();

    void setUid(int id) { uid = id; }
    void setUName(QString name) { uname = name; }
    void setGroup(Group *group) { this->group = group; }
    virtual void show();

    // 发送消息
    void sendMsg(QString msg);

    // 收到消息 参数一发送者的名称
    void recvMsg(QString name, QString msg);

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_sizeBox_currentTextChanged(const QString &arg1);

    void on_toolButton_clicked(bool checked);

    void on_toolButton_2_clicked(bool checked);

    void on_toolButton_3_clicked(bool checked);

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();


    void on_close_clicked();

    void on_sendMsg_clicked();

private:
    Ui::GroupChat *ui;
    int uid;   // 当前用户的id
    QString uname;  // 当前用户的名称
    Group *group; // 群组信息
};

#endif // GROUPCAHT_H
