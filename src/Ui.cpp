#include "../headers/Ui.hpp"
#include "../headers/controller.hpp"
#include <iostream>

User_Interface::User_Interface()
{
    this->Current_Screen_State = SCREEN_STATE::MENU;
}

bool User_Interface::Manage_Screen(Controller& control)
{
    switch (Current_Screen_State)
    {
    case SCREEN_STATE::MENU:
        Starting_Menu_Screen();
        return true;
    
    case SCREEN_STATE::PROMPT_INPUT:
        control.Set_User1_And_User2_Info(Get_User_Input());
        return true;
        
    case SCREEN_STATE::GAME_LOOP:
        Game_Loop_Screen(control);
        return true;
    
    case SCREEN_STATE::GAME_OVER:
        // Finished_Game_Screen();
        return true;

    case SCREEN_STATE::PROGRAM_SHOULD_TEMINATE:
        return false;
    }
}