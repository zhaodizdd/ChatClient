#ifndef CLIENTNET_H
#define CLIENTNET_H

#include <unistd.h>

#include <QDebug>
#include <QTcpSocket>
#include <QWidget>

class ClientNet : public QWidget
{
public:
    ~ClientNet();
    static ClientNet* NewInstance();

public:
    //发送string
    bool sendMsg(std::string &msg);

    //通过qt自己封装的socket连接
    bool connectByQtSocket();

public slots:
    //接受string
    void slotRecvMsg();

public:
    // 这里直接写的服务器的地址和端口号，未将其设置未配置文件。
    const char IP[16] = "192.168.117.132";
    const int PORT = 8000;
private:
    ClientNet(QWidget *parent = nullptr);
    static ClientNet* singleObj;
    int connfd;
    QTcpSocket* conn;
};

#endif // CLIENTNET_H
