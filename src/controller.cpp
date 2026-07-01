#include "../headers/controller.hpp"
#include "../headers/fighters_sub_classes.hpp"
#include "../headers/structs.hpp"

Controller::Controller()
{
    Space_To_Array_Index_Map[1] = {2, 12};   
    Space_To_Array_Index_Map[2] = {0, 19};   
    Space_To_Array_Index_Map[3] = {0, 31};   
    Space_To_Array_Index_Map[4] = {0, 37};   
    Space_To_Array_Index_Map[5] = {0, 49};   
    Space_To_Array_Index_Map[6] = {0, 55};   
    Space_To_Array_Index_Map[7] = {4, 7};   
    Space_To_Array_Index_Map[8] = {2, 19};   
    Space_To_Array_Index_Map[9] = {0, 25};   
    Space_To_Array_Index_Map[10] = {2, 36};   
    Space_To_Array_Index_Map[11] = {0, 43};   
    Space_To_Array_Index_Map[12] = {2, 48};   
    Space_To_Array_Index_Map[13] = {6, 1};   
    Space_To_Array_Index_Map[14] = {6, 18};   
    Space_To_Array_Index_Map[15] = {4, 25};   
    Space_To_Array_Index_Map[16] = {6, 30};   
    Space_To_Array_Index_Map[17] = {6, 68};   
    Space_To_Array_Index_Map[18] = {8, 7};   
    Space_To_Array_Index_Map[19] = {8, 18};   
    Space_To_Array_Index_Map[20] = {8, 24};   
    Space_To_Array_Index_Map[21] = {6, 42};   
    Space_To_Array_Index_Map[22] = {8, 48};   
    Space_To_Array_Index_Map[23] = {8, 60};   
    Space_To_Array_Index_Map[24] = {10, 13};   
    Space_To_Array_Index_Map[25] = {10, 10};   
    Space_To_Array_Index_Map[26] = {8, 36};   
    Space_To_Array_Index_Map[27] = {10, 43};   
    Space_To_Array_Index_Map[28] = {10, 49};   
    Space_To_Array_Index_Map[29] = {10, 61};   
    Space_To_Array_Index_Map[30] = {10, 31};   
    Space_To_Array_Index_Map[31] = {10, 37};   
    Space_To_Array_Index_Map[32] = {10, 55};   

    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)] = Dracula::Get_Instance();
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)] = new Dracula_Sister(1);
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)] = new Dracula_Sister(2);
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)] = new Dracula_Sister(3);

    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)] = Sherlock::Get_Instance();
    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)] = Watson::Get_Instance();

}


void Controller::Set_User1_And_User2_Info(const User1_And_User2_Info& info_struct)
{
    //user1 info
    user1.Set_Hero_Name_String(info_struct.User1_Hero_Name);
    user1.Set_Hero_Name_Type(info_struct.User1_Hero_Type);
    user1.Set_Age(info_struct.User1_Age);
    user1.Set_Name(info_struct.User1_Name);
    
    //user2 info
    user2.Set_Hero_Name_String(info_struct.User2_Hero_Name);
    user2.Set_Hero_Name_Type(info_struct.User2_Hero_Type);
    user2.Set_Age(info_struct.User2_Age);
    user2.Set_Name(info_struct.User2_Name);
}

void Controller::Fill_Users_Info_Struct(User1_And_User2_Info& info_struct)
{
    info_struct.User1_Age = user1.Return_User_Age();
    info_struct.User1_Hero_Name = user1.Return_Hero_Name_String();
    info_struct.User1_Hero_Type = user1.Return_Hero_Type();
    info_struct.User1_Name = user1.Return_UserName();
    
    info_struct.User2_Age = user2.Return_User_Age();
    info_struct.User2_Hero_Name = user2.Return_Hero_Name_String();
    info_struct.User2_Hero_Type = user2.Return_Hero_Type();
    info_struct.User2_Name = user2.Return_UserName();

}


Controller::~Controller()
{
    Dracula::Destroy_Object();
    Watson::Destroy_Object();
    Sherlock::Destroy_Object();
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)];
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)];
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)];
}

void Controller::Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct)
{
    Fighter_Base_Class* Base_Fighter_Class_Pointer = nullptr;

    switch (fighter_name)
    {
        case Fighters_Names::DRACULA:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)];
            break;
                
        case Fighters_Names::SHERLOCK:
            Base_Fighter_Class_Pointer = Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)];
            break;
                
        case Fighters_Names::WATSON:
            Base_Fighter_Class_Pointer = Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)];
            break;
                
        case Fighters_Names::SIS1:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)];
            break;
            
        case Fighters_Names::SIS2:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)];
            break;

        case Fighters_Names::SIS3:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)];
            break;
        
    }
    info_struct.Current_Hp = Base_Fighter_Class_Pointer->Return_Fighter_Current_Hp();
    info_struct.Initial_Hp = Base_Fighter_Class_Pointer->Return_Fighter_Initial_Hp();
    info_struct.Move_Value = Base_Fighter_Class_Pointer->Return_Fighter_Current_Move_Value();
    info_struct.Range = Base_Fighter_Class_Pointer->Return_Fighter_Attacking_Range();
}