#include "alert.h"
#include "ui_alert.h"

Alert::Alert(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Alert)
{
    ui->setupUi(this);
}

Alert::~Alert()
{
    delete ui;
}

void Alert::on_closeButton_clicked()
{
    this->close();
}

void Alert::setTitle(QString title){
    this->title = title;
}

void Alert::setMsg(QString msg){
    this->msg = msg;
}

void Alert::setButtonContent(QString bc){
    this->buttonContent = bc;
}

int Alert::exec(){
    ui->label->setText(this->title);
    ui->msg->setText(this->msg);
    ui->closeButton->setText(this->buttonContent);
    return QDialog::exec();
}

