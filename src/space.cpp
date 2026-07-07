#include "../headers/space.hpp"

Space::Space()
{
    occupied_by_whom = USER::NONE;
}

void Space::Change_Occupied_Status()
{
    this->Is_Occupied = !Is_Occupied;
}

bool Space::Get_Occupied_Status() const
{
    return this->Is_Occupied;
}

bool Space::Get_Secret_Pathway_Status() const
{
    return this->Has_Secret_Path;
}

bool Space::Get_Multi_Zone_status() const
{
    return this->Is_Multi_Zone;
}

void Space::Get_Zone_Color(std::array <ZONE_COLORS, 3>& To_Be_Filled)
{
    for(int i = 0 ; i < 3 ; i++)
    {
        To_Be_Filled[i] = zone[i];
    }
}

void Space::Set_Info(bool Is_Multi_zone, bool Is_Occupied, bool Has_Secret_Path, int Space_Number, const std::array<ZONE_COLORS, 3>& Colors)
{
    this->Is_Multi_Zone = Is_Multi_zone;
    this->Is_Occupied = Is_Occupied;
    this->Has_Secret_Path = Has_Secret_Path;
    this->Space_Number = Space_Number;
    for(int i = 0 ; i < 3 ; i++)
    {
        zone[i] = Colors[i];
    }
    
}

int Space::Get_Space_Number() const
{
    return Space_Number;
}

void Space::Set_Which_User_Is_Occupying_The_Space(USER user_occupying_space)
{
    occupied_by_whom = user_occupying_space;
}
USER Space::Get_Which_User_Is_Occupying_The_Space()
{
    return occupied_by_whom;
}