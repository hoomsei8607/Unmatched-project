#ifndef HERO_ABSTREACT_HPP
#define HERO_ABSTREACT_HPP
#include "enums.hpp"

class Fighter_Base_Class
{
    public:
        void Move();

    protected:
        int Initial_Hp;
        int Current_Hp;
        int Base_Move_Value;
        int Current_Move_Value; //in case the player wants to boost the movement
        int Current_Hero_Space; //which space is hero standing on in the map
        ATTACKING_RANGE Range_Type;
        FIGHTER_TYPE fighter_type;

};

#endif