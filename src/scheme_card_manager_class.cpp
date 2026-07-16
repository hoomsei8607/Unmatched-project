#include "../headers/scheme_card_manager_class.hpp"
#include <set>
#include "../headers/graph.hpp"
using namespace ftxui;

Scheme_Manager::Scheme_Manager(SCHEME_CARDS_SCREEN screen)
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
        // Confirm_Suspicion_Screen(control);
        return true;
    
    case SCHEME_CARDS_SCREEN::MISTFORM_SCREEN:
        Mistform_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::BAPTISM_OF_BLOOD_SCREEN:
        Baptism_Of_Blood_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::PREY_UPON_SCREEN:
        // Prey_Upon_Screen(control);
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
    auto screen = ScreenInteractive::Fullscreen();
    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();
    std::set<int> empty_spaces_on_the_map = game_map_ptr->return_all_unoccupied_spaces();
    std::vector<std::string> spaces_option_for_toggle_box;
    for(int space : empty_spaces_on_the_map)
    {
        spaces_option_for_toggle_box.push_back(std::to_string(space));
    }

    int selected_space = 0;
    auto toggle_box = Toggle(&spaces_option_for_toggle_box, &selected_space);

    auto confirm_button = Button("CONFIRM", [&]{
        int new_space_number = std::stoi(spaces_option_for_toggle_box[selected_space]);
        int former_space_number = control.Return_Hero_Space_Number(Fighters_Names::DRACULA);

        USER user_occupying_the_space = game_map_ptr->Get_User_Occupying_Space(former_space_number);

        game_map_ptr->Set_User_Occupying_Space(USER::NONE, former_space_number);
        game_map_ptr->Change_Space_Occiupied_Status(former_space_number);
        game_map_ptr->Set_User_Occupying_Space(user_occupying_the_space, new_space_number);
        game_map_ptr->Change_Space_Occiupied_Status(new_space_number);

        control.Set_Fighter_Space_Number(Fighters_Names::DRACULA, new_space_number);

        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::DRACULA), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;

        current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
        screen.ExitLoopClosure()();

    });
    auto container = Container::Vertical({toggle_box, confirm_button});
    screen.Loop(Renderer(container, [&]{
        return vbox({
            vbox({
                text(" "),
                text("CHOOSEN CARD: MISTFORM") | hcenter | bold | underlined | size(WIDTH, EQUAL, 90) | color(Color::NavajoWhite3),
                text(" "),
                text("MOVE DRACULA TO ONE OF THESE AVAILABLE SPACES WITHOUT LOSING YOUR TURN") | bold,
                text(" "),
                container -> Render()
            }) | center
        })| border;
    }));

}

void Scheme_Manager::Baptism_Of_Blood_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    bool Is_Any_Sister_Dead = control.Is_Any_Of_Dracula_Sisters_Dead();
    USER user_who_owns_dracula;
    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();

    if(control.Return_User1_Hero_Name() == HERO_NAME::DRACULA)
    {
        user_who_owns_dracula = USER::USER1;
    }
    else
    {
        user_who_owns_dracula = USER::USER2;
    }



    if(Is_Any_Sister_Dead)
    {
        std::set<int> available_spaces_to_place_the_revived_sister_on = game_map_ptr->return_all_spaces_with_the_corresponding_zones(game_map_ptr->return_zone(control.Return_Hero_Space_Number(Fighters_Names::DRACULA)));
        std::vector<std::string> options_for_toggle_box;
        int selected_space = 0;

        for(int space : available_spaces_to_place_the_revived_sister_on)
        {
            options_for_toggle_box.push_back(std::to_string(space));
        }

        auto toggle_box = Toggle(&options_for_toggle_box, &selected_space);
        auto confirm_button = Button("CONFIRM", [&]{
            int space_number_for_revived_sis = std::stoi(options_for_toggle_box[selected_space]);
            control.Revive_The_Selected_Fighter(control.Return_Dead_Sister_Number(), space_number_for_revived_sis);
            game_map_ptr->Set_User_Occupying_Space(user_who_owns_dracula, space_number_for_revived_sis);
            game_map_ptr->Change_Space_Occiupied_Status(space_number_for_revived_sis);

            Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
            control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::DRACULA), temp_struct_to_update_fighter_position_on_screen);
            control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
            control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
            screen.ExitLoopClosure()();
        });
        auto container = Container::Vertical({
            toggle_box,
            confirm_button
        });

        screen.Loop(Renderer(container, [&]{
            return vbox({
                vbox({
                    text(" "),
                    text("CHOOSEN CARD: BAPTISM OF BLOOD") | hcenter | bold | underlined | size(WIDTH, EQUAL, 90) | color(Color::NavajoWhite3),
                    text(" "),
                    text("DRACULA: +2HP") | bold,
                    text(" "),
                    text("DEAD SISTER: REVIVED") | bold,
                    text(" "),
                    text("SLECET WHERE TO PLACE THE REVIVED SISTER") | bold,
                    text(" "),
                    container -> Render() | size(WIDTH, EQUAL, 90)
                }) | center
            }) | border;

        }));


        


    }
    else
    {
        
        auto continue_button = Button("CONTINUE", [&]{
            screen.ExitLoopClosure()();
        });
        screen.Loop(Renderer(continue_button, [&]{
            return vbox({
                vbox({
                    text(" "),
                    text("CHOOSEN CARD: BAPTISM OF BLOOD") | hcenter | bold | underlined | size(WIDTH, EQUAL, 90) | color(Color::NavajoWhite3),
                    text(" "),
                    text("DRACULA: +2HP") | bold,
                    text(" "),
                    text("NO SISTER REVIVED") | bold,
                    text(" "),
                    continue_button -> Render() | size(WIDTH, EQUAL, 90)
                }) | center
            }) | border;
            
        }));
    }
    control.change_fighter_health(Fighters_Names::DRACULA, 2);
    current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
    if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
    {
        control.Change_User_Turn();
    }
}

void Scheme_Manager::Ravening_Seduction_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    std::set<int> available_spaces_to_move_the_enemy_to;
    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();
    

    USER enemy_user;
    if(control.Return_User_Turn() == USER::USER1)
    {
        enemy_user = USER::USER2;
    }
    else
    {
        enemy_user = USER::USER1;

    }



    int ravening_seduction_sub_screen_number = 0;
    bool card_effect_completed_successfuly = false;
    std::vector<Fighters_Names> selectable_heros = control.Return_Alive_Fighters(HERO_NAME::SHERLOCK);
    std::vector<std::string> options_for_toggle_box;

    for(auto fighter : selectable_heros)
    {
        options_for_toggle_box.push_back(control.Conver_Fighter_Name_Enum_To_String(fighter));
    }

    int selected_fighter_index = 0;

    while(!card_effect_completed_successfuly)
    {
        switch (ravening_seduction_sub_screen_number)
        {
            case 0:
            {
                //select fighter
                ravening_seduction_sub_screen_number++;
                auto toggle_box = Radiobox(&options_for_toggle_box, & selected_fighter_index);
                auto confirm_button = Button("CONFIRM", [&]{
                    screen.ExitLoopClosure()();
                });
                auto container = Container::Vertical({
                    toggle_box,
                    confirm_button
                });
                screen.Loop(Renderer(container, [&]{
                    return vbox({
                        vbox({
                            text(" "),
                            text("CHOOSEN CARD: RAVENING SEDUCTION") | hcenter | bold | underlined | size(WIDTH, EQUAL, 90) | color(Color::NavajoWhite3),
                            text(" "),
                            text("CHOOSE AN ENEMY TO MOVE UP TO 2 SPACES") | bold,
                            text(" "),
                            container->Render() | size(WIDTH, EQUAL, 90)
                            
                        }) | center
                    }) | border;
                }));
                break;
            }
        
            case 1:
            {
                //select where you wanna move the fighter to 
                ravening_seduction_sub_screen_number++;
                game_map_ptr->Recursive_Path_Finder(available_spaces_to_move_the_enemy_to, control.Return_Hero_Space_Number(selectable_heros[selected_fighter_index]), 2, enemy_user);
                std::vector<std::string> selectable_spaces_to_move_enemy;
                for(int space_number : available_spaces_to_move_the_enemy_to)
                {
                    selectable_spaces_to_move_enemy.push_back(std::to_string(space_number));
                }
                int selected_space = 0;
                auto confirm_button = Button("CONFIRM", [&]{

                    //move the fighter
                    int former_space_number = control.Return_Hero_Space_Number(selectable_heros[selected_fighter_index]);
                    int new_space_number = std::stoi(selectable_spaces_to_move_enemy[selected_space]);
                    game_map_ptr->Change_Space_Occiupied_Status(former_space_number);
                    game_map_ptr->Change_Space_Occiupied_Status(new_space_number);

                    game_map_ptr->Set_User_Occupying_Space(USER::NONE, former_space_number);
                    game_map_ptr->Set_User_Occupying_Space(enemy_user, new_space_number);

                    control.Set_Fighter_Space_Number(selectable_heros[selected_fighter_index], new_space_number);

                    Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
                    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::DRACULA), temp_struct_to_update_fighter_position_on_screen);
                    control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
                    control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;

                    screen.ExitLoopClosure()();
                });
                auto radio_box = Radiobox(&selectable_spaces_to_move_enemy, &selected_space);
                auto container = Container::Vertical({
                    radio_box,
                    confirm_button
                });

                screen.Loop(Renderer(container, [&]{
                    return vbox({
                        vbox({
                            text(" "),
                            text("CHOOSEN CARD: RAVENING SEDUCTION") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                            text(" "),
                            hbox({text("CHOOSEN ENEMY: "), text(options_for_toggle_box[selected_fighter_index])}),
                            text(" "),
                            control.map_and_user_info | hcenter,
                            text(" "),
                            text("CHOOSE A SPACE TO MOVE THE ENEMY TO"),
                            container->Render() | size(WIDTH, EQUAL, 100)
                            
                        }) | center
                    }) | border;
                }));

                break;
            }
        
            case 2:
            {
                //deal the damage
                ravening_seduction_sub_screen_number++;
                int adjacent_sisters = 0;
                bool there_are_sisters_adjacent_to_the_enemy = false;
                std::set<int> adjacent_enemies_space_numbers = game_map_ptr->return_adjacent_enemies_space_numbers_for_melee_attack(enemy_user, control.Return_Hero_Space_Number(selectable_heros[selected_fighter_index]));
                std::vector<int> sisters_space_numbers = control.Return_Sisters_Space_Numbers();
                for(int space_number : sisters_space_numbers)
                {
                    if(adjacent_enemies_space_numbers.count(space_number))
                    {
                        adjacent_sisters++;
                        there_are_sisters_adjacent_to_the_enemy = true;
                        adjacent_enemies_space_numbers.erase(space_number);
                    }
                }
                Element for_render;
                Component continue_button = Button("CONTINUE", [&]{
                    control.change_fighter_health(selectable_heros[selected_fighter_index], adjacent_sisters);
                    screen.ExitLoopClosure()();
                });
                
                screen.Loop(Renderer(continue_button, [&]{
                    if(there_are_sisters_adjacent_to_the_enemy)
                    {
                        return vbox({
                            vbox({
                                text(" "),
                                text("CHOOSEN CARD: RAVENING SEDUCTION") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                                text(" "),
                                hbox({text("CHOOSEN ENEMY: "), text(options_for_toggle_box[selected_fighter_index])}),
                                text(" "),
                                control.map_and_user_info | hcenter,
                                text(" "),
                                hbox({text(options_for_toggle_box[selected_fighter_index]), text(": -"), text(std::to_string(adjacent_sisters)), text("HP DUE TO ADJACENT SISTERS")}),
                                text(" "),
                                continue_button ->Render() | size(WIDTH, EQUAL, 100) | hcenter
                            }) | center
                        })|center;
                    }
                    else
                    {
                        return vbox({
                            vbox({
                                text(" "),
                                text("CHOOSEN CARD: RAVENING SEDUCTION") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                                text(" "),
                                hbox({text("CHOOSEN ENEMY: "), text(options_for_toggle_box[selected_fighter_index])}),
                                text(" "),
                                control.map_and_user_info | hcenter,
                                text(" "),
                                text("NO ADJACENT SISTERS"),
                                continue_button ->Render() | size(WIDTH, EQUAL, 100) | hcenter
                            }) | center
                        })|center;
                        
                    }
                }));

                break;
            }
        
            case 3:
            {
                // change turn and exit
                ravening_seduction_sub_screen_number++;
                if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
                {
                    control.Change_User_Turn();
                }
                current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
                break;
            }
        
        }
    }

}

void Scheme_Manager::Eliminate_The_Impossible_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    USER enemy_user;
    if(control.Return_User_Turn() == USER::USER1)
    {
        enemy_user = USER::USER2;
    }
    else
    {
        enemy_user = USER::USER1;
    }
    Element enemy_hand = control.Return_Hand_Elements_For_Render(enemy_user);
    std::vector<std::string> enemy_hand_for_radio_box = control.Return_Hand_As_String(enemy_user);
    int selected_card = 0;



    auto confirm_button = Button("CONFRIM", [&]{
        current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
        control.discard(selected_card, enemy_user);
        if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
        {
            control.Change_User_Turn();
        }
        screen.ExitLoopClosure()();
    });
    auto toggle_box = Toggle(&enemy_hand_for_radio_box, &selected_card);
    auto container = Container::Vertical({toggle_box, confirm_button});
    screen.Loop(Renderer(container, [&]{
        return vbox({
            vbox({
                text(" "),
                text("CHOOSEN CARD: ELIMINATE THE IMPOSSIBLE") | hcenter | bold | underlined | color(Color::NavajoWhite3),
                text(" "),
                enemy_hand | hcenter,
                text(" "),
                text("CHOOSE A CARD TO DISCARD FROM YOUR ENEMY"),
                container ->Render() | hcenter
            }) | center
        }) | border;
    }));

}


void Scheme_Manager::Master_Of_Disguise_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();
    USER enemy_user;
    if(control.Return_User_Turn() == USER::USER1)
    {
        enemy_user = USER::USER2;
    }
    else
    {
        enemy_user = USER::USER1;

    }
    auto confirm_button = Button("CONTINUE", [&]{
        current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
        control.change_fighter_health(Fighters_Names::SHERLOCK, -1);
        // move them heros
        int dracula_former_space_number = control.Return_Hero_Space_Number(Fighters_Names::DRACULA);
        control.Set_Fighter_Space_Number(Fighters_Names::DRACULA, control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
        control.Set_Fighter_Space_Number(Fighters_Names::SHERLOCK, dracula_former_space_number);
        game_map_ptr->Set_User_Occupying_Space(control.Return_User_Turn(), dracula_former_space_number);
        game_map_ptr->Set_User_Occupying_Space(enemy_user, control.Return_Hero_Space_Number(Fighters_Names::DRACULA));
        //updating print info for screen
        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::DRACULA), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::DRACULA)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::SHERLOCK)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::SHERLOCK)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
        if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
        {
            control.Change_User_Turn();
        }
        screen.ExitLoopClosure()();
    });


    screen.Loop(Renderer(confirm_button, [&]{
        return vbox({
            vbox({
                text(" "),
                text("CHOOSEN CARD: ELIMINATE THE IMPOSSIBLE") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                text(" "),
                control.map_and_user_info | hcenter,
                text(" "),
                text("SHERLOCK SWITCHES SPACE WITH THE OPPOSING HERO"),
                text(" "),
                text("OPPOSING HERO: -1HP"),
                text(" "),
                confirm_button ->Render() | size(WIDTH, EQUAL, 100) | hcenter
            }) | center
        }) | center;
    }));
}

void Scheme_Manager::Administer_Aid_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();
    std::set<int> unoccupied_spaces_adjacent_to_sherlock;
    game_map_ptr->Recursive_Path_Finder(unoccupied_spaces_adjacent_to_sherlock, control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), 1, control.Return_User_Turn());
    std::vector<std::string> options_for_radio_box;
    for(int space : unoccupied_spaces_adjacent_to_sherlock)
    {
        options_for_radio_box.push_back(std::to_string(space));
    }
    int selected_space = 0;
    auto radio_box = Radiobox(&options_for_radio_box, & selected_space);
    auto confirm_button = Button("CONFIRM", [&]{
        //draw one card for sherlock
        control.draw(control.Return_User_Turn());
        //add 1 hp to sherlcok
        control.change_fighter_health(Fighters_Names::SHERLOCK, 1);
        // move watson close to sherlock
        int former_watson_space_number = control.Return_Hero_Space_Number(Fighters_Names::WATSON);
        game_map_ptr->Change_Space_Occiupied_Status(former_watson_space_number);
        game_map_ptr->Change_Space_Occiupied_Status(std::stoi(options_for_radio_box[selected_space]));
        game_map_ptr->Set_User_Occupying_Space(USER::NONE, former_watson_space_number);
        game_map_ptr->Set_User_Occupying_Space(control.Return_User_Turn(), std::stoi(options_for_radio_box[selected_space]));
        control.Set_Fighter_Space_Number(Fighters_Names::WATSON, std::stoi(options_for_radio_box[selected_space]));

        Space_Row_And_Column_In_Array temp_struct_to_update_fighter_position_on_screen;
        control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::WATSON), temp_struct_to_update_fighter_position_on_screen);
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::WATSON)].Row_Index = temp_struct_to_update_fighter_position_on_screen.row_index;
        control.fighters_printing_info_array[static_cast<int>(Fighters_Names::WATSON)].Column_Index = temp_struct_to_update_fighter_position_on_screen.column_index;
        current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
        if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
        {
            control.Change_User_Turn();
        }
        screen.ExitLoopClosure()();
    });
    auto container = Container::Vertical({radio_box, confirm_button});
    screen.Loop(Renderer(container, [&]{
        return vbox({
            vbox({
                text(" "),
                text("CHOOSEN CARD: ADMINISTER AID") | hcenter | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3),
                text(" "),
                text("SHERLOCK: +1HP"),
                text(" "),
                text("DREW 1 CARD FOR SHERLOCK"),
                text(" "),
                control.map_and_user_info | hcenter,
                text(" "),
                text("CHOOSE A SPACE TO MOVE WATSON TO"),
                text(" "),
                container ->Render() | size(WIDTH, EQUAL, 100) | hcenter
            }) | center     
        }) | border;
    }));

    
}


void Scheme_Manager::Confirm_Suspicion_Screen(Controller& control)
{
    auto screen = ScreenInteractive::Fullscreen();
    int user_input_value = 0;
    USER attacker = control.Return_User_Turn();
    USER defender;
    if(attacker == USER::USER1)
    {
        defender = USER::USER2;
    }
    else
    {
        defender = USER::USER2;
    }

    std::vector<std::string> available_values = {"1", "2", "3", "4", "5", "6"};
    int selected_option = 0;
    int sub_screen_index = 0;
    bool effect_has_been_executed_exit_loop = false;

    


    while(!effect_has_been_executed_exit_loop)
    {
        switch (sub_screen_index)
        {
        case 0:
            {
                //get the guess 
                //if card exists go to screen1 and ask the defender to choose a card to discard
                //else go to screen 2 and see the defenders hand
                auto radio_box = Radiobox(&available_values, &selected_option);
                auto confirm_button = Button("CONFIRM", [&]{
                    //do the logic
                    user_input_value = std::stoi(available_values[selected_option]);
                    if(control.Does_Card_Exist_In_Hand_With_The_Corresponding_Value(defender, user_input_value))
                    {
                        sub_screen_index = 1;
                    }
                    else
                    {
                        sub_screen_index = 2;
                    }
                    screen.ExitLoopClosure()();
                });
                auto container = Container::Vertical({radio_box, confirm_button});

                screen.Loop(Renderer(container, [&]{
                    return vbox({
                        vbox({
                            text(" "),
                            text("SELECTED CARD: CONFIRM SUSPICION") | bold | underlined | size(WIDTH, EQUAL, 100) | color(Color::NavajoWhite3) | hcenter,
                            text(" "),
                            text("SPECIFY A VALUE: ") | bold,
                            text(" "),
                            container->Render() | hcenter | size(WIDTH, EQUAL, 100)
                        }) | center
                    }) | border;
                }));



                break;
            }
        case 1:
            {
                //ask the defender to discard a card    
                std::vector<int> qualified_cards_indices = control.Return_Card_Indexes_That_Match_The_Given_Value(defender, user_input_value);
                std::vector<Element> graphical_representation_of_defender_hand;
                std::vector<std::string> options_for_radio_box;
                int selected_option = 0;
                
                for(int index : qualified_cards_indices)
                {
                    graphical_representation_of_defender_hand.push_back(control.Return_A_Single_Card_Graphical_Representation(defender, index));
                    options_for_radio_box.push_back(control.Return_Card_Name(defender, index));
                }

                auto confirm_button = Button("CONFRIM", [&]{
                    control.change_fighter_health(Fighters_Names::DRACULA, -user_input_value);
                    control.discard(qualified_cards_indices[selected_option], defender);
                    sub_screen_index = 3;
                    screen.ExitLoopClosure()();
                });

                auto radio_box = Radiobox(&options_for_radio_box, &selected_option);
                auto container = Container::Vertical({radio_box, confirm_button});
                
                screen.Loop(Renderer(container, [&]{
                    return vbox({
                        vbox({
                            text(""),
                            text("SELECTED CARD: CONFIRM SUSPICION") | hcenter | bold | underlined | color(Color::NavajoWhite3),
                            text(""),
                            text("YOU ARE DEFENDING") | bold,
                            text(""),
                            text("CHOOSE A CARD TO DISCARD:") | bold,
                            text(""),
                            hbox({graphical_representation_of_defender_hand}) | hcenter,
                            text(""),
                            container -> Render() | hcenter


                        }) | center
                    }) | border;
                }));
                break;
            }
        
        case 2:
            {
                //show defenders hand    
                auto continue_button = Button("CONTINUE", [&]{
                    sub_screen_index = 3;
                    screen.ExitLoopClosure()();
                });
                screen.Loop(Renderer(continue_button, [&]{
                    return vbox({
                        vbox({
                            text(""),
                            text("SELECTED CARD: CONFRIM SUSPICION") | hcenter | underlined | color(Color::NavajoWhite3),
                            text(""),
                            text("TAKE A LOOK AT YOUR OPPONENTS HAND"),
                            text(""),
                            control.Return_Hand_Elements_For_Render(defender) | hcenter,
                            text(""),
                            continue_button -> Render() | hcenter

                        }) | center
                    }) | border;
                }));


                break;
            }
        
        case 3:
            //exit and go back main loop    
            effect_has_been_executed_exit_loop = true;
            current_screen = SCHEME_CARDS_SCREEN::EXIT_TO_MAIN_LOOP;
            if(control.Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
            {
                control.Change_User_Turn();
            }
            break;
        
        default:
            break;
        }
    }
}