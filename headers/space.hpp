#ifndef SPACE_HPP
#define SPACE_HPP
#include <array>
#include "enums.hpp"

class Space
{
    public:
    void Change_Occupied_Status(); //reverses the occupied status
    bool Get_Occupied_Status();//returns wether  a space is occupied or not
    bool Get_Secret_Pathway_Status(); //returns a boolian wether a space is a secret path way or not
    bool Get_Multi_Zone_status();
    void Get_Zone_Color(std::array<ZONE_COLORS,3>& Passed_Array_To_Be_Filled);
    void Set_Info(bool Is_Multi_zone, bool Is_Occupied, bool Has_Secret_Path, int Space_Number, const std::array<ZONE_COLORS, 3>& Colors);

    private:
    bool Is_Multi_Zone;
    bool Is_Occupied;
    bool Has_Secret_Path;
    int Space_Number;
    ZONE_COLORS zone[3];


};

#endif