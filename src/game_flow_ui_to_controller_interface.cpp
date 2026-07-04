#include "../headers/game_flow_ui_to_controller_interface.hpp"
#include "../headers/graph.hpp"
#include <vector>
#include <string>
#include <set>

using namespace ftxui;

User_Choice_Manager::User_Choice_Manager()
{
    game_current_screen = GAME_FLOW_SCREENS::MANEUVER;
    selected_fighter = Fighters_Names::DRACULA;
}

bool User_Choice_Manager::Screen_Manager(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
{
    switch (game_current_screen)
    {
        case GAME_FLOW_SCREENS::CHOOSE_FIGHTER:
            // Choose_Fighter_Screen(user_turn, control, map_and_user_info);
            return true;

        case GAME_FLOW_SCREENS::CHOOSE_ACTION:
            // Choose_Action_Screen(user_turn, control, map_and_user_info);
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


void User_Choice_Manager::Maneuver_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_user_info,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
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
        control.Set_Fighter_Space_Number(selected_fighter, stoi(Spaces_That_Fighter_Can_Move_To_RadioBox_Option[Selected_Space_For_Move])) ;
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