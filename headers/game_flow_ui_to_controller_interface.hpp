#ifndef GAME_FLOW_UI_TO_CONTROLLER_INTERFACE_HPP
#define GAME_FLOW_UI_TO_CONTROLLER_INTERFACE_HPP
#include "enums.hpp"
#include "controller.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

enum class GAME_FLOW_SCREENS {CHOOSE_FIGHTER, CHOOSE_ACTION, MANEUVER, SCHEME, ATTACK, GO_BACK_TO_MAIN_LOOP};

class User_Choice_Manager
{
    public:
        User_Choice_Manager();
        bool Screen_Manager(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info, Fighters_Print_Info* fighters_printing_info, int fighters_count);
        // void Choose_Fighter_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info);
        // void Choose_Action_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info);
        void Maneuver_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info, Fighters_Print_Info* fighter_printing_info, int fighters_count);
        // void Scheme_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info);
        // void Attack_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info);
    private:
        GAME_FLOW_SCREENS game_current_screen;
        Fighters_Names selected_fighter;
};


#endif