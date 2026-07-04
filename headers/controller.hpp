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
        void Fill_Users_Info_Struct(User1_And_User2_Info& info_struct) const; 
        void Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct) const;
        HERO_NAME Return_Younger_Hero_Name() const;
        void Set_Fighter_Space_Number(Fighters_Names fighter_name, int new_space);
        int Return_Hero_Space_Number(Fighters_Names fighter_Name) const;
        void Convert_Space_Number_To_Row_And_Column_Index(int space_number, Space_Row_And_Column_In_Array& info_struct);
        void Set_Younger_User_Variable_Value();
        void Change_User_Turn();
        USER Return_User_Turn() const;
        USER Return_Younger_User() const;
        std::string Return_Younger_User_Name() const;
        std::string Return_Older_User_Name() const;
        std::string Return_User1_Username() const;
        std::string Return_User2_Username() const;
        HERO_NAME Return_User1_Hero_Name() const;
        HERO_NAME Return_User2_Hero_Name() const;
        int Return_Fighter_Move_Value(Fighters_Names fighter_name) const;
        bool Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn();
        ~Controller();
    private:
        User user1;
        User user2;
        Fighter_Base_Class* Dracula_And_Sisters[4];
        Fighter_Base_Class* Sherklock_And_Watson[2];
        std::map <int, Space_Row_And_Column_In_Array> Space_To_Array_Index_Map;
        USER Younger_User;
        USER User_Turn;
        USER_ACTION current_user_action;
};
#endif