#include "../headers/fighters_sub_classes.hpp"

Dracula::Dracula()
{
    Initial_Hp=13;
    Current_Hp=13;
    Base_Move_Value=2;
    Current_Move_Value=2;
    Is_Fighter_Alive=true;
    Range_Type=ATTACKING_RANGE::MELEE;
    fighter_type=FIGHTER_TYPE::HERO;
    Fighter_Name = Fighters_Names::DRACULA;
    Current_Hero_Space=0;
    Attacking_Range = 1;

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
    Fighter_Name = Fighters_Names::SHERLOCK;
    Current_Hero_Space=0;
    Attacking_Range = 1;
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
    Fighter_Name = Fighters_Names::WATSON;
    Current_Hero_Space=0;
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
    Attacking_Range = 1;

    switch (sis_number)
    {
    case 1:
        Fighter_Name = Fighters_Names::SIS1;
        break;
    
    
    case 2:
        Fighter_Name = Fighters_Names::SIS2;
        break;
    
    
    case 3:
        Fighter_Name = Fighters_Names::SIS3;
        break;
    
    }

}