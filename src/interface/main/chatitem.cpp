#include "chatitem.h"
#include "ui_chatitem.h"

ChatItem::ChatItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatItem)
{
    ui->setupUi(this);
}

ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::setType(QString type) { ui->type->setText(type); }
void ChatItem::setId(int id) { ui->name->setNum(id); this->id = id; }
void ChatItem::setMsg(QString msg) { ui->msg->setText(msg); }
void ChatItem::setSum(int n) { ui->sum->setNum(n);}


// 单击事件回调
void ChatItem::mousePressEvent(QMouseEvent *event)
{

}
