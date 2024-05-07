#ifndef IPUTPOPUP_H
#define IPUTPOPUP_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class InputPopup; }
QT_END_NAMESPACE

// 这是一个公共的输入弹窗类 用与注册、添加好友、创建群组、加入群组
class InputPopup : public QDialog
{
    Q_OBJECT
public:
    InputPopup(QDialog *parent = nullptr);
    ~InputPopup();

    void setinputText1(QString inputText1);
    void setinputText2(QString inputText2);
    void setButtonContent(QString bc);
    void hideInput2();

private slots:
    void on_pushButton_clicked();

public:
    int id;             // 保存第一个输入框的数据（输入框类型可能不一）
    QString input1;     // 保存第一个输入框的数据
    QString input2;     // 保存第二个输入框的数据

private:
    Ui::InputPopup *ui;

};

#endif // IPUTPOPUP_H
