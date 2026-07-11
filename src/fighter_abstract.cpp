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
void Fighter_Base_Class::change_health(int amount)
{
    if (Current_Hp+amount>Initial_Hp)
    {
        Current_Hp=Initial_Hp;
        return;
    }
    
    Current_Hp+=amount;
}
bool Fighter_Base_Class::return_is_fighter_alive()  
{
    return Is_Fighter_Alive;
}

ATTACKING_RANGE Fighter_Base_Class::Return_Fighter_Attacking_Range_Enum_Type() const
{
    return Range_Type;
}

void Fighter_Base_Class::Reset_Move_Value()
{
    Current_Move_Value = Base_Move_Value;
}

void Fighter_Base_Class::Boost_Move_Value(int boost_value)
{
    Current_Move_Value += boost_value;
}

Fighters_Names Fighter_Base_Class::Get_Fighter_Name() const
{
    return Fighter_Name;
}