#include "../headers/Fighting_Screen_Manager_Class.hpp"

#include <chrono>
#include <thread>
#include <iostream>

using namespace ftxui;

Fighting_Screen_Manager::Fighting_Screen_Manager(int attacker_card_value, int attacker_card_index)
{
    current_screen = FIGHTING_SCREEN_SUB_SCREENS::TAKING_DEFENDER_INPUT;
    Attacker_Card_Value = attacker_card_value;
    attacker_card_index = attacker_card_index; 
}

bool Fighting_Screen_Manager::Screen_Manager(Controller& control)
{
    switch (current_screen)
    {
    case FIGHTING_SCREEN_SUB_SCREENS::TAKING_DEFENDER_INPUT:
        Taking_Defender_Input_Screen(control);
        return true;


    case FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN:

        return true;

    case FIGHTING_SCREEN_SUB_SCREENS::DURING_FIGHT_SCREEN:

        return true;

    case FIGHTING_SCREEN_SUB_SCREENS::RESULTS_SCREEN:

        return true;

    case FIGHTING_SCREEN_SUB_SCREENS::RETURN_TO_MAIN_LOOP:
        return false;
    
    default:
        break;
    }
}

void Fighting_Screen_Manager::Taking_Defender_Input_Screen(Controller& control)
{


    auto screen = ScreenInteractive::Fullscreen();
    USER defender;
    if(control.Return_User_Turn() == USER::USER1)
    {
        defender = USER::USER2;
    }
    else if(control.Return_User_Turn() == USER::USER2)
    {
        defender = USER::USER1;
    }



    std::vector<Card_Base_Class*> copy_of_defender_hand = control.Return_A_Copy_Of_User_Hand(defender);
    std::string defender_name;


    if(defender == USER::USER1)
    {
        defender_name = control.Return_User1_Username();
    }
    else if(defender == USER::USER2)
    {
        defender_name = control.Return_User2_Username();
    }
    Element defender_hand = control.Return_Hand_Elements_For_Render(defender);
    std::vector<std::string> defender_hand_as_string = control.Return_Hand_As_String(defender);
    int selected_card = 0;
    auto radiobox = Toggle(&defender_hand_as_string, &selected_card);
    auto Confirm_Button = Button("CONFIRM", [&]{
        Defender_Card_Value = control.Return_card_Value(defender, selected_card);
        Defender_Selected_Card_Index = selected_card;
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN;
        screen.ExitLoopClosure()();
    });

    auto Skip_Button = Button("SKIP", [&]{
        Defender_Card_Value = 0;
        Defender_Selected_Card_Index = -1;
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN;
        screen.ExitLoopClosure()();
    });
    auto container = Container::Vertical({
        radiobox,
        Confirm_Button,
        Skip_Button
    });

    Confirm_Button = Confirm_Button | Maybe([&]{
        if(copy_of_defender_hand[selected_card]->get_type() == CARD_TYPE::VERSATILE || copy_of_defender_hand[selected_card]->get_type() == CARD_TYPE::DEFENCE)
        {
            return true;
        }
        return false;
    });



    screen.Loop(Renderer(container, [&]{
        return vbox({
            hbox({text(defender_name), text(": "), text("YOU ARE DEFEDING")}),
            text("CHOOSE A CARD OR SKIP"),
            defender_hand,
            container->Render()
        });
    }));
}