#include "../headers/Ui.hpp"


User_Interface::User_Interface()
{
    this->Current_Screen_State = SCREEN_STATE::MENU;
}

bool User_Interface::Manage_Screen()
{
    switch (Current_Screen_State)
    {
    case SCREEN_STATE::MENU:
        Starting_Menu_Screen();
        return true;
    
    case SCREEN_STATE::GAME_LOOP:
        Game_Loop_Screen();
        return true;
    
    case SCREEN_STATE::GAME_OVER:
        // Finished_Game_Screen();
        return true;

    case SCREEN_STATE::PROGRAM_SHOULD_TEMINATE:
        return false;
    
    }
}