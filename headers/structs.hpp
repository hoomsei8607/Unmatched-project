#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include "enums.hpp"
#include <string>

struct User1_And_User2_Info{
    std::string User1_Name;
    std::string User2_Name;

    int User1_Age;
    int User2_Age;

    HERO_NAME User1_Hero_Name;
    HERO_NAME User2_Hero_Name;

};


#endif