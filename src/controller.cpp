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
    Space_To_Array_Index_Map[7] = {4, 6};   
    Space_To_Array_Index_Map[8] = {2, 18};   
    Space_To_Array_Index_Map[9] = {0, 25};   
    Space_To_Array_Index_Map[10] = {2, 36};   
    Space_To_Array_Index_Map[11] = {0, 42};   
    Space_To_Array_Index_Map[12] = {2, 48};   
    Space_To_Array_Index_Map[13] = {6, 1};   
    Space_To_Array_Index_Map[14] = {6, 18};   
    Space_To_Array_Index_Map[15] = {4, 24};   
    Space_To_Array_Index_Map[16] = {6, 30};   
    Space_To_Array_Index_Map[17] = {6, 67};   
    Space_To_Array_Index_Map[18] = {8, 7};   
    Space_To_Array_Index_Map[19] = {8, 18};   
    Space_To_Array_Index_Map[20] = {8, 24};   
    Space_To_Array_Index_Map[21] = {6, 42};   
    Space_To_Array_Index_Map[22] = {8, 48};   
    Space_To_Array_Index_Map[23] = {8, 62};   
    Space_To_Array_Index_Map[24] = {10, 12};   
    Space_To_Array_Index_Map[25] = {10, 18};   
    Space_To_Array_Index_Map[26] = {8, 36};   
    Space_To_Array_Index_Map[27] = {10, 42};   
    Space_To_Array_Index_Map[28] = {10, 49};   
    Space_To_Array_Index_Map[29] = {10, 60};   
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

void Controller::Fill_Users_Info_Struct(User1_And_User2_Info& info_struct) const
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

void Controller::Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct) const
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

HERO_NAME Controller::Return_Younger_Hero_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user2.Return_Hero_Type();
    }
    return user1.Return_Hero_Type();
}

void Controller::Set_Fighter_Space_Number(Fighters_Names fighter_name, int new_space) 
{
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SHERLOCK:
        Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::WATSON:
        Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS1:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS2:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS3:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    default:
        break;
    }
}

void Controller::Convert_Space_Number_To_Row_And_Column_Index(int space_number, Space_Row_And_Column_In_Array& info_struct)
{
    if(space_number < 1 || space_number > 32 )
    {
        return;
    }
    info_struct.column_index = Space_To_Array_Index_Map[space_number].column_index;
    info_struct.row_index = Space_To_Array_Index_Map[space_number].row_index;
} 

int Controller::Return_Hero_Space_Number(Fighters_Names fighter_name) const
{
    switch (fighter_name)
    {
            
        case Fighters_Names::DRACULA:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS1:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS2:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS3:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SHERLOCK:
            return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Space();
            
            
        case Fighters_Names::WATSON:
            return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Space();
           
    }
}

void Controller::Set_Younger_User_Variable_Value()
{
    if(user1.Return_User_Age() > user2.Return_User_Age())
    {
        Younger_User = USER::USER2;
    }
    else
    {
        Younger_User = USER::USER1;
    }
    User_Turn = Younger_User;
}

void Controller::Change_User_Turn()
{
    if(User_Turn == USER::USER1)
    {
        User_Turn = USER::USER2;
    }
    else if(User_Turn == USER::USER2)
    {
        User_Turn = USER::USER1;
    }
}

USER Controller::Return_User_Turn() const
{
    return User_Turn;
}

USER Controller::Return_Younger_User() const
{
    return Younger_User;
}

std::string Controller::Return_Older_User_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user1.Return_UserName();
    }
    return user2.Return_UserName();
}

std::string Controller::Return_Younger_User_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user2.Return_UserName();
    }
    return user1.Return_UserName();
}

int Controller::Return_Fighter_Move_Value(Fighters_Names fighter_name) const
{
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Return_Fighter_Current_Move_Value();
    
    case Fighters_Names::SIS1:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SIS2:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SIS3:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SHERLOCK:
        return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Move_Value();
    case Fighters_Names::WATSON:
        return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Move_Value();
        
    default:
        break;
    }   
}

bool Controller::Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn()
{
    switch (current_user_action)
    {
    case USER_ACTION::USER1_ACTION1:
        current_user_action = USER_ACTION::USER1_ACTION2;
        return false;
    
    case USER_ACTION::USER2_ACTION1:
        current_user_action = USER_ACTION::USER2_ACTION2;
        return false;
    
    case USER_ACTION::USER1_ACTION2:
        current_user_action = USER_ACTION::USER2_ACTION1;
        return true;
    
    case USER_ACTION::USER2_ACTION2:
        current_user_action = USER_ACTION::USER1_ACTION1;
        return true;
    
    }
}

HERO_NAME Controller::Return_User1_Hero_Name() const
{
    return user1.Return_Hero_Type();
}
HERO_NAME Controller::Return_User2_Hero_Name() const
{
    return user2.Return_Hero_Type();
}

std::string Controller::Return_User1_Username() const
{
    return user1.Return_UserName();
}
std::string Controller::Return_User2_Username() const
{
    return user2.Return_UserName();
}