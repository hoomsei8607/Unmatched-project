#include "../headers/Fighting_Screen_Manager_Class.hpp"
#include "../headers/after_combat_sub_screen_manager.hpp"
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
        During_Combat_Screen(control);
        return true;

    case FIGHTING_SCREEN_SUB_SCREENS::RESULTS_SCREEN:
        Show_Fight_Results_Screen(control);
        return true;


    case FIGHTING_SCREEN_SUB_SCREENS::AFTER_COMBAT_SCREEN:
        After_Combat_Screen(control);
        return true;

    case FIGHTING_SCREEN_SUB_SCREENS::ELEMENTARY_DEFENCE_CARD:
        Elementary_Defence_Card_Screen(control);
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

        if(control.Return_Selected_Card_Name_As_An_Enum(defender, selected_card) == cards::ELEMENTARY)
        {
            current_screen = FIGHTING_SCREEN_SUB_SCREENS::ELEMENTARY_DEFENCE_CARD;
        }
        else
        {
            current_screen = FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN;
        }
        screen.ExitLoopClosure()();
    });

    auto Skip_Button = Button("SKIP", [&]{
        Defender_Card_Value = 0;
        Defender_Selected_Card_Index = -1;
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN;
        screen.ExitLoopClosure()();
    });
    

    Confirm_Button = Confirm_Button | Maybe([&]{
        if(control.Return_Selected_Card_Type(defender, selected_card) == CARD_TYPE::VERSATILE || control.Return_Selected_Card_Type(defender, selected_card) == CARD_TYPE::DEFENCE)
        {
            return true;
        }
        else
        {
            return false;
        }
    });

    auto container = Container::Vertical({
        radiobox,
        Confirm_Button,
        Skip_Button
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
    Element defender_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Defender, Defender_Selected_Card_Index) | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, 15);
    Element attacker_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Attacker, Attacker_Selected_Card_Index) | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, 15);
    


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
                if(control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index) == cards::FEINT)
                {
                    control.Disable_Card_Effect(Attacker, Attacker_Selected_Card_Index);
                }
                control.Call_Card_Effect_Function(Defender,control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index),Defender_Selected_Card_Index);
                immediate_effects_results_log += control.Get_Card_Immediate_Result_Log(Defender, Defender_Selected_Card_Index);
            }
            if (control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::IMMEDIATE && control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index) != cards::FEINT)
            {
                if(control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index) == cards::FEINT)
                {
                    control.Disable_Card_Effect(Defender, Defender_Selected_Card_Index);
                }
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
            text(" "),
            text("IMMEDIATE EFFECTS") | bold | color(Color::NavajoWhite3),
            text(" "),
            hbox({
                vbox({
                    text("ATTACKER CARD"),
                    attacker_selected_card_element
                }),
                vbox({}) | size(WIDTH, EQUAL, 30),
                vbox({
                    text("DEFENDER CARD"),
                    defender_selected_card_element
                })
            }),
            text(" "),
            vbox({
                text("IMMIDIATE EFFECTS RESULT LOG") | ftxui::underlined | bold | color(Color::NavajoWhite3),
                text(" "),
                text(immediate_effects_results_log)
            }) | size(WIDTH, EQUAL, 90),
            Continue_Button->Render() |size(WIDTH, EQUAL, 90)
        }) | hcenter | vcenter | border;
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
    Element defender_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Defender, Defender_Selected_Card_Index) | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, 15);
    Element attacker_selected_card_element = control.Return_A_Single_Card_Graphical_Representation(Attacker, Attacker_Selected_Card_Index) | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, 15);
    
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
            text(" "),
            text("DURING FIGHT EFFECTS") | bold | color(Color::NavajoWhite3),
            text(" "),
            hbox({
                vbox({
                    text("ATTACKER CARD"),
                    attacker_selected_card_element
                }),
                vbox({}) | size(WIDTH, EQUAL, 30),
                vbox({
                    text("DEFENDER CARD"),
                    defender_selected_card_element
                })
            }),
            vbox({
                text(" "),
                text("DURING FIGHT EFFECTS RESULT LOG") | ftxui::underlined | bold | color(Color::NavajoWhite3),
                text(" "),
                text(during_combat_result_log)
            }) | size(WIDTH, EQUAL, 90),
            Continue_Button->Render() | size(WIDTH, EQUAL, 90)
        })| hcenter | vcenter | border;
    }));


    Attacker_Card_Value = control.Return_card_Value(Attacker, Attacker_Selected_Card_Index);

    if(Has_Defender_Skipped_Card_Selection)
    {
        Defender_Card_Value = 0;
    }
    else
    {
        Defender_Card_Value = control.Return_card_Value(Defender, Defender_Selected_Card_Index);
    }

}


void Fighting_Screen_Manager::Show_Fight_Results_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    USER Attacker = control.Return_User_Turn();
    USER Defender;
    std::string Fight_Results;
    std::string Damage_Dealt;

    if(Attacker == USER::USER1)
    {
        Defender = USER::USER2;
    }
    else
    {
        Defender = USER::USER1;
    }

    if((Attacker_Card_Value - Defender_Card_Value) >= 1)
    {
        //attacker has won
        Fight_Results = "ATTACKER WON THE COMBAT";
        Damage_Dealt = std::to_string(Attacker_Card_Value - Defender_Card_Value);
        control.Set_Who_Has_Won_The_Combat_Variable(Attacker);
    }
    else
    {
        Fight_Results = "DEFENDER WON THE COMBAT";
        Damage_Dealt = std::to_string(Defender_Card_Value - Attacker_Card_Value);
        control.Set_Who_Has_Won_The_Combat_Variable(Defender);
    }

    auto continue_button = Button("CONTINUE", [&]{
        current_screen = FIGHTING_SCREEN_SUB_SCREENS::AFTER_COMBAT_SCREEN;
        screen.ExitLoopClosure()();
    });

    screen.Loop(Renderer(continue_button, [&]{
        return vbox({
            text(Fight_Results) | center | underlined | color(Color::NavajoWhite3) |bold,
            text(" "),
            hbox({text("DAMAGE DEALT: "), text(Damage_Dealt)}) | center,
            continue_button->Render() | center
        }) | hcenter | vcenter;
    }));
}

void Fighting_Screen_Manager::After_Combat_Screen(Controller& control)
{
    AFTER_COMBAT_SUB_SCREENS after_effect_card_screen;
    
    Element Describtion_For_User;
    USER Attacker = control.Return_User_Turn();
    USER Defender;
    if(Attacker == USER::USER1)
    {
        Defender = USER::USER2;
    }
    else 
    {   
        Defender = USER::USER1;
    }

    bool Has_Defender_Skipped_turn;
    if(Defender_Selected_Card_Index == -1)
    {
        Has_Defender_Skipped_turn = true;
    }
    else
    {
        Has_Defender_Skipped_turn = false;
    }

    if(Has_Defender_Skipped_turn)
    {
        auto screen = ScreenInteractive::Fullscreen();
        if(control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::AFTER_COMBAT && control.Should_Card_Effect_Be_Executed(Attacker, Attacker_Selected_Card_Index))
        {

            switch (control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index))
            {
            case cards::DASH:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::DASH;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE YOUR FIGHTER UPTO 3 SPACES")
                });
                break;
            
            case cards::THE_GAME_IS_AFOOT:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::GAME_IS_AFOOT;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE SHERLOCK UPTO 3 SPACES")
                });
                break;
            
            case cards::THIRST_FOR_SUSTENANCE:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::THIRST_FOR_SUSTENANCE;
                if(control.return_who_won_the_combat() != Attacker)
                {
                    break;
                }

                Describtion_For_User = vbox({
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("CHOOSE A SPACE TO MOVE DRACULA ADJACENT TO THE OPPISNG FIGHTER"),
                    text(" ")
                });
                break;
            
            case cards::STUDY_METHODS:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::STUDY_METHODS;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("TAKE A LOOK AT YOUR OPPONENTS HAND"),
                    text(" "),

                    control.Return_Hand_Elements_For_Render(Defender)
                });
                break;
            
            default:
                break;
            }

            auto continue_button = Button("CONTINUE", [&]{
                screen.ExitLoopClosure()();
            });

            screen.Loop(Renderer(continue_button, [&]{
                return vbox({
                    Describtion_For_User | hcenter,
                    continue_button -> Render() | size(WIDTH, EQUAL, 45) | hcenter
                }) | center;
            }));
            After_Combat_Sub_Screen_Manager after_combet_sub_screens(control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index), Attacker, after_effect_card_screen);
            while(true)
            {
                if(!after_combet_sub_screens.Screen_Manager(control))
                {
                    break;
                }
            }

        }
        else
        {
            auto screen = ScreenInteractive::Fullscreen();


            Describtion_For_User = vbox({
                text(" "),
                text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                text(" "),
                text("NO EFFECTS") | center 
            });

            auto continue_button = Button("CONTINUE", [&]{
                screen.ExitLoopClosure();
            });

            screen.Loop(Renderer(continue_button, [&]{
                return vbox({
                    Describtion_For_User | hcenter,
                    continue_button -> Render() | size(WIDTH, EQUAL, 45) | hcenter 
                }) | center;
            }));
        }
    }
    else
    {
        bool No_Effect_Should_occur;
        if(!control.Should_Card_Effect_Be_Executed(Attacker, Attacker_Selected_Card_Index) && !control.Should_Card_Effect_Be_Executed(Defender, Defender_Selected_Card_Index))
        {
            No_Effect_Should_occur = true;
        }
        if(control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index) == CARD_EFFECT_TYPE::AFTER_COMBAT && control.Should_Card_Effect_Be_Executed(Defender, Defender_Selected_Card_Index))
        {
            auto screen = ScreenInteractive::Fullscreen();
            switch (control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index))
            {
            case cards::DASH:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::DASH;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE YOUR FIGHTER UPTO 3 SPACES")
                });
                break;
            
            case cards::THE_GAME_IS_AFOOT:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::GAME_IS_AFOOT;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE SHERLOCK UPTO 3 SPACES")
                });
                break;
            
            case cards::THIRST_FOR_SUSTENANCE:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::THIRST_FOR_SUSTENANCE;
                if(control.return_who_won_the_combat() != Attacker)
                {
                    break;
                }

                Describtion_For_User = vbox({
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("CHOOSE A SPACE TO MOVE DRACULA ADJACENT TO THE OPPISNG FIGHTER"),
                    text(" ")
                });
                break;
            
            case cards::STUDY_METHODS:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::STUDY_METHODS;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("TAKE A LOOK AT YOUR OPPONENTS HAND"),
                    text(" "),

                    control.Return_Hand_Elements_For_Render(Attacker)
                });
                break;
            
            default:
                break;
            }

            auto continue_button = Button("CONTINUE", [&]{
                screen.ExitLoopClosure()();
            });

            screen.Loop(Renderer(continue_button, [&]{
                return vbox({
                    Describtion_For_User | hcenter,
                    continue_button -> Render() | size(WIDTH, EQUAL, 45) | hcenter
                });
            }));
            After_Combat_Sub_Screen_Manager after_combet_sub_screens(control.Return_Selected_Card_Name_As_An_Enum(Defender, Defender_Selected_Card_Index), Defender, after_effect_card_screen);
            while(true)
            {
                if(!after_combet_sub_screens.Screen_Manager(control))
                {
                    break;
                }
            }

        }

        if(control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) == CARD_EFFECT_TYPE::AFTER_COMBAT && control.Should_Card_Effect_Be_Executed(Attacker, Attacker_Selected_Card_Index))
        {
            auto screen = ScreenInteractive::Fullscreen();
            switch (control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index))
            {
            case cards::DASH:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::DASH;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE YOUR FIGHTER UPTO 3 SPACES")
                });
                break;
            
            case cards::THE_GAME_IS_AFOOT:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::GAME_IS_AFOOT;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("MOVE SHERLOCK UPTO 3 SPACES")
                });
                break;
            
            case cards::THIRST_FOR_SUSTENANCE:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::THIRST_FOR_SUSTENANCE;
                if(control.return_who_won_the_combat() != Attacker)
                {
                    break;
                }
                Describtion_For_User = vbox({
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("CHOOSE A SPACE TO MOVE DRACULA ADJACENT TO THE OPPISNG FIGHTER"),
                    text(" ")
                });

                break;
            
            case cards::STUDY_METHODS:
                after_effect_card_screen = AFTER_COMBAT_SUB_SCREENS::STUDY_METHODS;
                Describtion_For_User = vbox({
                    text(" "),
                    text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                    text(" "),
                    text("TAKE A LOOK AT YOUR OPPONENTS HAND"),
                    text(" "),

                    control.Return_Hand_Elements_For_Render(Defender)
                });
                break;
            
            default:
                break;
            }

            auto continue_button = Button("CONTINUE", [&]{
                screen.ExitLoopClosure()();
            });

            screen.Loop(Renderer(continue_button, [&]{
                return vbox({
                    Describtion_For_User | hcenter,
                    continue_button -> Render() | size(WIDTH, EQUAL, 45) | hcenter
                }) | center;
            }));
            After_Combat_Sub_Screen_Manager after_combet_sub_screens(control.Return_Selected_Card_Name_As_An_Enum(Attacker, Attacker_Selected_Card_Index), Attacker, after_effect_card_screen);
            while(true)
            {
                if(!after_combet_sub_screens.Screen_Manager(control))
                {
                    break;
                }
            }

        }

        if(control.Return_Selected_Card_Effect_Type(Defender, Defender_Selected_Card_Index) != CARD_EFFECT_TYPE::AFTER_COMBAT && control.Return_Selected_Card_Effect_Type(Attacker, Attacker_Selected_Card_Index) != CARD_EFFECT_TYPE::AFTER_COMBAT && No_Effect_Should_occur)
        {
            auto screen = ScreenInteractive::Fullscreen();


            Describtion_For_User = vbox({
                text(" "),
                text("AFTER COMBAT RESULTS") | underlined | color(Color::NavajoWhite3) | bold | size(WIDTH, EQUAL, 90),
                text(" "),
                text("NO EFFECTS") | center
            });

            auto continue_button = Button("CONTINUE", [&]{
                screen.ExitLoopClosure();
            });

            screen.Loop(Renderer(continue_button, [&]{
                return vbox({
                    Describtion_For_User | hcenter,
                    continue_button -> Render() | size(WIDTH, EQUAL, 45) | hcenter 
                })| center;
            }));
        }


    }

    current_screen = FIGHTING_SCREEN_SUB_SCREENS::RETURN_TO_MAIN_LOOP;

    
}

void Fighting_Screen_Manager::Elementary_Defence_Card_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    std::vector<std::string> enemy_card_value_guess = {"1", "2", "3", "4", "5", "6"};
    int current_sub_screen = 0;
    int guessed_value = 0;
    bool elementary_card_effect_applied_exit_the_loop = false;
    int selected = 0;
    

    while(!elementary_card_effect_applied_exit_the_loop)
    {
        switch (current_sub_screen)
        {
        case 0:
            {
                //take the guess   
                auto confirm_button = Button("CONFIRM", [&]{
                    guessed_value = std::stoi(enemy_card_value_guess[selected]);
                    current_sub_screen++;
                    screen.ExitLoopClosure()();
                });
                auto radio_box = Radiobox(&enemy_card_value_guess, &selected);
                auto container = Container::Vertical({radio_box, confirm_button});
                screen.Loop(Renderer(container, [&]{
                    
                    return vbox({
                        vbox({
                            text(" "),
                            text("SELECTED CARD: ELEMENTARY") | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3) | hcenter,
                            text(" "),
                            text("GUESS YOUR OPPONENT'S CARD VALUE: ") | bold ,
                            text(" "),
                            container->Render() | size(WIDTH, EQUAL, 100) | hcenter
                        }) | center
                    }) | border;
                }));
                break;
            }        
        case 1:
            {
                //report
                bool has_defender_guessed_correctly = false;
                if(control.Return_card_Value(control.Return_User_Turn(), Attacker_Selected_Card_Index) == guessed_value)
                {
                    has_defender_guessed_correctly = true;
                }

                auto continue_button = Button("CONTINUE", [&]{
                    if(has_defender_guessed_correctly)
                    {
                        control.Disable_Card_Effect(control.Return_User_Turn(), Attacker_Selected_Card_Index);
                        control.Set_Card_Value(control.Return_User_Turn(), Attacker_Selected_Card_Index, 0);

                    }
                    current_sub_screen++;
                    screen.ExitLoopClosure()();
                });

                Element Results;
                if(has_defender_guessed_correctly)
                {
                    Results = vbox({
                        vbox({
                            text(" "),
                            text("GUESS RESULT") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                            text(" "),
                            text("CONGRATULATIONS: YOUR GUESS WAS CORRECT") | bold,
                            text(" "),
                            text("ENEMY'S CARD EFFECT HAS BEEN DISABLED ") | bold,
                            text(" "),
                            text("ENEMY'S CARD VALUE HAS BEEN SET TO 0") | bold,
                            continue_button -> Render() | hcenter | size(WIDTH, EQUAL, 100)
                        }) | center
                    }) | border;
                }
                else
                {
                    Results = vbox({
                        vbox({
                            text(" "),
                            text("GUESS RESULT") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                            text(" "),
                            text("WHOOPS YOUR GUESS WAS WRONG WE CONTINUE AS NORMAL") | bold,
                            text(" "),
                            continue_button -> Render() | hcenter | size(WIDTH, EQUAL, 100)
                        }) | center
                    }) | border;
                }
                break;
                screen.Loop(Renderer(continue_button, [&]{
                    return Results;
                }));
            }
        case 2:
            //exit
            elementary_card_effect_applied_exit_the_loop = true;
            current_screen = FIGHTING_SCREEN_SUB_SCREENS::IMMIDATE_RESULTS_SCREEN;

            break;
        
        }
    }
}