#include "../headers/Ui.hpp"
#include "../headers/enums.hpp"

using namespace ftxui;
enum Screen_State {NAME_INPUT, AGE_INPUT, HERO_NAME_INPUT};
void User_Interface::Get_User_Input()
{
    auto screen = ScreenInteractive::TerminalOutput();
    std::string User1_Name = "";
    std::string User2_Name = "";
    std::string User1_Age;
    std::string User2_Age;
    HERO_NAME User1_Hero;
    HERO_NAME User2_Hero;

    static int turn = 1;
    static Screen_State state = NAME_INPUT;

    static bool Dracula = true;
    static bool Sherlock = false;
    auto User1_Name_Input = Input(&User1_Name, "You are user1 enter you name: ");
    auto User2_Name_Input = Input(&User1_Name, "You are user2 enter you name: ");
    auto User1_Age_Input = Input(&User1_Age, "Enter your age: ");
    auto User2_Age_Input = Input(&User2_Age, "Enter your age: ");
    auto Name_Confrim_Button = Button("Confirm", [&]{state = AGE_INPUT;});
    auto Age_Conrim_Button = Button("Confirm", [&]{state = HERO_NAME_INPUT;});
    auto Hero_Confirm_Button = Button("Confirm", [&]{
        if(turn = 1)
        {
            turn = 2;
            if(Dracula)
            {
                User1_Hero = HERO_NAME::DRACULA;
            }
            else
            {
                User1_Hero = HERO_NAME::SHERLOCK;
            }
            state = NAME_INPUT;
        }
        else
        {
            if(Dracula)
            {
                User2_Hero = HERO_NAME::DRACULA;
            }
            else
            {
                User2_Hero = HERO_NAME::SHERLOCK;
            }
            screen.ExitLoopClosure()();
        }
    });


    auto Dracula_Checkbox = Checkbox("Dracula", &Dracula);
    auto Sherlock_Checkbox = Checkbox("Sherlock", &Sherlock);
    auto checkbox_list = Container::Horizontal({Dracula_Checkbox, Sherlock_Checkbox});
    Component renderer;

    if(Dracula)
    {
        Sherlock = false;
    }
    else
    {
        Sherlock = true;
    }

    if(turn == 1)
    {
        switch (state)
        {
        case Screen_State::NAME_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    User1_Name_Input->Render(),
                    Age_Conrim_Button->Render()
                });
            });
            break;
        
        case Screen_State::AGE_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    User1_Age_Input->Render(),
                    Age_Conrim_Button->Render()
                });
            });
            break;
        
        case Screen_State::HERO_NAME_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    text("Choose your hero: "),
                    separator(),
                    checkbox_list->Render(),
                    Hero_Confirm_Button->Render()
                });
            });
            break;
        
        }
    }
    else
    {
        switch (state)
        {
        case Screen_State::NAME_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    User2_Name_Input->Render(),
                    Age_Conrim_Button->Render()
                });
            });
            break;
        
        case Screen_State::AGE_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    User2_Age_Input->Render(),
                    Age_Conrim_Button->Render()
                });
            });
            break;
        
        case Screen_State::HERO_NAME_INPUT:
            renderer = Renderer([&]{
                return vbox({
                    text("Choose your hero: "),
                    separator(),
                    checkbox_list->Render(),
                    Hero_Confirm_Button->Render()
                });
            });
            break;
        
        }
    }


}