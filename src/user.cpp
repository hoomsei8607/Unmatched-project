#include "../headers/user.hpp"

void User::Set_Age(int age)
{
    this->age = age;
}

void User::Set_Hero_Name(HERO_NAME hero_name)
{
    this->hero = hero_name;
}

void User::Set_Name(const std::string& name)
{
    this->name = name;
}