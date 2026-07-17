#include "../headers/Ui.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>
#include <string>
enum class MENU_SUB_SCREENS{SETTING, HELP, NONE};


using namespace::ftxui;

void User_Interface::Starting_Menu_Screen(Controller& control)
{
    std::vector<std::string> Menu_Options {"START GAME", "HELP", "EXIT"};
    int Selected_Menu_Option = 0;
    MENU_SUB_SCREENS Selected_Sub_Screen = MENU_SUB_SCREENS::NONE;
    std::string Game_Titile = R"(
        _   _ _   _ ___  ___  ___ _____ _____  _   _  ___________ 
        | | | | \ | ||  \/  | / _ \_   _/  __ \| | | ||  ___|  _  \
        | | | |  \| || .  . |/ /_\ \| | | /  \/| |_| || |__ | | | |
        | | | | . ` || |\/| ||  _  || | | |    |  _  ||  __|| | | |
        | |_| | |\  || |  | || | | || | | \__/\| | | || |___| |/ / 
        \___/\_| \_/\_|  |_/\_| |_/\_/  \____/\_| |_/\____/|___/  
        )";
        
        
        
        
        
        
        auto renderer = Renderer([&]{
            
            std::vector<Element> Menu_Elements;
            Element Menu_To_Be_Rendered;
            for(int i = 0 ; i < Menu_Options.size() ; i++)
            {
                if(i == Selected_Menu_Option)
                {
                    Menu_Elements.push_back(text("➢ " + Menu_Options[i]) | color(Color::NavajoWhite3));
                    
            }
            else
            {
                Menu_Elements.push_back(text("  " + Menu_Options[i]) | color(Color::GrayDark));
                
            }
        }
        
        Menu_To_Be_Rendered = vbox({
            Menu_Elements[0] | center,
            Menu_Elements[1] | center,
            Menu_Elements[2] | center,
    
        }) | center;

        return
        vbox
        ({    
            paragraphAlignCenter(Game_Titile) | hcenter | color(Color::NavajoWhite3),
            separator(),
            vbox
            ({
                Menu_To_Be_Rendered
            })| border

        });  
    });

    auto Input_Interpreter  = CatchEvent(renderer, [&](Event event){
        if(event == Event::ArrowDown)
        {
            Selected_Menu_Option++;
            if(Selected_Menu_Option > 2)
            {
                Selected_Menu_Option = 0;
            }
            return true;
        }
        else if(event == Event::ArrowUp)
        {
            Selected_Menu_Option--;
            if(Selected_Menu_Option < 0)
            {
                Selected_Menu_Option = 2;
            }
            return true;

        }
        else if(event == Event::Return)
        {
            switch (Selected_Menu_Option)
            {
            case 0:
                Current_Screen_State = SCREEN_STATE::PROMPT_INPUT;
                control.screen.ExitLoopClosure()();
                return true;

            case 1:
                Selected_Sub_Screen = MENU_SUB_SCREENS::HELP;
                return true;
                
            case 2:
                Current_Screen_State = SCREEN_STATE::PROGRAM_SHOULD_TEMINATE;
                control.screen.ExitLoopClosure()();
                return true;
            }
            return false;
        }
        return false;
    });

    control.screen.Loop(Input_Interpreter);
}