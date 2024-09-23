#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"
// user表的数据操作类
class UserModel
{
public:
    // User表的增加方法
    bool insert(User &user);
    // user表的查询方法
    User query(int id);
    // user表的更新操作
    bool update(User user);
    // 重置用户的状态信息
    void resetState();
};
#endif