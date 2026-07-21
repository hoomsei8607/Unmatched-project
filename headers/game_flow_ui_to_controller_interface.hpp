#ifndef GAME_FLOW_UI_TO_CONTROLLER_INTERFACE_HPP
#define GAME_FLOW_UI_TO_CONTROLLER_INTERFACE_HPP
#include "enums.hpp"
#include "controller.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

enum class GAME_FLOW_SCREENS {CHOOSE_FIGHTER, CHOOSE_ACTION, CHOOSE_MANEUVER_TYPE, MANEUVER_BOOST_SCREEN,  MANEUVER, FIGHTING_SCREEN, Card_Selection_Screen, CHOOSE_YOUR_ENEMY_SCREEN, GAME_OVER_SCREEN, GO_BACK_TO_MAIN_LOOP, SCHEME_CARD_MANAGER};

class User_Choice_Manager
{
    public:
        User_Choice_Manager();
        bool Screen_Manager(USER user_turn, Controller& control, Fighters_Print_Info* fighters_printing_info, int fighters_count);
        void Choose_Fighter_Screen(USER user_turn, Controller& control);
        void Choose_Action_Screen(USER user_turn, Controller& control);
        void Maneuver_Screen(USER user_turn, Controller& control, Fighters_Print_Info* fighter_printing_info, int fighters_count);
        void Select_Card_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_use_info);
        void Choose_Maneuver_Type(Controller& control);
        void Choose_Card_To_Boost_Maneuver_With(USER user_turn, Controller& control);
        void Choose_Enemy_Screen(Controller& control);
        void Fighting_Screen(USER user_turn, Controller& control);
        void Scheme_Card_Manager_Screen(Controller& control);
        void Game_Over_Screen(Controller& control);
    private:
        GAME_FLOW_SCREENS game_current_screen;
        Fighters_Names selected_fighter;
        int selected_Attacker_card_index;
        int attacker_card_value;
        ATTACKING_RANGE attack_type;
        
};


#endif