#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "../_db_core/Database.hpp"

int main()
{
    Database db("localhost", "framework", "user", "123");

    std::vector<std::map<std::string, std::string>> rows;
    if(db.getAll("SELECT * FROM post", rows))
    {
        std::cout << rows[0]["id"] << std::endl;
    }

    return 0;
}