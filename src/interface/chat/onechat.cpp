#include "onechat.h"
#include "ui_onechat.h"
#include "../../models/usermodel.h"
#include "../../route/msg.h"

#include <QJsonObject>

#include <QColorDialog>
OneChat::OneChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneChat)
{
    qDebug() << "创建" << endl;
    ui->setupUi(this);
}

OneChat::~OneChat()
{
    qDebug() << "析构";
    delete ui;
}


// 发送消息
void OneChat::sendMsg(QString msg)
{
    UserModel* user = UserModel::NewInstance();

    // 组装单聊的json对象
    QJsonObject json;
    json.insert("msgid", ONE_CHAT_MSG);
    json.insert("id", uid);
    json.insert("name", uname);
    json.insert("toid", firendId);
    json.insert("msg", msg);

    if (!user->sendMag(json))
    {
        qDebug() << "消息发送失败" << endl;
    }
}

// 收到消息 参数一发送者的名称
void OneChat::recvMsg(QString name, QString msg)
{
    QString str = "<span style='color:red;'>" + name + "</span>";
    ui->msgBrowser->append(str);
    ui->msgBrowser->setAlignment(Qt::AlignLeft);
    ui->msgBrowser->append(msg);
}


void OneChat::on_close_clicked()
{
   this->close();
}

void OneChat::on_sendMsg_clicked()
{
    //以纯文本的方式获取文本框的内容（不含格式）
    QString msg=ui->msgTxtEdit->document()->toPlainText();
    if (!msg.isEmpty())
    {
        //以html的方式获取文本框的内容（含格式）
        QString strHtml=ui->msgTxtEdit->document()->toHtml();
        QString message = "<div align='right' >" + strHtml + "</div>";
        QString name = "<span style='color:blue;'>" + uname + "</span>";
        // 自己发送的消息靠右边对其
        ui->msgBrowser->append(name);
        ui->msgBrowser->setAlignment(Qt::AlignRight);
        ui->msgBrowser->append(message);

        // 清空输入框
        ui->msgTxtEdit->clear();

        this->sendMsg(msg);
    }
}

void OneChat::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setFontFamily(f.toString());
    ui->msgTxtEdit->setFocus();
}

void OneChat::on_sizeBox_currentTextChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}


void OneChat::on_toolButton_clicked(bool checked)
{
    if (checked)
    {
        ui->msgTxtEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->msgTxtEdit->setFontWeight(QFont::Normal);
    }
}

void OneChat::on_toolButton_2_clicked(bool checked)
{
    ui->msgTxtEdit->setFontItalic(checked);
    ui->msgTxtEdit->setFocus();
}

void OneChat::on_toolButton_3_clicked(bool checked)
{
    ui->msgTxtEdit->setFontUnderline(checked);
    ui->msgTxtEdit->setFocus();
}

void OneChat::on_toolButton_4_clicked()
{
    QColor color = QColorDialog::getColor(color, this);

    ui->msgTxtEdit->setTextColor(color);
}

void OneChat::on_toolButton_6_clicked()
{
    ui->msgTxtEdit->clear();
}
