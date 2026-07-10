#ifndef FIGHTING_SCREEN_MANAGER_CLASS_HPP
#define FIGHTING_SCREEN_MANAGER_CLASS_HPP
#include "enums.hpp"
#include "controller.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

enum class FIGHTING_SCREEN_SUB_SCREENS{TAKING_DEFENDER_INPUT, IMMIDATE_RESULTS_SCREEN, DURING_FIGHT_SCREEN, RESULTS_SCREEN, RETURN_TO_MAIN_LOOP};

class Fighting_Screen_Manager
{
    public:
        Fighting_Screen_Manager(int attacker_card_value, int attacker_card_index);
        bool Screen_Manager(Controller& control);
        void Show_Immediate_Combat_Results(Controller& control);
        void During_Combat_Screen(Controller& control);
        void Taking_Defender_Input_Screen(Controller& control);

    private:
        int Defender_Selected_Card_Index;
        int Attacker_Card_Value;
        int Defender_Card_Value;
        int Attacker_Selected_Card_Index;
        FIGHTING_SCREEN_SUB_SCREENS current_screen;
        USER winner;

};

#endif