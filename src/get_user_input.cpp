#include "../headers/Ui.hpp"
#include "../headers/enums.hpp"
#include "../headers/Ui.hpp"
#include <cctype>

using namespace ftxui;
enum Screen_State {USER1_NAME_INPUT, USER2_NAME_INPUT, USER1_AGE_INPUT, USER2_AGE_INPUT, HERO_NAME_INPUT, USER_INDEPENDENT_WRONG_AGE_INPUT};

bool Is_String_All_Numbers(const std::string& input);


User1_And_User2_Info User_Interface::Get_User_Input(Controller& control)
{
    USER current_user_giving_inputs = USER::USER1;
    std::string User1_Name = "";
    std::string User2_Name = "";
    std::string User1_Age = "";
    std::string User2_Age = "";
    HERO_NAME User1_Hero;
    HERO_NAME User2_Hero;

    int turn = 1;
    Screen_State state = USER1_NAME_INPUT;
    int current_page = USER1_NAME_INPUT;

    auto User1_Name_Input = Input(&User1_Name, "You are user1 enter you name: ");
    auto User2_Name_Input = Input(&User2_Name, "You are user2 enter you name: ");
    auto User1_Age_Input = Input(&User1_Age, "You are User1 enter your age: ");
    auto User2_Age_Input = Input(&User2_Age, "You are User2 enter your age: ");
    auto User1_Name_Confirm_Button = Button("Confirm", [&]{state = USER1_AGE_INPUT; current_page = USER1_AGE_INPUT;});
    auto User2_Name_Confirm_Button = Button("Confirm", [&]{state = USER2_AGE_INPUT; current_page = USER2_AGE_INPUT;});
    
    auto User1_Age_Confrim_Button = Button("Confirm", [&]{
        if(Is_String_All_Numbers(User1_Age) && !User1_Age.empty())
        {
            state = USER2_NAME_INPUT; current_page = USER2_NAME_INPUT;
            current_user_giving_inputs = USER::USER2;
            
        }
        else
        {
            state = USER_INDEPENDENT_WRONG_AGE_INPUT; current_page = USER_INDEPENDENT_WRONG_AGE_INPUT;
        }
    });
   
    auto User2_Age_Confrim_Button = Button("Confirm", [&]{
        if(Is_String_All_Numbers(User2_Age) && !User2_Age.empty())
        {
            state = HERO_NAME_INPUT; 
            current_page = HERO_NAME_INPUT;
             if(std::stoi(User1_Age) > std::stoi(User2_Age))
            {
                turn = 2;
                control.Set_User_Turn(USER::USER2);
                control.Set_Current_User_Action(USER_ACTION::USER2_ACTION1);
            }
            else
            {
                turn = 1;
                control.Set_User_Turn(USER::USER1);
                control.Set_Current_User_Action(USER_ACTION::USER1_ACTION1);
            }
        }
        else
        {
            state = USER_INDEPENDENT_WRONG_AGE_INPUT;
            current_page = USER_INDEPENDENT_WRONG_AGE_INPUT;
        }
    });
   
    std::vector<std::string> Hero_Options {"DRACULA", "SHERLOCK"};
    int selected = 0;
    auto hero_select_radio_box = Radiobox(&Hero_Options, &selected);
    auto Hero_Confirm_Button = Button("Confirm", [&]{
       
        if(turn == 1)
        {
            if(selected == 0)
            {
                User1_Hero = HERO_NAME::DRACULA;
                User2_Hero = HERO_NAME::SHERLOCK;
            }
            else
            {
                User1_Hero = HERO_NAME::SHERLOCK;
                User2_Hero = HERO_NAME::DRACULA;
            }
        }
        else
        {
            if(selected == 0)
            {
                User2_Hero = HERO_NAME::DRACULA;
                User1_Hero = HERO_NAME::SHERLOCK;
            }
            else
            {
                User2_Hero = HERO_NAME::SHERLOCK;
                User1_Hero = HERO_NAME::DRACULA;
            }
            
        }
        Current_Screen_State = SCREEN_STATE::GAME_LOOP;
        control.screen.ExitLoopClosure()();
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

    std::string Wrong_Age_Input_Replacement = "";
    auto Replace_Wrong_Age_Input = Input(&Wrong_Age_Input_Replacement, "WRONG AGE! ENTER NUMBERS ONLY");
    auto Replace_Wrong_Age_Input_Confirm_Button = Button("CONFIRM", [&]{
        if(!Is_String_All_Numbers(Wrong_Age_Input_Replacement) || Wrong_Age_Input_Replacement.empty())
        {
            Wrong_Age_Input_Replacement.erase();
            return;
        }

        if(current_user_giving_inputs == USER::USER1)
        {
            User1_Age = Wrong_Age_Input_Replacement;
            Wrong_Age_Input_Replacement.erase();
            current_user_giving_inputs = USER::USER2;
            current_page = Screen_State::USER2_NAME_INPUT;
            state = Screen_State::USER2_NAME_INPUT;
        }
        else
        {
            User2_Age = Wrong_Age_Input_Replacement;
            current_page = Screen_State::HERO_NAME_INPUT;
            state = Screen_State::HERO_NAME_INPUT;
        }
    });
    auto Wrong_Age_Input_Event_Handler = Container::Vertical({
        Replace_Wrong_Age_Input,
        Replace_Wrong_Age_Input_Confirm_Button
    });

    auto Event_Handler_Container = Container::Tab({
        User1_Name_Event_handler,
        User2_Name_Event_handler,
        User1_Age_Event_Handler,
        User2_Age_Event_Handler,
        Hero_Name_Event_Handler,
        Wrong_Age_Input_Event_Handler
    }, &current_page);

    auto renderer = Renderer(Event_Handler_Container, [&]{
        if(turn == 1)
        {
            switch (state)
            {
            case Screen_State::USER1_NAME_INPUT:
                return vbox({
                    User1_Name_Input->Render() | size(WIDTH, EQUAL, 100),
                    User1_Name_Confirm_Button->Render() | size(WIDTH, EQUAL, 100),
                }) | center;
            
            case Screen_State::USER1_AGE_INPUT:
                    return vbox({
                        User1_Age_Input->Render() | size(WIDTH, EQUAL, 100),
                        User1_Age_Confrim_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            case Screen_State::USER_INDEPENDENT_WRONG_AGE_INPUT:
                    return vbox({
                        Replace_Wrong_Age_Input -> Render() | size(WIDTH, EQUAL, 100),
                        Replace_Wrong_Age_Input_Confirm_Button -> Render() | size(WIDTH, EQUAL, 100)
                    }) | center;
                    
                    

            case Screen_State::USER2_AGE_INPUT:
                    return vbox({
                        User2_Age_Input->Render() | size(WIDTH, EQUAL, 100),
                        User2_Age_Confrim_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            case Screen_State::USER2_NAME_INPUT:
                    return vbox({
                        User2_Name_Input->Render() | size(WIDTH, EQUAL, 100),
                        User2_Name_Confirm_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            
            case Screen_State::HERO_NAME_INPUT:
                    return vbox({
                        hbox({text("You are User1 ( "), text(User1_Name), text(" ) Choose your hero: ")}),
                        separator(),
                        Hero_Name_Event_Handler->Render() | size(WIDTH, EQUAL, 100),
                    }) | center;
            }
            return vbox({});
        }
        else
        {
            switch (state)
            {
            case Screen_State::USER1_NAME_INPUT:
                return vbox({
                    User1_Name_Input->Render() | size(WIDTH, EQUAL, 100),
                    User1_Name_Confirm_Button->Render() | size(WIDTH, EQUAL, 100),
                }) | center;
            
            case Screen_State::USER1_AGE_INPUT:
                    return vbox({
                        User1_Age_Input->Render() | size(WIDTH, EQUAL, 100),
                        User1_Age_Confrim_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            case Screen_State::USER2_AGE_INPUT:
                    return vbox({
                        User2_Age_Input->Render() | size(WIDTH, EQUAL, 100),
                        User2_Age_Confrim_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            case Screen_State::USER2_NAME_INPUT:
                    return vbox({
                        User2_Name_Input->Render() | size(WIDTH, EQUAL, 100),
                        User2_Name_Confirm_Button->Render() | size(WIDTH, EQUAL, 100)
                    }) | center;

            
            case Screen_State::HERO_NAME_INPUT:
                    return vbox({
                        hbox({text("You are User2 ( "), text(User2_Name), text(" ) Choose your hero: ")}),
                        separator() | size(WIDTH, EQUAL, 100) ,
                        Hero_Name_Event_Handler->Render() | size(WIDTH, EQUAL, 100),
                    }) | center;
            }
            return vbox({});
        }
    });
    

    control.screen.Loop(renderer);

    std::string User1_Hero_Name_String = ""; 
    std::string User2_Hero_Name_String = ""; 

    
    //assign to the users all the info you have got
    if(User1_Hero == HERO_NAME::DRACULA)
    {
        User2_Hero = HERO_NAME::SHERLOCK;
        User1_Hero_Name_String = "DRACULA";
        User2_Hero_Name_String = "SHERLOCK";
    }
    else
    {
        User2_Hero = HERO_NAME::DRACULA;
        User1_Hero_Name_String = "SHERLOCK";
        User2_Hero_Name_String = "DRACULA";
    }

    User1_And_User2_Info info_struct;
    info_struct.User1_Age = User1_Age;
    info_struct.User2_Age = User2_Age;
    info_struct.User1_Name = User1_Name;
    info_struct.User2_Name = User2_Name;
    info_struct.User1_Hero_Type = User1_Hero;
    info_struct.User2_Hero_Type = User2_Hero;
    info_struct.User1_Hero_Name = User1_Hero_Name_String;
    info_struct.User2_Hero_Name = User2_Hero_Name_String;
    


    return info_struct;
}

bool Is_String_All_Numbers(const std::string& input)
{
    for(int i = 0 ; i < input.size() ; i++)
    {
        if(!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}
