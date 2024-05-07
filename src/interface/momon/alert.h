#ifndef ALERT_H
#define ALERT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Alert; }
QT_END_NAMESPACE

class Alert : public QDialog
{
    Q_OBJECT
public:
    Alert(QDialog *parent = nullptr);
    ~Alert();

    void setTitle(QString title);
    void setMsg(QString content);
    void setButtonContent(QString bc);
    virtual int exec();
private slots:
    void on_closeButton_clicked();

private:
    Ui::Alert *ui;
    QString title;
    QString msg;
    QString buttonContent = "OK";
};

#endif // ALERT_H
