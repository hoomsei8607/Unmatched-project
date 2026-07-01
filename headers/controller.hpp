#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "user.hpp"
#include "structs.hpp"
#include <string>
#include <map>
#include "fighter_abstract.hpp"

class Controller
{
    public:
        Controller();
        void Set_User1_And_User2_Info(const User1_And_User2_Info& info_struct);
        void Fill_Users_Info_Struct(User1_And_User2_Info& info_struct); 
        void Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct);
        ~Controller();
    private:
        User user1;
        User user2;
        Fighter_Base_Class* Dracula_And_Sisters[4];
        Fighter_Base_Class* Sherklock_And_Watson[2];
        std::map <int, Space_Row_And_Column_In_Array> Space_To_Array_Index_Map;

};
#endif