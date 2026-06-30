#ifndef USER_HPP
#define USER_HPP
#include <string>
#include "enums.hpp"

class User
{
    public:
        void Set_Age(int age);
        void Set_Name(const std::string& name);
        void Set_Hero_Name(HERO_NAME hero_name);

    private:
        int age;
        std::string name;
        HERO_NAME hero;

        

};

#endif