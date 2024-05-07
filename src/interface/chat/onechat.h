#ifndef ONECHAT_H
#define ONECHAT_H

#include <QWidget>

namespace Ui {
class OneChat;
}

class OneChat : public QWidget
{
    Q_OBJECT

public:

    ~OneChat();
public:
    OneChat(QWidget *parent = nullptr);

    void setUId(int id) { uid = id; }
    void setFirendid(int id) {  firendId = id; }
    void setUName(QString name) { uname = name; }
    void setFirendName(QString name) { firendName = name; }

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
    int uid;       // 记录用户id
    QString uname; // 记录用户名称
    int firendId;     // 记录好友id
    QString firendName; // 记录好友名称

private:
    Ui::OneChat *ui;
};

#endif // ONECHAT_H
