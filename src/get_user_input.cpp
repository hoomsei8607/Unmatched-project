#include "../headers/Ui.hpp"
#include "../headers/enums.hpp"

using namespace ftxui;
enum Screen_State {USER1_NAME_INPUT, USER2_NAME_INPUT, USER1_AGE_INPUT, USER2_AGE_INPUT, HERO_NAME_INPUT};

User1_And_User2_Info User_Interface::Get_User_Input()
{
    auto screen = ScreenInteractive::Fullscreen();
    std::string User1_Name = "";
    std::string User2_Name = "";
    std::string User1_Age;
    std::string User2_Age;
    HERO_NAME User1_Hero;
    HERO_NAME User2_Hero;

    static int turn = 1;
    static Screen_State state = USER1_NAME_INPUT;
    int current_page = USER1_NAME_INPUT;

    auto User1_Name_Input = Input(&User1_Name, "You are user1 enter you name: ");
    auto User2_Name_Input = Input(&User2_Name, "You are user2 enter you name: ");
    auto User1_Age_Input = Input(&User1_Age, "Enter your age: ");
    auto User2_Age_Input = Input(&User2_Age, "Enter your age: ");
    auto User1_Name_Confirm_Button = Button("Confirm", [&]{state = USER1_AGE_INPUT; current_page = USER1_AGE_INPUT;});
    auto User2_Name_Confirm_Button = Button("Confirm", [&]{state = USER2_AGE_INPUT; current_page = USER2_AGE_INPUT;});
    auto User1_Age_Confrim_Button = Button("Confirm", [&]{state = HERO_NAME_INPUT; current_page = HERO_NAME_INPUT;});
    auto User2_Age_Confrim_Button = Button("Confirm", [&]{state = HERO_NAME_INPUT; current_page = HERO_NAME_INPUT;});
    std::vector<std::string> Hero_Options {"DRACULA", "SHERLOCK"};
    int selected = 0;
    auto hero_select_radio_box = Radiobox(&Hero_Options, &selected);
    auto Hero_Confirm_Button = Button("Confirm", [&]{
        if(turn == 1)
        {
            turn = 2;
            if(selected == 0)
            {
                User1_Hero = HERO_NAME::DRACULA;
            }
            else
            {
                User1_Hero = HERO_NAME::SHERLOCK;
            }
            state = USER2_NAME_INPUT;
            current_page = USER2_NAME_INPUT;
        }
        else
        {
            if(selected == 0)
            {
                User2_Hero = HERO_NAME::DRACULA;
            }
            else
            {
                User2_Hero = HERO_NAME::SHERLOCK;
            }
            Current_Screen_State = SCREEN_STATE::GAME_LOOP;
            screen.ExitLoopClosure()();
        }
    });
    
    auto Hero_Name_Event_Handler = Container::Vertical({
        hero_select_radio_box,
        Hero_Confirm_Button 
    });

    auto User1_Name_Event_handler = Container::Vertical({
        User1_Name_Input,
        User1_Name_Confirm_Button
    });

    auto User2_Name_Event_handler = Container::Vertical({
        User2_Name_Input,
        User2_Name_Confirm_Button
    });
    auto User1_Age_Event_Handler = Container::Vertical({
        User1_Age_Input,
        User1_Age_Confrim_Button
    });
    auto User2_Age_Event_Handler = Container::Vertical({
        User2_Age_Input,
        User2_Age_Confrim_Button
    });


    auto Event_Handler_Container = Container::Tab({
        User1_Name_Event_handler,
        User2_Name_Event_handler,
        User1_Age_Event_Handler,
        User2_Age_Event_Handler,
        Hero_Name_Event_Handler
    }, &current_page);

    auto renderer = Renderer(Event_Handler_Container, [&]{
        if(turn == 1)
        {
            switch (state)
            {
            case Screen_State::USER1_NAME_INPUT:
                return vbox({
                    User1_Name_Input->Render(),
                    User1_Name_Confirm_Button->Render(),
                });
            
            case Screen_State::USER1_AGE_INPUT:
                    return vbox({
                        User1_Age_Input->Render(),
                        User1_Age_Confrim_Button->Render()
                    });
            
            case Screen_State::HERO_NAME_INPUT:
                    return vbox({
                        text("Choose your hero: "),
                        separator(),
                        Hero_Name_Event_Handler->Render(),
                    });
            }
        }
        else
        {
            switch (state)
            {
            case Screen_State::USER2_NAME_INPUT:
                return vbox({
                    User2_Name_Input->Render(),
                    User2_Name_Confirm_Button->Render(),
                });
            
            case Screen_State::USER2_AGE_INPUT:
                    return vbox({
                        User2_Age_Input->Render(),
                        User2_Age_Confrim_Button->Render()
                    });
            
            // case Screen_State::HERO_NAME_INPUT:
            //         return vbox({
            //             text("Choose your hero: "),
            //             separator(),
            //             Hero_Name_Event_Handler->Render(),
            //         });
            }
        }
    });
    

    screen.Loop(renderer);
    //assign to the users all the info you have got
    if(User1_Hero == HERO_NAME::DRACULA)
    {
        User2_Hero = HERO_NAME::SHERLOCK;
    }
    else
    {
        User2_Hero = HERO_NAME::DRACULA;
    }
    User1_And_User2_Info info_struct;
    info_struct.User1_Age = std::stoi(User1_Age);
    info_struct.User1_Name = User1_Name;
    info_struct.User1_Hero_Name = User1_Hero;
    info_struct.User2_Age = std::stoi(User2_Age);
    info_struct.User2_Name = User2_Name;
    info_struct.User2_Hero_Name = User2_Hero;
    return info_struct;
}