#ifndef HERO_ABSTREACT_HPP
#define HERO_ABSTREACT_HPP
#include "enums.hpp"

class Fighter_Base_Class
{
    public:
        void Move();
        int Return_Fighter_Initial_Hp();
        int Return_Fighter_Current_Hp();
        int Return_Fighter_Current_Move_Value();
        int Return_Fighter_Current_Space();

    protected:
        int Initial_Hp;
        int Current_Hp;
        int Base_Move_Value;
        int Current_Move_Value; //in case the player wants to boost the movement
        int Current_Hero_Space; //which space is hero standing on in the map
        bool Is_Fighter_Alive;
        ATTACKING_RANGE Range_Type;
        FIGHTER_TYPE fighter_type;

};

#endif