#include "groupmodel.hpp"
#include "db.h"
#include "gropuuser.hpp"
#include "user.hpp"
bool GroupModel::createGroup(Group &group)
{
    // 1 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')",
            group.getName().c_str(), group.getDesc().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            group.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void GroupModel::addGroup(int userid, int groupid, string role)
{
    // 1 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser values(%d,%d,'%s')",
            groupid, userid, role.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

vector<Group> GroupModel::queryGroups(int userid)
{

    char sql[1024] = {0};
    sprintf(sql, "SELECT a.id, a.groupname, a.groupdesc FROM allgroup a \
    INNER JOIN groupuser b on a.id = b.groupid WHERE b.userid = %d",
            userid);
    vector<Group> groupVec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                Group group;
                group.setId(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                groupVec.push_back(group);
            }
            mysql_free_result(res);
        }
    }
    for (auto &group : groupVec)
    {
        sprintf(sql, "  SELECT a.id, a.name, a.state,b.grouprole FROM user a \
        INNER JOIN groupuser b on a.id = b.userid WHERE b.groupid = %d ",
                group.getId());
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                group.getUser().push_back(user);
            }
            mysql_free_result(res);
        }
    }
    return groupVec;
}

vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid = %d and userid !=%d", groupid, userid);
    vector<int> userVec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                userVec.push_back(atoi(row[0]));
            }
            mysql_free_result(res);
        }
    }
    return userVec;
}
