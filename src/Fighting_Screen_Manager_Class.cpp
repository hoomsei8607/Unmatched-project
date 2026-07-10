#include "../headers/Fighting_Screen_Manager_Class.hpp"

#include <chrono>
#include <thread>
#include <iostream>

using namespace ftxui;

Fighting_Screen_Manager::Fighting_Screen_Manager(int attacker_card_value, int attacker_card_index)
{
    current_screen = FIGHTING_SCREEN_SUB_SCREENS::TAKING_DEFENDER_INPUT;
    Attacker_Card_Value = attacker_card_value;
    Attacker_Selected_Card_Index = attacker_card_index; 
}

bool Fighting_Screen_Manager::Screen_Manager(Controller& control)
{
    switch (current_screen)
    {
    case FIGHTING_SCREEN_SUB_SCREENS::TAKING_DEFENDER_INPUT:
        Taking_Defender_Input_Screen(control);
        return true;

 
    case FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN:
        Show_Immediate_Combat_Results(control);
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
        if(control.Return_Selected_Card_Type(defender, selected_card) == CARD_TYPE::VERSATILE || copy_of_defender_hand[selected_card]->get_type() == CARD_TYPE::DEFENCE)
        {
            return true;
        }
        else
        {
            return false;
        }
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

void Fighting_Screen_Manager::Show_Immediate_Combat_Results(Controller& control)
{


    auto screen = ScreenInteractive::Fullscreen();
    USER Attacker = control.Return_User_Turn();
    USER Defender;

    bool Has_Defender_Skipped_Card_Selection;
    if(Defender_Selected_Card_Index == -1)
    {
        Has_Defender_Skipped_Card_Selection = true;
    }
    else
    {
        Has_Defender_Skipped_Card_Selection = false;
    }


    std::string immediate_effects_results_log = "";
    if(Attacker == USER::USER1)
    {
        Defender = USER::USER2;
    }
    else
    {
        Defender = USER::USER1;
    }
    Element defender_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Defender, Defender_Selected_Card_Index);
    Element attacker_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Attacker, Attacker_Selected_Card_Index);
    


    if(Has_Defender_Skipped_Card_Selection)
    {
        if (control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::IMMEDIATE )
            {
                control.Call_Card_Effect_Function(Attacker,control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index),Attacker_Selected_Card_Index);
                immediate_effects_results_log += control.Get_Card_Immediate_Result_Log(Attacker, Attacker_Selected_Card_Index);
            }
        else
        {
            
            immediate_effects_results_log = "NO IMMEDIATE EFFECTS OCCURED";
        }
    }
    else
    {
        if(control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) != CARD_EFFECT_TYPE::IMMEDIATE && control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index) != CARD_EFFECT_TYPE::IMMEDIATE)
        {
            immediate_effects_results_log = "NO IMMEDIATE EFFECTS OCCURED";
        }
        else
        {
            if (control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index)==CARD_EFFECT_TYPE::IMMEDIATE)
            {
                control.Call_Card_Effect_Function(Defender,control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index),Defender_Selected_Card_Index);
                immediate_effects_results_log += control.Get_Card_Immediate_Result_Log(Defender, Defender_Selected_Card_Index);
            }
            if (control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::IMMEDIATE && control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index) != cards::FEINT)
            {
                control.Call_Card_Effect_Function(Attacker,control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index),Attacker_Selected_Card_Index);
                immediate_effects_results_log += control.Get_Card_Immediate_Result_Log(Attacker, Attacker_Selected_Card_Index);
            }
            
        }
    }







    auto Continue_Button = Button("CONTINUE", [&]{
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::DURING_FIGHT_SCREEN;
        screen.ExitLoopClosure()();
    });





    screen.Loop(Renderer(Continue_Button,[&]{
        return vbox({
            text("IMMEDIATE EFFECTS"),
            hbox({
                vbox({
                    text("ATTACKER CARD"),
                    attacker_selected_card_element
                }),
                vbox({text("                         ")}),
                vbox({
                    text("DEFENDER CARD"),
                    defender_selected_card_element
                })
            }),
            text("IMMIDIATE EFFECTS RESULT LOG") | ftxui::underlined,
            text(immediate_effects_results_log),
            Continue_Button->Render()
        });
    }));
}



void Fighting_Screen_Manager::During_Combat_Screen(Controller& control)
{
    
    auto screen = ScreenInteractive::Fullscreen();
    USER Attacker = control.Return_User_Turn();
    USER Defender;

    bool Has_Defender_Skipped_Card_Selection;
    if(Defender_Selected_Card_Index == -1)
    {
        Has_Defender_Skipped_Card_Selection = true;
    }
    else
    {
        Has_Defender_Skipped_Card_Selection = false;
    }


    std::string during_combat_result_log = "";
    if(Attacker == USER::USER1)
    {
        Defender = USER::USER2;
    }
    else
    {
        Defender = USER::USER1;
    }
    Element defender_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Defender, Defender_Selected_Card_Index);
    Element attacker_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Attacker, Attacker_Selected_Card_Index);
    
    if(Has_Defender_Skipped_Card_Selection)
    {
        if (control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::DURING_COMBAT )
            {
                control.Call_Card_Effect_Function(Attacker,control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index),Attacker_Selected_Card_Index);
                during_combat_result_log += control.Get_Card_Immediate_Result_Log(Attacker, Attacker_Selected_Card_Index);
            }
        else
        {
            
            during_combat_result_log = "NO EFFECTS OCCURED";
        }
    }
    else
    {
        if(control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) != CARD_EFFECT_TYPE::DURING_COMBAT && control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index) != CARD_EFFECT_TYPE::DURING_COMBAT)
        {
            during_combat_result_log = "NO EFFECTS OCCURED";
        }
        else
        {
            if (control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index) == CARD_EFFECT_TYPE::DURING_COMBAT)
            {
                control.Call_Card_Effect_Function(Defender,control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index),Defender_Selected_Card_Index,Fighters_Names::NONE,-1,Attacker_Selected_Card_Index);
                during_combat_result_log += control.Get_Card_Immediate_Result_Log(Defender, Defender_Selected_Card_Index);
            }
            if (control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::DURING_COMBAT && control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index) != cards::FEINT)
            {
                control.Call_Card_Effect_Function(Attacker,control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index),Attacker_Selected_Card_Index,Fighters_Names::NONE,-1,Defender_Selected_Card_Index);
                during_combat_result_log += control.Get_Card_Immediate_Result_Log(Attacker, Attacker_Selected_Card_Index);
            }
            
        }
    }

    auto Continue_Button = Button("CONTINUE", [&]{
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::RESULTS_SCREEN;
        screen.ExitLoopClosure()();
    });

    screen.Loop(Renderer(Continue_Button,[&]{
        return vbox({
            text("IMMEDIATE EFFECTS"),
            hbox({
                vbox({
                    text("ATTACKER CARD"),
                    attacker_selected_card_element
                }),
                vbox({text("                         ")}),
                vbox({
                    text("DEFENDER CARD"),
                    defender_selected_card_element
                })
            }),
            text("IMMIDIATE EFFECTS RESULT LOG") | ftxui::underlined,
            text(during_combat_result_log),
            Continue_Button->Render()
        });
    }));

}