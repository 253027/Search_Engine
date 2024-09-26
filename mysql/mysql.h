#ifndef __MYSQL_HEAD_H__
#define __MYSQL_HEAD_H__

#include <mysql/mysql.h>
#include <string>
#include <string.h>
#include <iostream>

using std::string;
using namespace std;

class MysqlConnect
{
public:
    MysqlConnect(const string &_host, const string &_name, const string &_password, const string &_database, const string &_port);

    bool update(const string &sql);

    bool query(const string &sql);

    bool next();

    string getSring(const string &_name);

    ~MysqlConnect();

private:
    void freeResult();

    MysqlConnect() = delete;

    MYSQL_RES *res;

    MYSQL_ROW row;

    MYSQL *handle;

    MYSQL_FIELD *field;
};

#endif //__MYSQL_HEAD_H__