#include "../headers/user.hpp"

void User::Set_Age(const std::string& age)
{
    this->age = age;
}

void User::Set_Hero_Name_Type(HERO_NAME hero_name_type)
{
    this->hero_name_type = hero_name_type;
}

void User::Set_Name(const std::string& name)
{
    this->name = name;
}

void User::Set_Hero_Name_String(const std::string& hero_name_string)
{
    this->hero_name_string = hero_name_string;
}
std::string User::Return_UserName() const
{

    return this->name;
}

std::string User::Return_Hero_Name_String() const
{
    return this->hero_name_string;
}

HERO_NAME User::Return_Hero_Type() const
{
    return this->hero_name_type;
}

std::string User::Return_User_Age() const
{
    return this->age;
}
