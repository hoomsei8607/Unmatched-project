#ifndef SCHEME_CARD_MANAGER_HPP
#define SCHEME_CARD_MANAGER_HPP
#include "enums.hpp"
#include "controller.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

class Scheme_Manager
{
    public:
        Scheme_Manager(SCHEME_CARDS_SCREEN screen);

        bool Screen_Manager(Controller& control);

        void Administer_Aid_Screen(Controller& control);
        void Confirm_Suspicion_Screen(Controller& control);
        void Eliminate_The_Impossible_Screen(Controller& control);
        void Master_Of_Disguise_Screen(Controller& control);
 
        void Mistform_Screen(Controller& control);
        void Baptism_Of_Blood_Screen(Controller& control);
        void Prey_Upon_Screen(Controller& control);
        void Ravening_Seduction_Screen(Controller& control);


    private:
        SCHEME_CARDS_SCREEN current_screen;
};

#endif