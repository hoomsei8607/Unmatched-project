#include "../headers/Ui.hpp"
#include "../headers/Ui_GameLoop_Screen_Related_Function.hpp"
#include "../headers/controller.hpp"
#include <map>
using namespace ftxui;


void User_Interface::Game_Loop_Screen(Controller& control)
{
    

    User1_And_User2_Info user_info_struct;
    control.Fill_Users_Info_Struct(user_info_struct);
    Fighter_Info Dracula_Info;
    Fighter_Info Sherlock_Info;
    Fighter_Info Watson_Info;
    Fighter_Info Dracula_Sis1;
    Fighter_Info Dracula_Sis2;
    Fighter_Info Dracula_Sis3;

    
    
    auto render = Renderer([&]{
        control.Fill_Fighter_Info_Struct(Fighters_Names::DRACULA, Dracula_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SHERLOCK, Sherlock_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::WATSON, Watson_Info);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS1, Dracula_Sis1);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS2, Dracula_Sis2);
        control.Fill_Fighter_Info_Struct(Fighters_Names::SIS3, Dracula_Sis3);

        Element Player1_HeroInfo_Box;
        if(user_info_struct.User1_Hero_Type == HERO_NAME::DRACULA)
        {
            Player1_HeroInfo_Box = vbox({
                text(user_info_struct.User1_Hero_Name),
                hbox({text("Hp: "), text(std::to_string(Dracula_Info.Current_Hp)), text("/"), text(std::to_string(Dracula_Info.Initial_Hp))}),
                gauge((float)Dracula_Info.Current_Hp/ Dracula_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Dracula_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Dracula_Info.Range))}),
                
            }) | border;
        }
        else if(user_info_struct.User1_Hero_Type == HERO_NAME::SHERLOCK)
        {
            Player1_HeroInfo_Box = vbox({
                text(user_info_struct.User1_Hero_Name),
                hbox({text("Hp: "), text(std::to_string(Sherlock_Info.Current_Hp)), text("/"), text(std::to_string(Sherlock_Info.Initial_Hp))}),
                gauge((float)Sherlock_Info.Current_Hp/ Sherlock_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Sherlock_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Sherlock_Info.Range))}),
                
            }) | border;
        }
        
        Element Player2_HeroInfo_Box;

        if(user_info_struct.User2_Hero_Type == HERO_NAME::SHERLOCK)
        {
            Player2_HeroInfo_Box = vbox({
                text(user_info_struct.User2_Hero_Name),
                hbox({text("Hp: "), text(std::to_string(Sherlock_Info.Current_Hp)), text("/"), text(std::to_string(Sherlock_Info.Initial_Hp))}),
                gauge((float)Sherlock_Info.Current_Hp/ Sherlock_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Sherlock_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Sherlock_Info.Range))}),
            }) | border;
        }
        else if(user_info_struct.User2_Hero_Type == HERO_NAME::DRACULA)
        {
            Player2_HeroInfo_Box = vbox({
                text(user_info_struct.User2_Hero_Name),
                hbox({text("Hp: "), text(std::to_string(Dracula_Info.Current_Hp)), text("/"), text(std::to_string(Dracula_Info.Initial_Hp))}),
                gauge((float)Dracula_Info.Current_Hp/ Dracula_Info.Initial_Hp),
                hbox({text("Move Value: "), text(std::to_string(Dracula_Info.Move_Value))}),
                hbox({text("Range: "), text(std::to_string(Dracula_Info.Range))}),
            }) | border;

        }
    
        auto Control_Prompt = vbox({
            text("PRESS C") | bold ,
            text("open control menu")
        }) | border;
    
        auto Location_Info = vbox({
            text("Current Space Number: "), // fill the number
            text("Connected To: ") //fill the numbers
        }) | border;
    
        auto Terminal_Out_Map = vbox
        ({
            paragraphAlignCenter(Return_Map_To_Be_Rendered())
        }) | border;
    

        return vbox({
            hbox({
                Player1_HeroInfo_Box,
                Terminal_Out_Map,
                Player2_HeroInfo_Box,
            }),
            vbox({}) | border,
            Control_Prompt
        });
    });

    auto screen = ScreenInteractive::Fullscreen();
    auto to_be_looped_on = CatchEvent(render, [&](Event event){
        if(event == Event::Character('q'))
        {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
        
    });
    screen.Loop(to_be_looped_on);
    Current_Screen_State = SCREEN_STATE::PROGRAM_SHOULD_TEMINATE;
    
}