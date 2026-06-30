#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "structs.hpp"
#include "controller.hpp"
#ifndef UI_HPP
#define UI_HPP

enum class SCREEN_STATE{MENU, GAME_LOOP, GAME_OVER, PROGRAM_SHOULD_TEMINATE, PROMPT_INPUT, NONE};

class User_Interface
{
    public:
        User_Interface();
        bool Manage_Screen(Controller& control);
        void Starting_Menu_Screen();
        void Game_Loop_Screen();
        User1_And_User2_Info Get_User_Input();
        // void Finished_Game_Screen();
        
    private:
        SCREEN_STATE Current_Screen_State;

};


#endif