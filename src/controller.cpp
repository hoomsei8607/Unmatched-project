#include "../headers/controller.hpp"
#include "../headers/structs.hpp"

void Controller::Set_User1_And_User2_Info(User1_And_User2_Info info_struct)
{
    //user1 info
    user1.Set_Hero_Name(info_struct.User1_Hero_Name);
    user1.Set_Age(info_struct.User1_Age);
    user1.Set_Name(info_struct.User1_Name);
    //user2 info
    user2.Set_Hero_Name(info_struct.User2_Hero_Name);
    user2.Set_Age(info_struct.User2_Age);
    user2.Set_Name(info_struct.User2_Name);
}