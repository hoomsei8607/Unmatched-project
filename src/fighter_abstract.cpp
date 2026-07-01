#include "../headers/fighter_abstract.hpp"

int Fighter_Base_Class::Return_Fighter_Initial_Hp() const
{
    return Initial_Hp;
}

int Fighter_Base_Class::Return_Fighter_Current_Hp() const
{
    return Current_Hp;
}

int Fighter_Base_Class::Return_Fighter_Current_Move_Value() const
{
    return Current_Move_Value;
}

int Fighter_Base_Class::Return_Fighter_Current_Space() const
{
    return Current_Hero_Space;
}

int Fighter_Base_Class::Return_Fighter_Attacking_Range() const
{
    return Attacking_Range;
}

void Fighter_Base_Class::Set_Current_Fighter_Space_Number(int new_space)
{
    this->Current_Hero_Space = new_space;
}