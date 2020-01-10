#include <map>
#include <string>
#include <iostream>

#include "../_db_core/Database.hpp"

int main()
{
    Database db("localhost", "framework", "user", "123");

    std::map<std::string, std::string> row;
    if(db.getOne("SELECT * FROM post WHERE id = 1", row))
    {
        std::cout << row["id"] << std::endl;
    }

    return 0;
}