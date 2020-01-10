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

/**
 * Проверяет, является ли строка пустой
 */
bool Database::isEmptyRow(MYSQL_ROW data)
{
    return data == NULL;
}

/**
 * Получение одной строки из базы данных
 **/
bool Database::getOne(const char* query, std::map<std::string, std::string>& row)
{
    if(!this->query(query)) return false;

    MYSQL_RES* res = mysql_store_result(&this->mysql);
    int numFields = mysql_num_fields(res);
    MYSQL_ROW data = mysql_fetch_row(res);

    if(this->isEmptyRow(data)) return false;

    for(int i = 0; i < numFields; i++)
    {
        MYSQL_FIELD* field = mysql_fetch_field_direct(res, i);
        row[field->name] = data[i];
    }

    return true;
}