#include "../headers/main_game_loop_sideckick_placement_manager.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace ftxui;

SideKick_Placement_Screen_Manager::SideKick_Placement_Screen_Manager(HERO_NAME younger_hero)
{
    if(younger_hero == HERO_NAME::DRACULA)
    {
        current_placement = SideKick_Placement_Screen::DRACULA_SIS1_SCREEN;
    }
    else if(younger_hero == HERO_NAME::SHERLOCK)
    {
        current_placement = SideKick_Placement_Screen::WATSON_SCREEN;
    }

    Young_User_SideKick_Spaces_Available = {"1", "2", "3", "4", "7", "8", "10", "11", "15"};
    Older_User_SideKick_Spaces_Available = {"17", "21", "23", "29"};
    
}

bool SideKick_Placement_Screen_Manager::Screen_Manager(Controller& control, Element map_and_user_info, Fighters_Print_Info* fighters_info_array)
{
    switch (current_placement)
    {
        case SideKick_Placement_Screen::WATSON_SCREEN:
            Dispaly_Watson_Screen(fighters_info_array[static_cast<int>(Fighters_Names::WATSON)], control, map_and_user_info);
            return true;
        
        case SideKick_Placement_Screen::DRACULA_SIS1_SCREEN:
            Display_Sis1_Screen(fighters_info_array[static_cast<int>(Fighters_Names::SIS1)], control, map_and_user_info);
            return true;
            
        case SideKick_Placement_Screen::DRACULA_SIS2_SCREEN:
            Display_Sis2_Screen(fighters_info_array[static_cast<int>(Fighters_Names::SIS2)], control, map_and_user_info);
            return true;
        
        case SideKick_Placement_Screen::DRACULA_SIS3_SCREEN:
            Display_Sis3_Screen(fighters_info_array[static_cast<int>(Fighters_Names::SIS3)], control, map_and_user_info);
            return true;
        
        case SideKick_Placement_Screen::CONTINUE_TO_THE_MAIN_MANAGER:
            return false;
    }
}



void SideKick_Placement_Screen_Manager::Dispaly_Watson_Screen(Fighters_Print_Info& watson_info_struct, Controller& control, ftxui::Element map_and_user_info)
{
    int selected_space = 0;
    

    Component SideKick_Space_Confirm_Button;
    Component Placement_Select_Handler;
    Component Available_Spaces_RadioBox;
    Element To_Be_Rendered;
    bool Is_Younger_User_Turn = (control.Return_Younger_User() == control.Return_User_Turn());

        if(Is_Younger_User_Turn)
        {
            Available_Spaces_RadioBox = Radiobox(&Young_User_SideKick_Spaces_Available, &selected_space);
            SideKick_Space_Confirm_Button = Button("Confirm", [&]{control.Change_User_Turn();
                current_placement = SideKick_Placement_Screen::DRACULA_SIS1_SCREEN;
                control.Set_Fighter_Space_Number(Fighters_Names::WATSON, std::stoi(Young_User_SideKick_Spaces_Available[selected_space]));
                watson_info_struct.Is_Placed_On_Map = true;
                control.screen.ExitLoopClosure()();
            });
            Placement_Select_Handler = Container::Vertical({
                Available_Spaces_RadioBox,
                SideKick_Space_Confirm_Button
            });
            

        }
        else
        {
            Available_Spaces_RadioBox = Radiobox(&Older_User_SideKick_Spaces_Available, &selected_space);
            SideKick_Space_Confirm_Button = Button("Confirm", [&]{control.Change_User_Turn();
                current_placement = SideKick_Placement_Screen::CONTINUE_TO_THE_MAIN_MANAGER;
                control.Set_Fighter_Space_Number(Fighters_Names::WATSON, std::stoi(Older_User_SideKick_Spaces_Available[selected_space]));
                watson_info_struct.Is_Placed_On_Map = true;
                control.screen.ExitLoopClosure()();
            });
             Placement_Select_Handler = Container::Vertical({
                Available_Spaces_RadioBox,
                SideKick_Space_Confirm_Button
            });
            
        }

        control.screen.Loop(Renderer(Placement_Select_Handler, [&]{
            if(Is_Younger_User_Turn)
            {
                To_Be_Rendered = vbox({
                hbox({text("User Turn: "), text(control.Return_Younger_User_Name())}) | hcenter,
                map_and_user_info | hcenter,
                text("Where do you want to place Dr.Watson? ") ,
                Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
                }) | center;
            }
            else
            {
                To_Be_Rendered = vbox({
                hbox({text("User Turn: "), text(control.Return_Older_User_Name())}) | hcenter,
                map_and_user_info | hcenter,
                text("Where do you want to place Dr.Watson? "),
                Placement_Select_Handler->Render()  | size(WIDTH, EQUAL, 100)
                }) | center;
            }
            return To_Be_Rendered;
    }));
    Space_Row_And_Column_In_Array Temp_Struct;
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::WATSON), Temp_Struct);
    watson_info_struct.Column_Index = Temp_Struct.column_index;
    watson_info_struct.Row_Index = Temp_Struct.row_index;
    watson_info_struct.Fighter_Name = 'W';


}

void SideKick_Placement_Screen_Manager::Display_Sis1_Screen(Fighters_Print_Info& sis1_info_struct, Controller& control, Element map_and_user_info) 
{
    int selected_space = 0;
    


    Component SideKick_Space_Confirm_Button;
    Component Placement_Select_Handler;
    Component Available_Spaces_RadioBox;
    Element To_Be_Rendered;
    bool Is_Younger_User_Turn = (control.Return_Younger_User() == control.Return_User_Turn());
    
    if(Is_Younger_User_Turn)
    {
        Available_Spaces_RadioBox = Radiobox(&Young_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::DRACULA_SIS2_SCREEN;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS1, std::stoi(Young_User_SideKick_Spaces_Available[selected_space]));
            sis1_info_struct.Is_Placed_On_Map = true;
            sis1_info_struct.Sis_Number = '1';
            Young_User_SideKick_Spaces_Available.erase(Young_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        

    }
    else
    {
        Available_Spaces_RadioBox = Radiobox(&Older_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::DRACULA_SIS2_SCREEN;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS1, std::stoi(Older_User_SideKick_Spaces_Available[selected_space]));
            sis1_info_struct.Is_Placed_On_Map = true;
            sis1_info_struct.Sis_Number = '1';
            Older_User_SideKick_Spaces_Available.erase(Older_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        
    }

    control.screen.Loop(Renderer(Placement_Select_Handler, [&]{
        if(Is_Younger_User_Turn)
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Younger_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister1? "),
            Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
            }) | center;
        }
        else
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Older_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister1? "),
            Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
            }) | center;
        }
        return To_Be_Rendered;
    }));

    Space_Row_And_Column_In_Array Temp_Struct;
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SIS1), Temp_Struct);

    sis1_info_struct.Column_Index = Temp_Struct.column_index;
    sis1_info_struct.Row_Index = Temp_Struct.row_index;
    sis1_info_struct.Fighter_Name = 's';

}


void SideKick_Placement_Screen_Manager::Display_Sis2_Screen(Fighters_Print_Info& sis2_struct_info, Controller& control, ftxui::Element map_and_user_info)
{
    int selected_space = 0;
    

    Component SideKick_Space_Confirm_Button;
    Component Placement_Select_Handler;
    Component Available_Spaces_RadioBox;
    Element To_Be_Rendered;
    bool Is_Younger_User_Turn = (control.Return_Younger_User() == control.Return_User_Turn());

    if(Is_Younger_User_Turn)
    {
        Available_Spaces_RadioBox = Radiobox(&Young_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::DRACULA_SIS3_SCREEN;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS2, std::stoi(Young_User_SideKick_Spaces_Available[selected_space]));
            sis2_struct_info.Is_Placed_On_Map = true;
            sis2_struct_info.Sis_Number = '2';
            Young_User_SideKick_Spaces_Available.erase(Young_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        

    }
    else
    {
        Available_Spaces_RadioBox = Radiobox(&Older_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::DRACULA_SIS3_SCREEN;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS2, std::stoi(Older_User_SideKick_Spaces_Available[selected_space]));
            sis2_struct_info.Is_Placed_On_Map = true;
            sis2_struct_info.Sis_Number = '2';
            Older_User_SideKick_Spaces_Available.erase(Older_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        
    }

    control.screen.Loop(Renderer(Placement_Select_Handler, [&]{
        if(Is_Younger_User_Turn)
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Younger_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister2? "),
            Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
            }) | center;
        }
        else
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Older_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister2? ") ,
            Placement_Select_Handler->Render()  | size(WIDTH, EQUAL, 100)
            }) | center;
        }
        return To_Be_Rendered;
    }));
    Space_Row_And_Column_In_Array Temp_Struct;
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SIS2), Temp_Struct);
    sis2_struct_info.Column_Index = Temp_Struct.column_index;
    sis2_struct_info.Row_Index = Temp_Struct.row_index;
    sis2_struct_info.Fighter_Name = 's';


}

void SideKick_Placement_Screen_Manager::Display_Sis3_Screen(Fighters_Print_Info& sis3_struct_info, Controller& control, ftxui::Element map_and_user_info)
{
    int selected_space = 0;
    
    
    Component SideKick_Space_Confirm_Button;
    Component Placement_Select_Handler;
    Component Available_Spaces_RadioBox;
    Element To_Be_Rendered;
    bool Is_Younger_User_Turn = (control.Return_Younger_User() == control.Return_User_Turn());

     
    if(Is_Younger_User_Turn)
    {
        Available_Spaces_RadioBox = Radiobox(&Young_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::WATSON_SCREEN;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS3, std::stoi(Young_User_SideKick_Spaces_Available[selected_space]));
            sis3_struct_info.Is_Placed_On_Map = true;
            sis3_struct_info.Sis_Number = '3';
            Young_User_SideKick_Spaces_Available.erase(Young_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        
    }
    else
    {
        Available_Spaces_RadioBox = Radiobox(&Older_User_SideKick_Spaces_Available, &selected_space);
        SideKick_Space_Confirm_Button = Button("Confirm", [&]{
            current_placement = SideKick_Placement_Screen::CONTINUE_TO_THE_MAIN_MANAGER;
            control.Set_Fighter_Space_Number(Fighters_Names::SIS3, std::stoi(Older_User_SideKick_Spaces_Available[selected_space]));
            sis3_struct_info.Is_Placed_On_Map = true;
            sis3_struct_info.Sis_Number = '3';
            Older_User_SideKick_Spaces_Available.erase(Older_User_SideKick_Spaces_Available.begin() + selected_space);
            control.screen.ExitLoopClosure()();
        });
        Placement_Select_Handler = Container::Vertical({
            Available_Spaces_RadioBox,
            SideKick_Space_Confirm_Button
        });
        
    }
    
    control.screen.Loop(Renderer(Placement_Select_Handler, [&]{
        
        if(Is_Younger_User_Turn)
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Younger_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister3? "),
            Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
            }) | center;
        }
        else
        {
            To_Be_Rendered = vbox({
            hbox({text("User Turn: "), text(control.Return_Older_User_Name())}) | hcenter,
            map_and_user_info | hcenter,
            text("Where do you want to place sister3? "),
            Placement_Select_Handler->Render() | size(WIDTH, EQUAL, 100)
            }) | center;
        }

        return To_Be_Rendered;
    }));
    Space_Row_And_Column_In_Array Temp_Struct;
    control.Convert_Space_Number_To_Row_And_Column_Index(control.Return_Hero_Space_Number(Fighters_Names::SIS3), Temp_Struct);
    control.Change_User_Turn();
    sis3_struct_info.Column_Index = Temp_Struct.column_index;
    sis3_struct_info.Row_Index = Temp_Struct.row_index;
    sis3_struct_info.Fighter_Name = 's';

}