#include "offlinemessagemodel.hpp"
#include "db.h"

void OffLineMsgModel::insert(int userid, string msg)
{
    // 1 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values('%d','%s')", userid, msg.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

void OffLineMsgModel::remove(int userid)
{
    // 1 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid = %d", userid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

vector<string> OffLineMsgModel::query(int userid)
{
    // 1 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);
    MySQL mysql;
    vector<string> vec;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            // 把用户的所有离线小区放入vec
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}
