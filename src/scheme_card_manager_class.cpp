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
        // Administer_Aid_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::ELIMINATE_THE_IMPOSSIBLE_SCREEN:
        // Eliminate_The_Impossible_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::MASTER_OF_DISGUISE_SCREEN:
        // Master_Of_Disguise_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::CONFIRM_SUSPICION_SCREEN:
        // Confirm_Suspicion_Screen(control);
        return true;
    
    case SCHEME_CARDS_SCREEN::MISTFORM_SCREEN:
        Mistform_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::BAPTISM_OF_BLOOD_SCREEN:
        // Baptism_Of_Blood_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::PREY_UPON_SCREEN:
        // Prey_Upon_Screen(control);
        return true;

    case SCHEME_CARDS_SCREEN::RAVENING_SEDUCTION_SCREEN:
        // Ravening_Seduction_Screen(control);
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
                text("CHOOSEN CARD: MISTFORM") | bold | underlined | size(WIDTH, EQUAL, 90) | color(Color::NavajoWhite3),
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
    
}