#include "Database.hpp"

Database::Database(
    const char* host, 
    const char* db_name, 
    const char* user, 
    const char* password
) : host(host), db_name(db_name), user(user), password(password)
{
    this->connect = false;

    mysql_init(&this->mysql);
    if(mysql_real_connect(&this->mysql, this->host, this->user, this->password, this->db_name, 0, NULL, 0))
    {
        this->connect = true;
    }
}

Database::~Database()
{
    mysql_close(&this->mysql);
}

bool Database::isConnect()
{
    return this->connect;
}