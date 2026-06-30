#include "../headers/Ui.hpp"
#include "../headers/Ui_GameLoop_Screen_Related_Function.hpp"

#include <map>


using namespace ftxui;


void User_Interface::Game_Loop_Screen()
{
    auto screen = ScreenInteractive::TerminalOutput();

    auto Player1_HeroInfo_Box = vbox({
       //text(hero name)
       //text(hero hp / hero initial hp)
       //gauge(hero_current_hp / hero initial hp)
       //text(hero range)
       //text(hero move value)
    }) | border;
    
    auto Player2_HeroInfo_Box = vbox({
       //text(hero name)
       //text(hero hp / hero initial hp)
       //gauge(hero_current_hp / hero initial hp)
       //text(hero range)
       //text(hero move value)
    }) | border;

    auto Control_Prompt = vbox({
        text("PRESS C") | bold | underlined,
        text("open control menu")
    }) | border;

    auto Location_Info = vbox({
        text("Current Space Number: "), // fill the number
        text("Connected To: ") //fill the numbers
    }) | border;

    
    

}