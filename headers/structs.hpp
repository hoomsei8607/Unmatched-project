#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include "enums.hpp"
#include <string>

struct User1_And_User2_Info
{
    std::string User1_Name;
    std::string User2_Name;

    std::string User1_Age;
    std::string User2_Age;

    std::string User1_Hero_Name;
    std::string User2_Hero_Name;

    HERO_NAME User1_Hero_Type; 
    HERO_NAME User2_Hero_Type; 

};

struct Space_Row_And_Column_In_Array
{
    int row_index;
    int column_index;
};

struct Fighters_Print_Info
{
    int Row_Index;
    int Column_Index;
    char Fighter_Name;
    bool Is_Placed_On_Map;
    char Sis_Number;
};

struct Fighter_Info
{
    int Initial_Hp;
    int Current_Hp;
    int Move_Value;
    int Range;
};


#endif