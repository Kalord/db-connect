#pragma once

#include <map>
#include <vector>
#include <iostream>

#ifdef __linux__ 
    #include <mysql/mysql.h>
#elif _WIN32
    #pragma comment(lib, "libmysql_.lib")
    #include <mysql.h>
#endif

/**
 * Класс для работы с базой данных
 * 
 * Примеры:
 *      Подключение к базе данных
 *      C++```
 *      Database db("localhost", "db_name", "user", "password");
 *      db.isConnect();
 *      ```
 *      
 *      Запрос в базу данных
 *      C++```
 *      db.query("INSERT INTO post (title) VALUES ('Hello')");
 *      ```
 *      
 *      Получение строки из базы данных
 *      C++```
 *      db.getOne("SELECT * FROM post WHERE id = 1");
 *      ```
 *      Может возвращаться как TableDataProvider, так и 
 *      std::map<std::string, std::string>
 *      
 *      Получение нескольких строк из базы данных
 *      C++```
 *      db.getAll("SELECT * FROM post");
 *      ```
 *      Может возвращаться как std::vector из TableDataProvider, так и 
 *      std::vector из std::map<std::string, std::string>
 * 
 * @author Artem Tyutnev <artem.tyutnev.developer@gmail.com>
 **/
class Database
{
private:
    /**
     * Хост для подключения
     **/
    const char* host;
    /**
     * База данных для подключения
     **/
    const char* db_name;
    /**
     * Пользователья для подключения
     **/
    const char* user;
    /**
     * Пароль для подключения
     **/
    const char* password;
    /**
     * Дескриптор соединения
     **/
    MYSQL mysql;
    /**
     * Флаг, указывающий, подключена ли база данных
     **/
    bool connect;
    /**
     * Флаг указывающий, была ли получена ошибка
     **/
    bool error;
    /**
     * Проверяет, является ли строка пустой
     */
    bool isEmptyRow(MYSQL_ROW data);
public:
    Database(
        const char* host, 
        const char* db_name, 
        const char* user, 
        const char* password
    );
    ~Database();

    bool isConnect();

    bool hasError();
    const char* getError();

    /**
     * Запрос в базу данных
     **/
    bool query(const char* query);

    /**
     * Получение одной строки из базы данных
     **/
    bool getOne(const char* query, std::map<std::string, std::string>& row);

    /**
     * Получение всех строк из базы данных
     **/
    bool getAll(const char* query, std::vector<std::map<std::string, std::string>>& row);
};