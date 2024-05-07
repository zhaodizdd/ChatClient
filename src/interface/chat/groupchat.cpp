#include "groupchat.h"
#include "ui_groupchat.h"
#include "../../models/usermodel.h"
#include "../../route/msg.h"
#include <QColorDialog>
#include <QJsonObject>

GroupChat::GroupChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
}

GroupChat::~GroupChat()
{
    delete ui;
}

// 发送消息
void GroupChat::sendMsg(QString msg)
{
    UserModel* user = UserModel::NewInstance();

    // 组装单聊的json对象
    QJsonObject json;
    json.insert("msgid", GROUP_CHAT_MSG);
    json.insert("id", uid);
    json.insert("name", uname);
    json.insert("groupid", group->id);
    json.insert("msg", msg);

    if (!user->sendMag(json))
    {
        qDebug() << "消息发送失败" << endl;
    }
}

// 收到消息 参数一发送者的名称
void GroupChat::recvMsg(QString name, QString msg)
{
    QString str = "<span style='color:red;'>" + name + "</span>";
    ui->msgBrowser->append(str);
    ui->msgBrowser->setAlignment(Qt::AlignLeft);
    ui->msgBrowser->append(msg);
}

void GroupChat::show()
{
    // 画群组中的好友信息
    // 先设置表格的行数
    int row = group->users.size();
    ui->userTable->setRowCount(row);
    ui->userTable->setColumnCount(3);
    // 设置表头
    ui->userTable->setHorizontalHeaderLabels(QStringList() << "用户id" << "用户名" << "角色");
    // 设置表格的所有信息不可编辑
    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置每一行的内容
    for (int i = 0; i < row; ++i)
    {
        ui->userTable->setItem(i,0,new QTableWidgetItem(QString::number(group->users[i].uid)));
        ui->userTable->setItem(i,1,new QTableWidgetItem(group->users[i].name));
        ui->userTable->setItem(i,2,new QTableWidgetItem(group->users[i].role));
    }

    QWidget::show();
}

void GroupChat::on_close_clicked()
{
   this->close();
}

void GroupChat::on_sendMsg_clicked()
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

void GroupChat::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setFontFamily(f.toString());
    ui->msgTxtEdit->setFocus();
}

void GroupChat::on_sizeBox_currentTextChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}


void GroupChat::on_toolButton_clicked(bool checked)
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

void GroupChat::on_toolButton_2_clicked(bool checked)
{
    ui->msgTxtEdit->setFontItalic(checked);
    ui->msgTxtEdit->setFocus();
}

void GroupChat::on_toolButton_3_clicked(bool checked)
{
    ui->msgTxtEdit->setFontUnderline(checked);
    ui->msgTxtEdit->setFocus();
}

void GroupChat::on_toolButton_4_clicked()
{
    QColor color = QColorDialog::getColor(color, this);

    ui->msgTxtEdit->setTextColor(color);
}

void GroupChat::on_toolButton_6_clicked()
{
    ui->msgTxtEdit->clear();
}
