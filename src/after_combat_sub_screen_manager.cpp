#include "../headers/after_combat_sub_screen_manager.hpp"
#include "../headers/graph.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using namespace ftxui;

After_Combat_Sub_Screen_Manager::After_Combat_Sub_Screen_Manager(cards selected_card_name, USER user_turn, AFTER_COMBAT_SUB_SCREENS screen)
{
    std::cout << "entered the screen manager constructor \n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    switch (selected_card_name)
    {
    case cards::DASH:
        current_screen = AFTER_COMBAT_SUB_SCREENS::DASH;
        break;
    
    case cards::THIRST_FOR_SUSTENANCE:
        current_screen = AFTER_COMBAT_SUB_SCREENS::THIRST_FOR_SUSTENANCE;
        break;
    
    case cards::THE_GAME_IS_AFOOT:
        current_screen = AFTER_COMBAT_SUB_SCREENS::GAME_IS_AFOOT;
        break;
    
    case cards::STUDY_METHODS:
        current_screen = AFTER_COMBAT_SUB_SCREENS::STUDY_METHODS;
        break;
    


    default:
        current_screen = AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER;
        break;
    }

    this->user_turn = user_turn;
    this->current_screen = screen;
}


bool After_Combat_Sub_Screen_Manager::Screen_Manager(Controller& control)
{
    std::cout << "entered the screen manager brancher \n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    switch (current_screen)
    {
    case AFTER_COMBAT_SUB_SCREENS::DASH:
        Dash_Card_Screen(control);
        return true;

    case AFTER_COMBAT_SUB_SCREENS::THIRST_FOR_SUSTENANCE:
        // Thirst_For_Sustenance_Screen(control);
        return true;

    case AFTER_COMBAT_SUB_SCREENS::GAME_IS_AFOOT:
        // Game_Is_Afoot(control);
        return true;

    case AFTER_COMBAT_SUB_SCREENS::STUDY_METHODS:
        return false;

    case AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER:
        return false;
    
    }
}

void After_Combat_Sub_Screen_Manager::Dash_Card_Screen(Controller& control)
{


    std::string selected_dracula_crew_fighter_name_to_move;

    switch (control.Which_Fighter_Is_Currently_Selected(HERO_NAME::DRACULA))
    {
    case Fighters_Names::DRACULA:
        selected_dracula_crew_fighter_name_to_move = "DRACULA";
        break;
    
    case Fighters_Names::SIS1:
        selected_dracula_crew_fighter_name_to_move = "SISTER1";
        break;
    
    case Fighters_Names::SIS2:
        selected_dracula_crew_fighter_name_to_move = "SISTER2";
        break;
    
    case Fighters_Names::SIS3:
        selected_dracula_crew_fighter_name_to_move = "SISTER3";
        break;
    }

    auto screen = ScreenInteractive::Fullscreen();
    Graph* game_graph = Graph::Get_Map_Graph_Pointer();
    std::set<int> Spaces_That_Fighter_Can_Move_To;
    USER user_who_ownes_dracula_and_sisters;
    Fighters_Names Who_Is_Going_To_Use_Dash;
    if(HERO_NAME::DRACULA == control.Return_User1_Hero_Name())
    {
        user_who_ownes_dracula_and_sisters = USER::USER1;
    }
    else 
    {
        user_who_ownes_dracula_and_sisters = USER::USER2;
    }

    Who_Is_Going_To_Use_Dash = control.Which_Fighter_Is_Currently_Selected(HERO_NAME::DRACULA);

    // Spaces_That_Fighter_Can_Move_To = game_graph->Available_Spaces_For_Moving(3, control.Return_Hero_Space_Number(Who_Is_Going_To_Use_Dash), user_who_ownes_dracula_and_sisters);
    game_graph->Recursive_Path_Finder(Spaces_That_Fighter_Can_Move_To,control.Return_Hero_Space_Number(Who_Is_Going_To_Use_Dash), 3, user_who_ownes_dracula_and_sisters);
    std::vector<std::string> available_spaces_for_render;
    for(int space_number : Spaces_That_Fighter_Can_Move_To)
    {
        available_spaces_for_render.push_back(std::to_string(space_number));
    }
    int selected = 0;
    auto toggle_box_for_render = Toggle(&available_spaces_for_render, &selected);
    auto confirm_button = Button("CONFIRM", [&]{
        int former_occupied_space = control.Return_Hero_Space_Number(Who_Is_Going_To_Use_Dash);
        USER current_user_occupying_the_space = game_graph->Get_User_Occupying_Space(former_occupied_space);
        game_graph->Set_User_Occupying_Space(USER::NONE, former_occupied_space);
        game_graph->Change_Space_Occiupied_Status(former_occupied_space);
        control.Set_Fighter_Space_Number(Who_Is_Going_To_Use_Dash, std::stoi(available_spaces_for_render[selected]));
        game_graph->Set_User_Occupying_Space(current_user_occupying_the_space, std::stoi(available_spaces_for_render[selected]));
        game_graph->Change_Space_Occiupied_Status(std::stoi(available_spaces_for_render[selected]));
        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Who_Is_Going_To_Use_Dash), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Who_Is_Going_To_Use_Dash)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Who_Is_Going_To_Use_Dash)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;        
        current_screen =  AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER;
        screen.ExitLoopClosure()();
    });
    auto skip_button = Button("SKIP THE EFFECT", [&]{
        current_screen =  AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER;
        screen.ExitLoopClosure()();
    });
    auto container = Container::Vertical({
        toggle_box_for_render,
        confirm_button,
        skip_button
    });
    
    
    screen.Loop(Renderer(container, [&]{
        return vbox({
            text(" "),
            hbox({text("SELECTED FIGHTER: "), text(selected_dracula_crew_fighter_name_to_move)}) | hcenter | bold | underlined | color(Color::NavajoWhite3) | size(WIDTH, EQUAL, 100),
            text(" "),
            control.map_and_user_info | hcenter,
            text(" "),
            text("CHOOSE A SPACE OR SKIP") ,
            text(" "),
            container -> Render() | size(WIDTH, EQUAL, 100),
        }) | center;
    }));

}

void After_Combat_Sub_Screen_Manager::Game_Is_Afoot(Controller& control)
{

    auto screen = ScreenInteractive::Fullscreen();
    Graph* game_graph = Graph::Get_Map_Graph_Pointer();
    std::set<int> Spaces_That_Fighter_Can_Move_To;
    USER user_who_owns_sherlock;
    if(HERO_NAME::SHERLOCK == control.Return_User1_Hero_Name())
    {
        user_who_owns_sherlock = USER::USER1;
    }
    else 
    {
        user_who_owns_sherlock = USER::USER2;
    }


    game_graph->Recursive_Path_Finder(Spaces_That_Fighter_Can_Move_To,control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), 3, user_who_owns_sherlock);
    std::vector<std::string> available_spaces_for_render;
    for(int space_number : Spaces_That_Fighter_Can_Move_To)
    {
        available_spaces_for_render.push_back(std::to_string(space_number));
    }
    int selected = 0;
    auto toggle_box_for_render = Toggle(&available_spaces_for_render, &selected);
    auto confirm_button = Button("CONFIRM", [&]{
        int former_occupied_space = control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK);
        USER current_user_occupying_the_space = game_graph->Get_User_Occupying_Space(former_occupied_space);
        game_graph->Set_User_Occupying_Space(USER::NONE, former_occupied_space);
        game_graph->Change_Space_Occiupied_Status(former_occupied_space);
        control.Set_Fighter_Space_Number(Fighters_Names::SHERLOCK, std::stoi(available_spaces_for_render[selected]));
        game_graph->Set_User_Occupying_Space(current_user_occupying_the_space, std::stoi(available_spaces_for_render[selected]));
        game_graph->Change_Space_Occiupied_Status(std::stoi(available_spaces_for_render[selected]));
        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::SHERLOCK)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::SHERLOCK)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;        
        current_screen =  AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER;
        screen.ExitLoopClosure()();
    });
    auto skip_button = Button("SKIP THE EFFECT", [&]{
        current_screen =  AFTER_COMBAT_SUB_SCREENS::RETURN_TO_FIGHTING_SCREEN_MANAGER;
        screen.ExitLoopClosure()();
    });
    auto container = Container::Vertical({
        toggle_box_for_render,
        confirm_button,
        skip_button
    });
    
    
    screen.Loop(Renderer(container, [&]{
        return vbox({
            text(" "),
            hbox({text("SELECTED FIGHTER: "), text("SHERLOCK")}) | hcenter | bold | underlined | color(Color::NavajoWhite3) | size(WIDTH, EQUAL, 100),
            text(" "),
            control.map_and_user_info | hcenter,
            text(" "),
            text("CHOOSE A SPACE OR SKIP") ,
            text(" "),
            container -> Render() | size(WIDTH, EQUAL, 100),
        }) | center;
    }));

}