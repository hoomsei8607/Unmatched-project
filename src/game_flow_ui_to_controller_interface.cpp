#include "../headers/game_flow_ui_to_controller_interface.hpp"
#include "../headers/graph.hpp"
#include "../headers/cards.hpp"
#include "../headers/controller.hpp"
#include "../headers/Fighting_Screen_Manager_Class.hpp"
#include "../headers/scheme_card_manager_class.hpp"
#include <vector>
#include <string>
#include <set>



using namespace ftxui;

User_Choice_Manager::User_Choice_Manager()
{
    game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;

}

bool User_Choice_Manager::Screen_Manager(USER user_turn, Controller& control,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
{
    switch (game_current_screen)
    {
        case GAME_FLOW_SCREENS::CHOOSE_FIGHTER:
            Choose_Fighter_Screen(control.Return_User_Turn(), control);
            return true;

        case GAME_FLOW_SCREENS::CHOOSE_ACTION:
            Choose_Action_Screen(control.Return_User_Turn(), control);
            return true;

        case GAME_FLOW_SCREENS::MANEUVER:
            Maneuver_Screen(control.Return_User_Turn(), control, fighter_printing_info, fighters_count);
            return true;


        case GAME_FLOW_SCREENS::Card_Selection_Screen:
            Select_Card_Screen(control.Return_User_Turn(), control, control.map_and_user_info);
            return true;

        
        case GAME_FLOW_SCREENS::FIGHTING_SCREEN:
            Fighting_Screen(control.Return_User_Turn(), control);
            return true;

        case GAME_FLOW_SCREENS::CHOOSE_MANEUVER_TYPE:
            Choose_Maneuver_Type(control);
            return true;

        case GAME_FLOW_SCREENS::MANEUVER_BOOST_SCREEN:
            Choose_Card_To_Boost_Maneuver_With(control.Return_User_Turn(), control);
            return true;

        case GAME_FLOW_SCREENS::CHOOSE_YOUR_ENEMY_SCREEN:
            Choose_Enemy_Screen(control);
            return true;
        
        case GAME_FLOW_SCREENS::SCHEME_CARD_MANAGER:
            Scheme_Card_Manager_Screen(control);
            return true;

        case GAME_FLOW_SCREENS::GAME_OVER_SCREEN:
            Game_Over_Screen(control);
            return true;

        case GAME_FLOW_SCREENS::GO_BACK_TO_MAIN_LOOP:
            return false;
        
    }
    return false;
}


void User_Choice_Manager::Maneuver_Screen(USER user_turn, Controller& control,  Fighters_Print_Info* fighter_printing_info, int fighters_count)
{

    
    std::string selected_hero_name = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);
    Graph* game_graph = Graph::Get_Map_Graph_Pointer();
    
    std::vector <std::string> Spaces_That_Fighter_Can_Move_To_RadioBox_Option;
    std::set <int> Available_Spaces;
    int Selected_Space_For_Move = 0;
    
    //this function assigns all the available spaces to the local set we just created
    (*game_graph).Recursive_Path_Finder(Available_Spaces, control.Return_Hero_Space_Number(selected_fighter), control.Return_Fighter_Move_Value(selected_fighter), user_turn);
    Available_Spaces.erase(control.Return_Hero_Space_Number(selected_fighter));

    for(auto element: Available_Spaces)
    {
        Spaces_That_Fighter_Can_Move_To_RadioBox_Option.push_back(std::to_string(element));
    }

    Component Available_Spaces_RadioBox = Radiobox(&Spaces_That_Fighter_Can_Move_To_RadioBox_Option, &Selected_Space_For_Move);


    Component Maneuver_Confirm_Button = Button("Confirm", [&]{
        USER space_occupied_by_which_user = game_graph->Get_User_Occupying_Space(control.Return_Hero_Space_Number(selected_fighter));
        game_graph->Set_User_Occupying_Space(USER::NONE, control.Return_Hero_Space_Number(selected_fighter));
        game_graph->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(selected_fighter));

        control.Set_Fighter_Space_Number(selected_fighter, std::stoi(Spaces_That_Fighter_Can_Move_To_RadioBox_Option[Selected_Space_For_Move])) ;
        control.draw(user_turn);
        game_graph->Set_User_Occupying_Space(space_occupied_by_which_user, control.Return_Hero_Space_Number(selected_fighter));
        game_graph->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(selected_fighter));
        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(selected_fighter), temp_struct_to_update_fighter_position_on_screen);
        fighter_printing_info[static_cast<int>(selected_fighter)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        fighter_printing_info[static_cast<int>(selected_fighter)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
        control.Update_Fighters_Living_Status_In_Printing_Info_Array();
        control.Update_Map();
        control.Clean_Up_The_Graph();
        if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
        {
            control.Discard_Cards_If_Deck_Has_More_Than_7_Cards(control.Return_User_Turn());
            control.Change_User_Turn();
            
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
        }
        else
        {
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
        }
        control.Reset_Fighter_Move_Value(selected_fighter);
        control.screen.ExitLoopClosure()();
    });

    Component Undo_Button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        control.screen.ExitLoopClosure()();
    });

    auto Moving_Fighter_Interactive_Ui = Container::Vertical({
        Available_Spaces_RadioBox,
        Maneuver_Confirm_Button,
        Undo_Button
    });



    control.screen.Loop(Renderer(Moving_Fighter_Interactive_Ui, [&]{
        return vbox({
            hbox({text("SELECTED FIGHTER: "), text(selected_hero_name)}) | hcenter,
            control.map_and_user_info | hcenter,
            text("Choose space: "),
            Moving_Fighter_Interactive_Ui->Render()
        }) | size(WIDTH, EQUAL, 120) | center;        
    }));



}

void User_Choice_Manager::Choose_Fighter_Screen(USER user_turn, Controller& control)
{
    
    
    
    std::vector <std::string> Selectable_Fighters;
    std::vector <Fighters_Names> Selectable_Fighters_Enum_Vector;
    int selected_fighter = 0;
    Element Text_Explanation = text("Choose a Fighter: ");
    Element User_Turn_Text;
    HERO_NAME user_hero;
    Component Confirm_Button = Button({"Confirm", [&]{
        User_Choice_Manager::selected_fighter = Selectable_Fighters_Enum_Vector[selected_fighter];
        attack_type = control.Return_Fighter_Attacking_Range(User_Choice_Manager::selected_fighter);
        control.Select_Fighter(User_Choice_Manager::selected_fighter);
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        control.screen.ExitLoopClosure()();
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
    control.screen.Loop(Renderer(Fighter_Selection_Container, [&]{
        return vbox({
            User_Turn_Text | hcenter,
            control.map_and_user_info | hcenter,
            Text_Explanation,
            Fighter_Selection_Container->Render()
        }) | size(WIDTH, EQUAL, 120) | center;
    }));

}


void User_Choice_Manager::Choose_Action_Screen(USER user_turn, Controller& control)
{
    

    std::string selected_hero_name_as_string = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);
    std::vector <std::string> options = {"MANEUVER", "USE CARDS"};
    int selected = 0;
    Component radio_box = Radiobox(&options, &selected);
    Component confirm_button = Button("Confirm", [&]{
        if(selected == 0)
        {
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_MANEUVER_TYPE;
        }
        else if(selected == 1)
        {
            game_current_screen = GAME_FLOW_SCREENS::Card_Selection_Screen;
        }
        control.screen.ExitLoopClosure()();
        
    });
    Component Undo_Button = Button("Undo", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
        control.screen.ExitLoopClosure()();
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


    control.screen.Loop(Renderer(Action_Select_Container, [&]{
        return vbox({
            hbox({text("SELECTED FIGHTER: "), text(selected_hero_name_as_string)}) | hcenter,
            control.map_and_user_info | hcenter,
            text("Choose Your Action: "),
            Action_Select_Container->Render()
        }) | size(WIDTH, EQUAL, 120) | center;
    }));
}

void User_Choice_Manager::Select_Card_Screen(USER user_turn, Controller& control, const ftxui::Element& map_and_use_info)
{
    Fighters_Names Attacker_Fighter_Name = selected_fighter;
    std::string selected_fighter_name_as_string = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);
    std::string user_trun_name_string;
    Graph* map_graph = Graph::Get_Map_Graph_Pointer();
    std::vector<Card_Base_Class*>copy_of_user_hand;
    std::vector<std::string> Card_Options = control.Return_Hand_As_String(user_turn);
    int selected = 0;

    

    if(user_turn == USER::USER1)
    {
        user_trun_name_string = control.Return_User1_Username();
        copy_of_user_hand = control.Return_A_Copy_Of_User_Hand(USER::USER1);
    }
    else
    {
        user_trun_name_string = control.Return_User2_Username();
        copy_of_user_hand = control.Return_A_Copy_Of_User_Hand(USER::USER2);
    }

    if(selected_fighter == Fighters_Names::SIS1 || selected_fighter == Fighters_Names::SIS2 || selected_fighter == Fighters_Names::SIS3)
    {
        Attacker_Fighter_Name = Fighters_Names::SISTERS;
    }




    Component Confirm_Button = Button("CONFIRM", [&]{
        if(copy_of_user_hand[selected]->get_type() == CARD_TYPE::ATTACK || copy_of_user_hand[selected]->get_type() == CARD_TYPE::VERSATILE )
        {
            game_current_screen = GAME_FLOW_SCREENS::CHOOSE_YOUR_ENEMY_SCREEN;
            selected_Attacker_card_index = selected;
            attacker_card_value = control.Return_card_Value(control.Return_User_Turn(), selected);
        }
        else if(copy_of_user_hand[selected]->get_type() == CARD_TYPE::SCHEME)
        {
            game_current_screen = GAME_FLOW_SCREENS::SCHEME_CARD_MANAGER;
            selected_Attacker_card_index = selected;
            attacker_card_value = 0;
        }
        control.screen.ExitLoopClosure()();

    });

    Component Undo_Button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        
        control.screen.ExitLoopClosure()();
    });

    Component Card_Select_RadioBox = Toggle(&Card_Options, &selected);

    
    
    Confirm_Button = Confirm_Button | Maybe([&]{
        
        if(control.Return_Card_Owner_Name(control.Return_User_Turn(), selected) != Fighters_Names::ANY && control.Return_Card_Owner_Name(control.Return_User_Turn(), selected) != Attacker_Fighter_Name )
        {
            return false;
        }
        
        if(control.Return_Selected_Card_Type(user_turn, selected) == CARD_TYPE::DEFENCE)
        {
            return false;
        }
        
        if(control.Return_Selected_Card_Type(user_turn, selected) == CARD_TYPE::VERSATILE || control.Return_Selected_Card_Type(user_turn, selected) == CARD_TYPE::ATTACK )
        {
            if(!map_graph->Can_Fighter_Use_Attacking_Cards(user_turn,control.Return_Fighter_Attacking_Range(selected_fighter), control.Return_Hero_Space_Number(selected_fighter)))
            {
                return false;
            }
            
        }
        if(control.Return_Selected_Card_Name_As_An_Enum(user_turn, selected) == cards::AMINISTER_AID)
        {
            std::set<int> spaces_adjacent_to_sherlock;
            map_graph->Recursive_Path_Finder(spaces_adjacent_to_sherlock, control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), 1, user_turn);
            if(spaces_adjacent_to_sherlock.empty() || !control.Return_Is_Fighter_Alive(Fighters_Names::WATSON))
            {
                return false;
            }
        }
        
        
        return true;
    });
    Component card_select_container = Container::Vertical({Card_Select_RadioBox, Confirm_Button, Undo_Button});
    Element user_hand_for_render = control.Return_Hand_Elements_For_Render(user_turn);
    
    

    

    auto main_renderer = Renderer(card_select_container, [&]{

        return vbox({
            hbox({text("SELECTED FIGHTER: "), text(selected_fighter_name_as_string)}) | hcenter,
            map_and_use_info | hcenter,
            user_hand_for_render,
            card_select_container->Render()
        }) | center;
    });
    control.screen.Loop(main_renderer);
}


void User_Choice_Manager::Fighting_Screen(USER user_turn, Controller& control)
{
    Fighting_Screen_Manager fighting_screen_manager_object( attacker_card_value, selected_Attacker_card_index);
    while (true)
    {
        if(!fighting_screen_manager_object.Screen_Manager(control))
        {
            break;
        }
    }
    control.Update_Fighters_Living_Status_In_Printing_Info_Array();
    control.Update_Map();
    control.Clean_Up_The_Graph();
    if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
    {
        control.Discard_Cards_If_Deck_Has_More_Than_7_Cards(control.Return_User_Turn());
        control.Change_User_Turn();
    }
    
    //check to see if hero is alive if not end the game and announce the winner
    //otherwise go back to choosing fighter
    if(control.Is_Game_Over())
    {
        game_current_screen = GAME_FLOW_SCREENS::GAME_OVER_SCREEN;
    }
    else
    {
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
    }


}

void User_Choice_Manager::Choose_Maneuver_Type(Controller& control)
{
    std::string selected_fighter_name_as_string = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);
    
    bool Is_User_Hand_Empty = control.Is_User_Hand_Empty(control.Return_User_Turn());
    std::string user_turn_name_string;

    if(control.Return_User_Turn() == USER::USER1)
    {
        user_turn_name_string = control.Return_User1_Username();
    }
    else
    {
        user_turn_name_string = control.Return_User2_Username();
    }


    auto normal_button = Button("NORMAL MANEUVER", [&]{
        game_current_screen = GAME_FLOW_SCREENS::MANEUVER;
        control.screen.ExitLoopClosure()();
    });

    auto boost_button = Button("BOOST MANEUVER", [&]{
        game_current_screen = GAME_FLOW_SCREENS::MANEUVER_BOOST_SCREEN;
        control.screen.ExitLoopClosure()();
    });

    auto undo_button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_ACTION;
        control.screen.ExitLoopClosure()();
    });

    boost_button = boost_button | Maybe([&]{
        return !Is_User_Hand_Empty;
    });

    auto container = Container::Vertical({
        normal_button,
        boost_button,
        undo_button
    });

    control.screen.Loop(Renderer(container, [&]{
        return vbox({
            hbox({text("SELECTED FIGHTER: "), text(selected_fighter_name_as_string)}),
            container->Render() | size(WIDTH, EQUAL, 90)
        }) | hcenter | vcenter;
    }));

}

void User_Choice_Manager::Choose_Card_To_Boost_Maneuver_With(USER user_turn, Controller& control)
{
    std::string selected_fighter_name_as_string = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);
    std::string user_turn_name_string;
    std::string selected_fighter_name = control.Conver_Fighter_Name_Enum_To_String(selected_fighter);

    Element user_hand_for_render = control.Return_Hand_Elements_For_Render(user_turn);
    std::vector<std::string> user_hand_selectable = control.Return_Hand_As_String(user_turn);
    int selected_card = 0;

    

    auto confirm_button = Button("CONRIM", [&]{
        control.Boost_Fighter_Move_Value(selected_fighter, control.return_card_boost_value(selected_card, user_turn));
        control.discard(selected_card, user_turn);
        game_current_screen = GAME_FLOW_SCREENS::MANEUVER;
        control.screen.ExitLoopClosure()();
    });

    auto undo_button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_MANEUVER_TYPE;
        control.screen.ExitLoopClosure()();
    });

    if(user_turn == USER::USER1)
    {
        user_turn_name_string = control.Return_User1_Username();
    }
    else
    {
        user_turn_name_string = control.Return_User2_Username();
    }


    auto options_toggle_box = Toggle(&user_hand_selectable, &selected_card);
    auto container = Container::Vertical({
        options_toggle_box,
        confirm_button,
        undo_button
    });

    control.screen.Loop(Renderer(container,  [&]{
        return vbox({
            hbox({text("SELECTED FIGHTER: "), text(selected_fighter_name_as_string)}),
            hbox({text("SELECTED FIGHTER: "), text(selected_fighter_name)}),
            user_hand_for_render,
            container->Render()
        }) | size(WIDTH, EQUAL, 120) | center;
    }));

}

void User_Choice_Manager::Choose_Enemy_Screen(Controller& control)
{
    
    Graph* game_graph = Graph::Get_Map_Graph_Pointer();
    std::set<int> space_number_occupied_by_enemies;
    std::vector<Fighters_Names> Available_Enemies;
    std::vector<std::string> Available_Enemies_Strings;
    int selected_enemy;
    if(attack_type == ATTACKING_RANGE::MELEE)
    {
        space_number_occupied_by_enemies = game_graph->return_adjacent_enemies_space_numbers_for_melee_attack(control.Return_User_Turn(), control.Return_Hero_Space_Number(selected_fighter));
    }
    else if(attack_type == ATTACKING_RANGE::RANGED)
    {
        space_number_occupied_by_enemies = game_graph->return_adjacent_enemies_space_numbers_for_melee_attack(control.Return_User_Turn(), control.Return_Hero_Space_Number(selected_fighter));
    }


    for(int element : space_number_occupied_by_enemies)
    {
        Fighters_Names potential_enemy;
        potential_enemy = control.Return_Fighter_Base_On_Space_Number(element);
        if(potential_enemy != Fighters_Names::NONE)
        {
            Available_Enemies.push_back(potential_enemy);
        }
    }
    for(auto fighter : Available_Enemies)
    {
        Available_Enemies_Strings.push_back(control.Conver_Fighter_Name_Enum_To_String(fighter));
    }

    auto undo_button = Button("UNDO", [&]{
        game_current_screen = GAME_FLOW_SCREENS::Card_Selection_Screen;
        control.screen.ExitLoopClosure()();
    });

    auto confirm_button = Button("CONFIRM", [&]{
        control.Set_Selected_Enemy(Available_Enemies[selected_enemy]);
        game_current_screen = GAME_FLOW_SCREENS::FIGHTING_SCREEN;
        control.screen.ExitLoopClosure()();
    });

    auto enemy_options_toggle_box = Toggle(&Available_Enemies_Strings, &selected_enemy);

    auto container = Container::Vertical({
        enemy_options_toggle_box,
        confirm_button,
        undo_button
    });

    control.screen.Loop(Renderer(container, [&]{
        return vbox({
            text(" "),
            text("CHOOSE AN ENEMY TO ATTACK") | bold | underlined |  color(Color::NavajoWhite3) | size(WIDTH, EQUAL, 90) | hcenter,
            text(" "),
            text("AVAILABLE ENEMIES: ") | bold,
            container -> Render() | size(WIDTH, EQUAL, 90)
        }) | hcenter | vcenter;
    }));

    
}

void User_Choice_Manager::Scheme_Card_Manager_Screen(Controller& control)
{
    cards selected_scheme_card_name = control.Return_Selected_Card_Name_As_An_Enum(control.Return_User_Turn(), selected_Attacker_card_index);
    SCHEME_CARDS_SCREEN selected_card_screen;
    USER attacker = control.Return_User_Turn();
    switch (selected_scheme_card_name)
    {
    case cards::AMINISTER_AID:
        selected_card_screen = SCHEME_CARDS_SCREEN::ADMINISTER_AID_SCREEN;
        break;
    
    case cards::CONFIRM_SUSPICION:
        selected_card_screen = SCHEME_CARDS_SCREEN::CONFIRM_SUSPICION_SCREEN;
        break;

    case cards::ELIMINATE_THE_IMPOSSIBLE:
        selected_card_screen = SCHEME_CARDS_SCREEN::ELIMINATE_THE_IMPOSSIBLE_SCREEN;
        break;
        
    case cards::MASTER_OF_DISGUISE:
        selected_card_screen = SCHEME_CARDS_SCREEN::MASTER_OF_DISGUISE_SCREEN;
        break;
        
    case cards::MISTFORM:
        selected_card_screen = SCHEME_CARDS_SCREEN::MISTFORM_SCREEN;
        break;
        
    case cards::BAPTISM_OF_BLOOD:
        selected_card_screen = SCHEME_CARDS_SCREEN::BAPTISM_OF_BLOOD_SCREEN;
        break;
        
    case cards::PREY_UPON:
        selected_card_screen = SCHEME_CARDS_SCREEN::PREY_UPON_SCREEN;
        break;
        
    case cards::RAVENING_SEDUCTION:
        selected_card_screen = SCHEME_CARDS_SCREEN::RAVENING_SEDUCTION_SCREEN;
        break;
    }

    Scheme_Manager exec_scehem_card_effects(selected_card_screen);
    while(true)
    {
        if(!exec_scehem_card_effects.Screen_Manager(control))
        {
            break;
        }
    }
    control.discard(selected_Attacker_card_index, attacker);


    if(control.Is_Game_Over())
    {
        game_current_screen = GAME_FLOW_SCREENS::GAME_OVER_SCREEN;
    }
    else
    {
        game_current_screen = GAME_FLOW_SCREENS::CHOOSE_FIGHTER;
    }
    
}

void User_Choice_Manager::Game_Over_Screen(Controller& control)
{
    
    USER who_won = control.Return_Who_won_The_Game();
    std::string winner_user_name;
    if(who_won == USER::USER1)
    {
        winner_user_name = control.Return_User1_Username();
    }
    else
    {   
        winner_user_name = control.Return_User2_Username();
    }


    auto exit_button = Button("EXIT", [&]{
        game_current_screen = GAME_FLOW_SCREENS::GO_BACK_TO_MAIN_LOOP;
        control.screen.ExitLoopClosure()();
    });

    control.screen.Loop(Renderer(exit_button, [&]{
        return vbox({
            vbox({
                text(""),
                text("GAME OVER") | hcenter | size(WIDTH, EQUAL, 100) | underlined | color(Color::NavajoWhite3) | bold,
                text(""),
                hbox({text(winner_user_name), text(" WON THE GAME")}) | bold,
                text(""),
                exit_button->Render() | hcenter | size(WIDTH, EQUAL, 100)
            }) | center
        }) | border;
    }));
}
