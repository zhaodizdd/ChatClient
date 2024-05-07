#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

    void mousePressEvent(QMouseEvent *event);//单击鼠标，可以判断左右键
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标点击后的释放

public:
    void apiLoginCallback();

private slots:
    void on_btnMin_clicked();

    void on_btnClose_clicked();

    void on_loginBut_clicked();

    void on_userid_textChanged(const QString &arg1);

    void on_password_textChanged(const QString &arg1);

    void on_registerBut_clicked();

private:
    Ui::Login *ui;

    //账号id
    int id;

    //密码
    QString password;

    //uid
    int uid = 0;

    //当前login界面是否有被鼠标选中后移动
    bool m_moving = false;
    //当前login界面移动的距离
    QPoint m_lastPos;
};
#endif // LOGIN_H
