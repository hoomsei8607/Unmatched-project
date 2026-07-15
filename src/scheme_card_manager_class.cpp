#include "../headers/scheme_card_manager_class.hpp"

Scheme_Manager::Scheme_Manager(SCHEME_CARDS_SCREEN screen, Controller& control)
{
    current_screen = screen;
}

bool Scheme_Manager::Screen_Manager(Controller& control)
{
    switch (current_screen)
    {
    case SCHEME_CARDS_SCREEN::ADMINISTER_AID_SCREEN:
        Administer_Aid_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::ELIMINATE_THE_IMPOSSIBLE_SCREEN:
        Eliminate_The_Impossible_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::MASTER_OF_DISGUISE_SCREEN:
        Master_Of_Disguise_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::CONFIRM_SUSPICION_SCREEN:
        Confirm_Suspicion_Screen(control);
        return true;
    
    case SCHEME_CARDS_SCREEN::MISTFORM_SCREEN:
        Mistform_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::BAPTISM_OF_BLOOD_SCREEN:
        Baptism_Of_Blood_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::PREY_UPON_SCREEN:
        Prey_Upon_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::RAVENING_SEDUCTION_SCREEN:
        Ravening_Seduction_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP:
        return false;
    default:
        break;
    }
}


void Scheme_Manager::Mistform_Screen(Controller& control)
{
    
}