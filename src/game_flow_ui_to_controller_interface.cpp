#include "../headers/game_flow_ui_to_controller_interface.hpp"
#include "../headers/graph.hpp"
#include "../headers/controller.hpp"
#include <vector>
#include <string>
#include <set>

#include <iostream>
#include <thread>
#include <chrono>


using namespace ftxui;

User_Choice_Manager::User_Choice_Manager()
{
    game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;

}

bool User_Choice_Manager::Screen_Manager(USER user_turn, Controller& control, const Element& map_and_user_info,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
{
    switch (game_current_screen)
    {
        case GAME_FLOW_SCREENS::CHOOSE_FIGHTER:
            Choose_Fighter_Screen(user_turn, control, map_and_user_info);
            return true;

        case GAME_FLOW_SCREENS::CHOOSE_ACTION:
            Choose_Action_Screen(user_turn, control, map_and_user_info);
            return true;

        case GAME_FLOW_SCREENS::MANEUVER:
            Maneuver_Screen(user_turn, control, map_and_user_info, fighter_printing_info, fighters_count);
            return true;

        case GAME_FLOW_SCREENS::SCHEME:
            // Scheme_Screen(user_turn, control, map_and_user_info);
            return true;

        case GAME_FLOW_SCREENS::ATTACK:
            // Attack_Screen(user_turn, control, map_and_user_info);
            return true;

        case GAME_FLOW_SCREENS::GO_BACK_TO_MAIN_LOOP:
            return false;
        
    }
    return false;
}


void User_Choice_Manager::Maneuver_Screen(USER user_turn, Controller& control, const Element& map_and_user_info,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
{

    auto screen = ScreenInteractive::Fullscreen();

    Graph* game_graph = Graph::Get_Map_Graph_Pointer();
    
    std::vector <std::string> Spaces_That_Fighter_Can_Move_To_RadioBox_Option;
    std::set <int> Available_Spaces;
    int Selected_Space_For_Move = 0;
    
    //this function assigns all the available spaces to the local set we just created
    (*game_graph).Recursive_Path_Finder(Available_Spaces, control.Return_Hero_Space_Number(selected_fighter), control.Return_Fighter_Move_Value(selected_fighter));
    

    for(auto element: Available_Spaces)
    {
        Spaces_That_Fighter_Can_Move_To_RadioBox_Option.push_back(std::to_string(element));
    }

    Component Available_Spaces_RadioBox = Radiobox(&Spaces_That_Fighter_Can_Move_To_RadioBox_Option, &Selected_Space_For_Move);


    Component Maneuver_Confirm_Button = Button("Confirm", [&]{
        control.Set_Fighter_Space_Number(selected_fighter, std::stoi(Spaces_That_Fighter_Can_Move_To_RadioBox_Option[Selected_Space_For_Move])) ;
        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(selected_fighter), temp_struct_to_update_fighter_position_on_screen);
        fighter_printing_info[static_cast<int>(selected_fighter)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        fighter_printing_info[static_cast<int>(selected_fighter)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
        if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
        {
            control.Change_User_Turn();
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
        }
        else
        {
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        }
        screen.ExitLoopClosure()();
    });

    Component Undo_Button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        screen.ExitLoopClosure()();
    });

    auto Moving_Fighter_Interactive_Ui = Container::Vertical({
        Available_Spaces_RadioBox,
        Maneuver_Confirm_Button,
        Undo_Button
    });



    screen.Loop(Renderer(Moving_Fighter_Interactive_Ui, [&]{
        return vbox({
            map_and_user_info,
            text("Choose space: "),
            Moving_Fighter_Interactive_Ui->Render()
        });        
    }));



}

void User_Choice_Manager::Choose_Fighter_Screen(USER user_turn, Controller& control, const Element& map_and_user_info)
{
    
    auto screen = ScreenInteractive::Fullscreen();
    
    std::vector <std::string> Selectable_Fighters;
    std::vector <Fighters_Names> Selectable_Fighters_Enum_Vector;
    int selected_fighter = 0;
    Element Text_Explanation = text("Choose a Fighter: ");
    Element User_Turn_Text;
    HERO_NAME user_hero;
    Component Confirm_Button = Button({"Confirm", [&]{
        User_Choice_Manager::selected_fighter = Selectable_Fighters_Enum_Vector[selected_fighter];
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        screen.ExitLoopClosure()();
    }});
    
   
    
    if(user_turn == USER::USER1)
    {
        User_Turn_Text = hbox({text("User Turn: "), text(control.Return_User1_Username())});
        if(control.Return_User1_Hero_Name() == HERO_NAME::DRACULA)
        {
            user_hero = HERO_NAME::DRACULA;
        }
        else
        {
            user_hero = HERO_NAME::SHERLOCK;
        }
    }
    else
    {
        User_Turn_Text = hbox({text("User Turn: "), text(control.Return_User2_Username())});
        if(control.Return_User2_Hero_Name() == HERO_NAME::DRACULA)
        {
            user_hero = HERO_NAME::DRACULA;
        }
        else
        {
            user_hero = HERO_NAME::SHERLOCK;
        }
    }


    if(user_hero == HERO_NAME::SHERLOCK)
    {
        Selectable_Fighters = {"SHERLOCK", "WATSON"};
        Selectable_Fighters_Enum_Vector = {Fighters_Names::SHERLOCK, Fighters_Names::WATSON};
    }
    else
    {
        Selectable_Fighters = {"DRACULA", "SISTER1", "SISTER2", "SISTER3"};
        Selectable_Fighters_Enum_Vector = {Fighters_Names::DRACULA, Fighters_Names::SIS1, Fighters_Names::SIS2, Fighters_Names::SIS3};
    }



    Component Fighters_RadioBox = Radiobox(&Selectable_Fighters, &selected_fighter);
    Component Fighter_Selection_Container = Container::Vertical({Fighters_RadioBox, Confirm_Button});
    screen.Loop(Renderer(Fighter_Selection_Container, [&]{
        return vbox({
            User_Turn_Text,
            map_and_user_info,
            Text_Explanation,
            Fighter_Selection_Container->Render()
        });
    }));

}


void User_Choice_Manager::Choose_Action_Screen(USER user_turn, Controller& control, const Element& map_and_user_info)
{
    auto screen = ScreenInteractive::Fullscreen();


    std::vector <std::string> options = {"MANEUVER", "USE CARDS"};
    int selected = 0;
    Component radio_box = Radiobox(&options, &selected);
    Component confirm_button = Button("Confirm", [&]{
        if(selected == 0)
        {
            game_current_screen = GAME_FLOW_SCREENS::MANEUVER;
        }
        else if(selected == 1)
        {
            game_current_screen = GAME_FLOW_SCREENS::Card_Screen;
        }
        screen.ExitLoopClosure()();
        
    });
    Component Undo_Button = Button("Undo", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
        screen.ExitLoopClosure()();
    });
    Component Action_Select_Container = Container::Vertical({radio_box, confirm_button, Undo_Button});

    std::string user_turn_name;
    if(user_turn == USER::USER1)
    {
        user_turn_name = control.Return_User1_Username();
    }
    else
    {
        user_turn_name = control.Return_User2_Username();
    }


    screen.Loop(Renderer(Action_Select_Container, [&]{
        return vbox({
            text(user_turn_name),
            map_and_user_info,
            text("Choose Your Action: "),
            Action_Select_Container->Render()
        });
    }));
}