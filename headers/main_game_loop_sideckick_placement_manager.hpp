#ifndef SIDE_KICK_PLACEMENT_MANAGER
#define SIDE_KICK_PLACEMENT_MANAGER
#include "controller.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

enum class SideKick_Placement_Screen{WATSON_SCREEN, DRACULA_SIS1_SCREEN, DRACULA_SIS2_SCREEN, DRACULA_SIS3_SCREEN, CONTINUE_TO_THE_MAIN_MANAGER};

class SideKick_Placement_Screen_Manager
{
    public:
        SideKick_Placement_Screen_Manager(HERO_NAME younger_hero);
        bool Screen_Manager(Controller& control, ftxui::Element map_and_User_info, Fighters_Print_Info* fighters_info_array);
        void Dispaly_Watson_Screen(Fighters_Print_Info& fighters_info_array, Controller& control, ftxui::Element map_and_user_info);
        void Display_Sis1_Screen(Fighters_Print_Info& fighters_info_array, Controller& control, ftxui::Element map_and_user_info);
        void Display_Sis2_Screen(Fighters_Print_Info& fighters_info_array, Controller& control, ftxui::Element map_and_user_info);
        void Display_Sis3_Screen(Fighters_Print_Info& fighters_info_array, Controller& control, ftxui::Element map_and_user_info);
    private:
        SideKick_Placement_Screen current_placement;
        std::vector <std::string> Young_User_SideKick_Spaces_Available;
        std::vector <std::string> Older_User_SideKick_Spaces_Available;

};


#endif