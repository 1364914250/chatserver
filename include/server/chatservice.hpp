#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map> //一个消息ID映射一个事件处理
#include <functional>
#include <mutex>
using namespace std;
using namespace muduo;
using namespace muduo::net;
#include "offlinemessagemodel.hpp"
#include "usermodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"

#include "json.hpp"
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型，事件处理器，派发3个东西
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //  客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 服务器异常，业务重置方法
    void reset();

    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

private:
    ChatService(); // 单例

    // 存储消息id和其对应的业务处理方法，消息处理器的一个表，写消息id对应的处理操作
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储用户id和其对应的长连接
    unordered_map<int, TcpConnectionPtr> _userConnectionMap;

    // 定义互斥锁 保证_userConnectionMap线程安全
    mutex _connMutex;

    // user表的数据操作类
    UserModel _userModel;

    // offlinemessage表的数据操作类
    OffLineMsgModel _offlineMsgModel;

    // friend表的数据操作类
    FriendModel _friednMode;

    // 群组表的数据操作类
    GroupModel _groupMode;

    // redis操作对象
    Redis _redis;
};

#endif