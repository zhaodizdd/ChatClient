#ifndef MSG_H
#define MSG_H

// 服务端与客户端通信消息协议
#include <QtGlobal>

enum EnMsgType
{
    LOGIN_MSG = 1,    // 登录消息
    LOGIN_MSG_ACK,    // 登录响应消息
    LOGINOUT_MSG,     // 注销消息
    LOGINOUT_MSG_ACk, // 注销响应消息
    REG_MSG,          // 注册消息
    REG_MSG_ACK,      // 注册响应消息
    ONE_CHAT_MSG,     // 聊天消息
    ADD_FRIEND_MSG,   // 添加好友消息
    ADD_FRIEND_MSG_ACK,   // 添加好友响应消息

    CREATE_GROUP_MSG, // 创建群组
    CREATE_GROUP_MSG_ACK, // 创建群组
    ADD_GROUP_MSG,    // 加入群组
    ADD_GROUP_MSG_ACK,    // 加入群组响应消息
    GROUP_CHAT_MSG,   // 群聊天
};

enum EnErrnoType
{
    ERROR_OK=0,
    ERROR_LOGIN_1,       // 没有该用户
    ERROR_LOGIN_2,       // 用户已登录
    ERROR_REG_1          // 注册失败
};

struct MsgHeader
{
    qint32 bodySize;        // 消息长度
    char   reserved[16]= {0};  // 预留位
};


#endif // MSG_H
