#include "../headers/Ui.hpp"
#include "../headers/Ui_GameLoop_Screen_Related_Function.hpp"
#include "../headers/controller.hpp"
#include "../headers/main_game_loop_sideckick_placement_manager.hpp"
#include "../headers/game_flow_ui_to_controller_interface.hpp"
#include "../headers/graph.hpp"
#include <map>
using namespace ftxui;


void User_Interface::Game_Loop_Screen(Controller& control)
{
    //initializing users hand
    control.Initialize_Users_hands();


    Graph* game_map_ptr = Graph::Get_Map_Graph_Pointer();
    control.Set_Younger_User_Variable_Value();
    SideKick_Placement_Screen_Manager side_kick_Screen_manager(control.Return_Younger_Hero_Name());

    User1_And_User2_Info user_info_struct;
    control.Fill_Users_Info_Struct(user_info_struct);
    Space_Row_And_Column_In_Array Temp_Struct_For_Updating_Hero_Position_On_Map;
    Fighters_Print_Info Map_Printing_Info[6];
    Fighter_Info Dracula_Info;
    Fighter_Info Sherlock_Info;
    Fighter_Info Watson_Info;
    Fighter_Info Dracula_Sis1_Info;
    Fighter_Info Dracula_Sis2_Info;
    Fighter_Info Dracula_Sis3_Info;

    //placing the heros on the map after we figured out
    //who is younger
    if(control.Return_Younger_Hero_Name() == HERO_NAME::DRACULA)
    {
        control.Set_Fighter_Space_Number(Fighters_Names::DRACULA, 9);
        game_map_ptr->Set_User_Occupying_Space(control.Return_Younger_User(), 9);
        control.Set_Fighter_Space_Number(Fighters_Names::SHERLOCK, 22);
        game_map_ptr->Set_User_Occupying_Space(control.Return_Older_User(), 22);

        
    }
    else if(control.Return_Younger_Hero_Name() == HERO_NAME::SHERLOCK)
    {
        control.Set_Fighter_Space_Number(Fighters_Names::DRACULA, 22);
        game_map_ptr->Set_User_Occupying_Space(control.Return_Older_User(), 22);
        control.Set_Fighter_Space_Number(Fighters_Names::SHERLOCK, 9);
        game_map_ptr->Set_User_Occupying_Space(control.Return_Younger_User(), 9);
    }
    game_map_ptr->Change_Space_Occiupied_Status(22);
    game_map_ptr->Change_Space_Occiupied_Status(9);

    //initializing the fighters position 
    //filling the temparory struct with dracula row and index valuse
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::DRACULA), Temp_Struct_For_Updating_Hero_Position_On_Map);
    Map_Printing_Info[static_cast<int>(Fighters_Names::DRACULA)].Is_Placed_On_Map = true;
    Map_Printing_Info[static_cast<int>(Fighters_Names::DRACULA)].Fighter_Name = 'D';
    Map_Printing_Info[static_cast<int>(Fighters_Names::DRACULA)].Row_Index = Temp_Struct_For_Updating_Hero_Position_On_Map.row_index;
    Map_Printing_Info[static_cast<int>(Fighters_Names::DRACULA)].Column_Index = Temp_Struct_For_Updating_Hero_Position_On_Map.column_index;
    
    //filling the temporary struct with sherlock row and index values
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK), Temp_Struct_For_Updating_Hero_Position_On_Map);
    Map_Printing_Info[static_cast<int>(Fighters_Names::SHERLOCK)].Is_Placed_On_Map = true;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SHERLOCK)].Fighter_Name = 'S';
    Map_Printing_Info[static_cast<int>(Fighters_Names::SHERLOCK)].Row_Index = Temp_Struct_For_Updating_Hero_Position_On_Map.row_index;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SHERLOCK)].Column_Index = Temp_Struct_For_Updating_Hero_Position_On_Map.column_index;

    Map_Printing_Info[static_cast<int>(Fighters_Names::WATSON)].Is_Placed_On_Map = false;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS1)].Is_Placed_On_Map = false;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS2)].Is_Placed_On_Map = false;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS3)].Is_Placed_On_Map = false;
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS1)].Sis_Number = '1';
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS2)].Sis_Number = '2';
    Map_Printing_Info[static_cast<int>(Fighters_Names::SIS3)].Sis_Number = '3';

        control.Fill_Fighter_Info_Struct(Fighters_Names::DRACULA, Dracula_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SHERLOCK, Sherlock_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::WATSON, Watson_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS1, Dracula_Sis1_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS2, Dracula_Sis2_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS3, Dracula_Sis3_Info);
        Element Player1_HeroInfo_Box;

        if(user_info_struct.User1_Hero_Type == HERO_NAME::DRACULA)
        {
            Player1_HeroInfo_Box = vbox({
                text("DRACULA"),
                hbox({text("Hp: "), text(std::to_string(Dracula_Info.Current_Hp)), text("/"), text(std::to_string(Dracula_Info.Initial_Hp))}),
                gauge((float)Dracula_Info.Current_Hp/ Dracula_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Dracula_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Dracula_Info.Range))}),
                text(user_info_struct.User1_Name)
            }) | border;
        }
        else if(user_info_struct.User1_Hero_Type == HERO_NAME::SHERLOCK)
        {
            Player1_HeroInfo_Box = vbox({
                text("SHERLOCK"),
                hbox({text("Hp: "), text(std::to_string(Sherlock_Info.Current_Hp)), text("/"), text(std::to_string(Sherlock_Info.Initial_Hp))}),
                gauge((float)Sherlock_Info.Current_Hp/ Sherlock_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Sherlock_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Sherlock_Info.Range))}),
                text(user_info_struct.User1_Name)
                
            }) | border;
        }
        Element Player2_HeroInfo_Box;
    
        if(user_info_struct.User2_Hero_Type == HERO_NAME::SHERLOCK)
        {
            Player2_HeroInfo_Box = vbox({
                text("SHERLOCK"),
                hbox({text("Hp: "), text(std::to_string(Sherlock_Info.Current_Hp)), text("/"), text(std::to_string(Sherlock_Info.Initial_Hp))}),
                gauge((float)Sherlock_Info.Current_Hp/ Sherlock_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Sherlock_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Sherlock_Info.Range))}),
                text(user_info_struct.User2_Name)
            }) | border;
        }
        else if(user_info_struct.User2_Hero_Type == HERO_NAME::DRACULA)
        {
            Player2_HeroInfo_Box = vbox({
                text("DRACULA"),
                hbox({text("Hp: "), text(std::to_string(Dracula_Info.Current_Hp)), text("/"), text(std::to_string(Dracula_Info.Initial_Hp))}),
                gauge((float)Dracula_Info.Current_Hp/ Dracula_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Dracula_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Dracula_Info.Range))}),
                text(user_info_struct.User2_Name)
            }) | border;
    
        }
        auto Location_Info = vbox({
            text("Current Space Number: "), // fill the number
            text("Connected To: ") //fill the numbers
        }) | border;


    //placing sidekicks on the map 
    while(true)
    {
    
        auto Terminal_Out_Map = vbox
        ({
            paragraphAlignCenter(Return_Map_To_Be_Rendered(6, Map_Printing_Info))
        }) | border;
        
        Element Users_Info_And_Map = vbox({
            hbox({
                Player1_HeroInfo_Box,
                Terminal_Out_Map,
                Player2_HeroInfo_Box,
            }),
        });
        
        if(!side_kick_Screen_manager.Screen_Manager(control, Users_Info_And_Map, Map_Printing_Info))
        {
            break;
        }
    }

    game_map_ptr->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(Fighters_Names::SIS1));
    game_map_ptr->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(Fighters_Names::SIS2));
    game_map_ptr->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(Fighters_Names::SIS3));
    game_map_ptr->Change_Space_Occiupied_Status(control.Return_Hero_Space_Number(Fighters_Names::WATSON));

    if(control.Return_User1_Hero_Name() == HERO_NAME::DRACULA)
    {
        game_map_ptr->Set_User_Occupying_Space(USER::USER1, control.Return_Hero_Space_Number(Fighters_Names::SIS1));
        game_map_ptr->Set_User_Occupying_Space(USER::USER1, control.Return_Hero_Space_Number(Fighters_Names::SIS2));
        game_map_ptr->Set_User_Occupying_Space(USER::USER1, control.Return_Hero_Space_Number(Fighters_Names::SIS3));
        game_map_ptr->Set_User_Occupying_Space(USER::USER2, control.Return_Hero_Space_Number(Fighters_Names::WATSON));
    }
    else
    {
        game_map_ptr->Set_User_Occupying_Space(USER::USER2, control.Return_Hero_Space_Number(Fighters_Names::SIS1));
        game_map_ptr->Set_User_Occupying_Space(USER::USER2, control.Return_Hero_Space_Number(Fighters_Names::SIS2));
        game_map_ptr->Set_User_Occupying_Space(USER::USER2, control.Return_Hero_Space_Number(Fighters_Names::SIS3));
        game_map_ptr->Set_User_Occupying_Space(USER::USER1, control.Return_Hero_Space_Number(Fighters_Names::WATSON));
    }
    

    
    //the main gameloop
    User_Choice_Manager user_choice_manager;
    while(true)
    {
        //updating fighter info after each action
        control.Fill_Fighter_Info_Struct(Fighters_Names::DRACULA, Dracula_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SHERLOCK, Sherlock_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::WATSON, Watson_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS1, Dracula_Sis1_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS2, Dracula_Sis2_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS3, Dracula_Sis3_Info);

        //recreating each element because information can change 
        auto Terminal_Out_Map = vbox
        ({
            paragraphAlignCenter(Return_Map_To_Be_Rendered(6, Map_Printing_Info))
        }) | border;
        
        Element Users_Info_And_Map = vbox({
            hbox({
                Player1_HeroInfo_Box,
                Terminal_Out_Map,
                Player2_HeroInfo_Box,
            }),
        });

        if(!user_choice_manager.Screen_Manager(control.Return_User_Turn(), control, Users_Info_And_Map, Map_Printing_Info, 6))
        {
            break;
        }
    }


    Current_Screen_State = SCREEN_STATE::PROGRAM_SHOULD_TEMINATE;
    std::cout << Return_Map_To_Be_Rendered(6, Map_Printing_Info);
}