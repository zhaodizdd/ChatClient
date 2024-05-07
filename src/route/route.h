#ifndef ROUTE_H
#define ROUTE_H

#include "msg.h"
#include "../interface/login/login.h"
#include "../interface/main/mainwindow.h"

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

class Route : public QWidget
{
public:
    Route(QWidget *parent = nullptr);
    static Route* NewInstance();


public:
    void distributeRecvMsg(QString msg);
    void setLoginInterface(Login* mylogin);
    void setMainWindowInterface(MainWindow* myMainWindow);

private:
    static Route* singleObj;

    Login* myLoginInterface;
    MainWindow* myMainWindowInterface;
};

#endif // ROUTE_H
