#include "../headers/fighter_abstract.hpp"

int Fighter_Base_Class::Return_Fighter_Initial_Hp()
{
    return Initial_Hp;
}

int Fighter_Base_Class::Return_Fighter_Current_Hp()
{
    return Current_Hp;
}

int Fighter_Base_Class::Return_Fighter_Current_Move_Value()
{
    return Current_Move_Value;
}

int Fighter_Base_Class::Return_Fighter_Current_Space()
{
    return Current_Hero_Space;
}

int Fighter_Base_Class::Return_Fighter_Attacking_Range()
{
    return Attacking_Range;
}