#ifndef RAYLIB_UI_HPP
#define RAYLIB_UI_HPP

#include <raylib.h>
#include <string>

struct PlayerInfo
{
    std::string name;
    int age;
    int hero;
};

class RaylibUI
{

public:

    enum class Screen
    {
        MAIN_MENU,

        USER1_NAME,
        USER1_AGE,

        USER2_NAME,
        USER2_AGE,

        USER1_HERO_SELECT,
        USER2_HERO_SELECT,

        GAME,

        EXIT
    };


private:

    PlayerInfo player1;
    PlayerInfo player2;
    
    Screen current_screen;

    bool running;
    int selected_hero;
    int user_number;

    std::string current_input;


    void Update();

    void Draw();


    void DrawMainMenu();

    void DrawTextInputScreen();


    void HandleTextInput();



public:

    RaylibUI();

    void Run();
    void DrawHeroSelect();

};


#endif