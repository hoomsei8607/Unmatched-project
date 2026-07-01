#include "../headers/fighters_sub_classes.hpp"
#include "../headers/fighters_sub_classes.hpp"

Dracula* Dracula::Object_Instance = nullptr;
Watson* Watson::Object_Instance = nullptr;
Sherlock* Sherlock::Object_Instance = nullptr;


Dracula* Dracula::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Dracula;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;
}
Dracula::Dracula()
{
    Initial_Hp=13;
    Current_Hp=13;
    Base_Move_Value=2;
    Current_Move_Value=2;
    Is_Fighter_Alive=true;
    Range_Type=ATTACKING_RANGE::MELEE;
    fighter_type=FIGHTER_TYPE::HERO;
    Current_Hero_Space=0;

}

Sherlock* Sherlock::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Sherlock;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;
    
}
Sherlock::Sherlock()
{
    Initial_Hp=16;
    Current_Hp=16;
    Base_Move_Value=2;
    Current_Move_Value=2;
    Is_Fighter_Alive=true;
    Range_Type=ATTACKING_RANGE::MELEE;
    fighter_type=FIGHTER_TYPE::HERO;
    Current_Hero_Space=0;
}

Watson* Watson::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Watson;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;
}
Watson::Watson()
{
    Initial_Hp=8;
    Current_Hp=8;
    Base_Move_Value=2;
    Current_Move_Value=2;
    Is_Fighter_Alive=true;
    Range_Type=ATTACKING_RANGE::RANGED;
    fighter_type=FIGHTER_TYPE::SIDE_KICK;
    Current_Hero_Space=0;
}

void Sherlock::Destroy_Object()
{
    if(Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}

void Dracula::Destroy_Object()
{
    if(Dracula::Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}

void Watson::Destroy_Object()
{
    if(Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}
Dracula_Sister::Dracula_Sister(int sis_number)
{
    this->sister_number = sis_number;
    Initial_Hp=1;
    Current_Hp=1;
    Base_Move_Value=2;
    Current_Move_Value=2;
    Is_Fighter_Alive=true;
    Range_Type=ATTACKING_RANGE::MELEE;
    fighter_type=FIGHTER_TYPE::SIDE_KICK;
    Current_Hero_Space=0;

}