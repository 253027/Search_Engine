#include "mysql.h"

MysqlConnect::MysqlConnect(const string &_host, const string &_name, const string &_password, const string &_database, const string &_port)
{
    handle = mysql_init(nullptr);
    handle = mysql_real_connect(handle, (_host == "") ? "localhost" : _host.c_str(), _name.c_str(), _password.c_str(), _database.c_str(), (_port == "") ? 0 : std::stoi(_port), nullptr, 0);
    mysql_set_character_set(handle, "utf8");
    res = nullptr, row = nullptr, field = nullptr;
}

MysqlConnect::~MysqlConnect()
{
    freeResult();
    if (handle)
        mysql_close(handle);
    handle = nullptr;
}

bool MysqlConnect::update(const string &sql)
{
    return mysql_query(handle, sql.c_str()) == 0;
}

bool MysqlConnect::query(const string &sql)
{
    freeResult();
    if (mysql_query(handle, sql.c_str()))
        return false;
    res = mysql_store_result(handle);
    field = mysql_fetch_fields(res);
    return true;
}

bool MysqlConnect::next()
{
    if (!res)
        return false;
    row = mysql_fetch_row(res);
    return row != nullptr;
}

void MysqlConnect::freeResult()
{
    if (!res)
        return;
    mysql_free_result(res);
    res = nullptr, field = nullptr, row = nullptr;
}

string MysqlConnect::getSring(const string &_name)
{
    int col = mysql_num_fields(res);
    for (int i = 0; i < col; i++)
    {
        if (strcmp(_name.c_str(), field[i].name))
            continue;
        return (row[i] == nullptr) ? "" : row[i];
    }
    return "";
}

// g++ Mysql.cpp -lmysqlclient -g -fsanitize=address
int main()
{
    MysqlConnect sql("", "aa", "123", "server", "");
    sql.query("select * from virtual_file_system");
    while (sql.next())
        cout << sql.getSring("id") << " " << sql.getSring("filename") << " " << sql.getSring("type") << " " << sql.getSring("md5") << endl;
    return 0;
}