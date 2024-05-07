#include "clientnet.h"
#include "../route/msg.h"
#include "../route/route.h"

#include <cstring>

#include <QString>


//包最大字节数限制为10M
#define MAX_PACKAGE_SIZE    10 * 1024 * 1024

ClientNet::ClientNet(QWidget *parent)
    : QWidget(parent)
    , connfd(-1)
    , conn(nullptr)
{
    //qDebug() << "net构造构" << endl;
}
ClientNet::~ClientNet()
{
    if (conn != nullptr)
    {
        //qDebug() << "析构" << endl;
        conn->disconnectFromHost();
        delete conn;
        conn = nullptr;
    }
}
//静态变量的初始化必须定义在外面
ClientNet* ClientNet::singleObj = NULL;

ClientNet* ClientNet::NewInstance(){
    if(singleObj == NULL){
        singleObj = new ClientNet();
        if (!singleObj->connectByQtSocket())
        {
            // 连接失败
            delete singleObj;
            return singleObj = nullptr;
        }
    }
    return singleObj;
}


//连接服务器
bool ClientNet::connectByQtSocket(){
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost(ClientNet::IP, ClientNet::PORT);
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    if(!socket->waitForConnected()){
        qDebug() << "连接失败" << endl;
        delete socket;
        return false;
    }
    // 连接成功
    conn = socket;
    //注册槽函数，
    //@param1 被触发的对象
    //@param2 被触发的事件
    //@param3 信号处理的类
    //@param4 信号处理的函数
    connect(conn, &QTcpSocket::readyRead, this, &ClientNet::slotRecvMsg);
    return true;
}


//1、处理tcp的connect信号函数
//1.1、处理收到的消息由route解析出来，分配给各个interface
//2、
//2.1、异步接收到的回调函数也放在route里面，然后由route分配给各个interface
//2.2、ClientNet::sendMsg(std::string msg)为纯string，由model封装好之后传进来
//3、业务login,chat等
bool ClientNet::sendMsg(std::string &msg){
    if (!this->conn->waitForConnected())
    {
        qDebug() << "连接断开" << endl;
        return false;
    }

    std::string strPackageData;
    MsgHeader header;
    header.bodySize = msg.size();
    // 插入包头
    strPackageData.append((const char*)&header, sizeof(header));
    strPackageData.append(msg);

    int returnWriteNum = this->conn->write(strPackageData.c_str(),strPackageData.length() + 1);
    QString qString = QString::fromStdString(strPackageData);
    qDebug() << qString.toUtf8() << endl;
    qDebug() << header.bodySize << endl;
    qDebug() << "确定发送长度：" << returnWriteNum << endl;
    return  true;
}

void ClientNet::slotRecvMsg()
{
    QByteArray buffer = this->conn->readAll();
    MsgHeader header;
    memset(&header, 0, sizeof header);
    memcpy(&header,buffer,sizeof(MsgHeader));
    qDebug() << buffer.toHex()<< endl;
    qDebug() << header.bodySize << endl;

//    // 服务器发送的消息错误
//    if (header.bodySize <= 0 ||
//            header.bodySize > MAX_PACKAGE_SIZE)
//    {
//        qDebug() << "收到服务器的消息错误" << endl;
//        return;
//    }
//    // 收到的数据不够一个完整的包
//    if ((uint)buffer.size() < (uint)header.bodySize + sizeof(MsgHeader))
//    {
//        //qDebug() << buffer<< endl;
//        qDebug() << "收到服务器的消息不完整" << endl;
//        return;
//    }

    // 获取主体消息
    // mid(1,3)：从第1 个后截取后面3个字符: 这里提取json主体消息
    QString msgByte = buffer.mid(sizeof (MsgHeader));

    //qDebug() << msgByte << endl;
    Route* route = Route::NewInstance();
    route->distributeRecvMsg(msgByte);
}
