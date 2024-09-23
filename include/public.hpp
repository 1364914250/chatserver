#ifndef PUBLIC_H
#define PUBLIC_H

/*
server 和 client的公共文件
*/

// 使用强类型枚举，避免全局的枚举变量的影响且更加安全，且可以指定类型
enum EnMsgType
{
    LOGIN_MSG = 1,    // 登录消息
    LOGIN_MSG_ACK,    // 登录响应消息。
    REG_MSG,          // 注册消息
    REG_MSG_ACK,      // 注册响应消息
    ONE_CHAT_MSG,     // 一对一聊天信息
    ADD_FRIEND_MSG,   // 添加好友信息
    CREATE_GROUP_MSG, // 创建群组
    ADD_GROUP_MSG,    // 加入群组
    GROUP_CHAT_MSG,    // 群聊天
    LOGINOUT_MSG
};

#endif