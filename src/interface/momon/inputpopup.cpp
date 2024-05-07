#include "inputpopup.h"
#include "ui_inputpopup.h"


InputPopup::InputPopup(QDialog *parent)
    : QDialog(parent)
    , id(-1)
    , ui(new Ui::InputPopup)
{
    ui->setupUi(this);
}
InputPopup::~InputPopup()
{
    delete ui;
}

void InputPopup::setinputText1(QString inputText1)
{
    ui->inputtext1->setText(inputText1);
}
void InputPopup::setinputText2(QString inputText2)
{
    ui->inputtext2->setText(inputText2);
}
void InputPopup::setButtonContent(QString bc)
{
    ui->pushButton->setText(bc);
}

void InputPopup::hideInput2()
{
    ui->input2->hide();
}


void InputPopup::on_pushButton_clicked()
{
    // 获取第一个输入框的值
    QString str = ui->input1->text();
    if (!str.isEmpty())
    {
        // 第一个输入框中可能输入数字也可能输入字符串
        // 先判断str是否为数字
        bool inInt;
        str.toInt(&inInt);
        if (inInt)
        {
            id = str.toInt();
            input1 = str;
        }
        else
            input1 = str;
    }
    // 获取第二个输入框的值
    if (!ui->input2->text().isEmpty())
    {
        input2 = ui->input2->text();
    }

    this->close();
}

