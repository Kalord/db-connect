#include "Database.hpp"

Database::Database(
    const char* host, 
    const char* db_name, 
    const char* user, 
    const char* password
) : host(host), db_name(db_name), user(user), password(password), connect(false), error(false)
{

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

bool Database::hasError()
{
    return this->error;
}

const char* Database::getError()
{
    return mysql_error(&this->mysql);
}

/**
 * Запрос в базу данных
 **/
bool Database::query(const char* query)
{
    if(mysql_query(&this->mysql, query))
    {
        this->error = true;
        return false;
    }
    return true;
}