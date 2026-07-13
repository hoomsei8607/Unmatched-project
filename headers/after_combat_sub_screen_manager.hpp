#ifndef AFTER_COMBAT_SUB_SCREEN_MANAGER_HPP
#define AFTER_COMBAT_SUB_SCREEN_MANAGER_HPP

#include "controller.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>



class After_Combat_Sub_Screen_Manager
{
    public:
    After_Combat_Sub_Screen_Manager(cards selected_card_name, USER user_turn, AFTER_COMBAT_SUB_SCREENS screen);
    bool Screen_Manager(Controller& control);
    void Dash_Card_Screen(Controller& control);
    void Thirst_For_Sustenance_Screen(Controller& control);
    void Game_Is_Afoot(Controller& control);
    void Study_Methods_Screen(Controller& control);
    void Change_User_Turn();
    private:
    AFTER_COMBAT_SUB_SCREENS current_screen;
    USER user_turn;


};



#endif