#include "login.h"
#include "ui_login.h"
#include "src/models/usermodel.h"
#include "src/interface/momon/alert.h"
#include "src/interface/momon/inputpopup.h"

#include <iostream>

#include <QPainter>
#include <QMouseEvent>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    // 去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    // 背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    // 设置用户id只能是数字
    ui->userid->setValidator(new QIntValidator(ui->userid));
}

Login::~Login()
{
    delete ui;
}

void Login::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        m_moving = true;
        //鼠标按下时，鼠标相对屏幕的位置减去窗口相对屏幕的位置
        //event->globalPos()和pos()返回(x, y)，x相对于屏幕左下角距离。y相对于屏幕左上角距离
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);
}

void Login::mouseMoveEvent(QMouseEvent *event){
    if (m_moving  && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void Login::mouseReleaseEvent(QMouseEvent *event){
    m_moving = false;
    return QDialog::mouseReleaseEvent(event);
}

void Login::on_btnMin_clicked()
{
    // 最小化窗口
    this->showMinimized();
}

void Login::on_btnClose_clicked()
{
    // 关闭窗口
    this->close();
}

void Login::on_loginBut_clicked()
{
    UserModel* user = UserModel::NewInstance();
    if (!user->login(id, password))
    {
        Alert alertObj;
        alertObj.setTitle("Login Failed");
        alertObj.setMsg("发送失败，请检查网络或服务器未连接");
        alertObj.setButtonContent("OK");
        alertObj.exec();

        delete user;
    }
}

void Login::apiLoginCallback()
{
    // 登录成功关闭当前窗口
    this->accept();
}

void Login::on_userid_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty())
    {
        id = std::stoi(arg1.toStdString());
    }
}

void Login::on_password_textChanged(const QString &arg1)
{
    password = arg1;
}

void Login::on_registerBut_clicked()
{
    InputPopup inputObj;
    inputObj.setinputText1("用户名称：");
    inputObj.setinputText2("用户密码：");
    inputObj.setButtonContent("注册");
    inputObj.exec();

    UserModel* user = UserModel::NewInstance();
    QString name = inputObj.input1;
    QString password = inputObj.input2;
    if (name != nullptr && password != nullptr)
    {
        if (!user->reg(name, password))
        {
            Alert alertObj;
            alertObj.setTitle("Register Failed");
            alertObj.setMsg("发送失败，请检查网络或服务器未连接");
            alertObj.setButtonContent("OK");
            alertObj.exec();
        }
    }
}
