#ifndef RAYLIB_UI_HPP
#define RAYLIB_UI_HPP


#include "../controller.hpp"
#include <raylib.h>
#include <string>
#include <set>


struct PlayerInfo
{
    std::string name;

    int age;

    int hero;
};

struct SpacePosition
{
    float x;
    float y;
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

        HELP,

        EXIT
    };


private:

    Screen current_screen;
    Texture2D draculaResized;
    Texture2D sherlockResized;
    Texture2D invisibleResized;

    Texture2D mapImage;

    bool running;


    std::string current_input;



    PlayerInfo player1;

    PlayerInfo player2;

    SpacePosition space_positions[33];
    Controller* controller;
    bool hero_taken[3];
    // hero_taken[0] = Dracula
    // hero_taken[1] = SHERLOCK
    // hero_taken[2] = INVISIBLE MAN

    USER hero_selection_user;
    bool first_hero_selected;

    Texture2D dracula_image;

    Texture2D sister1_image;
    Texture2D sister2_image;
    Texture2D sister3_image;

    Texture2D sherlock_image;
    Texture2D watson_image;

    Texture2D invisible_man_image;

    const int MAP_OFFSET_X = 300;
    const int MAP_OFFSET_Y = 150;

    USER placement_user;
    bool sidekick_placement_active;
    int current_sidekick_index;
    std::vector<int> available_placement_spaces;
    std::vector<Fighters_Names> sidekicks_to_place;

    bool maneuver_mode = false;
    Fighters_Names selected_fighter = Fighters_Names::NONE;
    int selected_fighter_space = -1;
    std::set<int> maneuver_available_spaces;
    int selected_maneuver_space = -1;
    Rectangle maneuver_button;

    void Start_SideKick_Placement();
    void Handle_SideKick_Placement();
    void Draw_Placement_Highlights();
    void Finish_SideKick_Placement();
    void DrawManeuverButton();
    void DrawManeuverAvailableSpaces();
    void Handle_Fighter_Selection();
    void Handle_Maneuver();
    int GetClickedManeuverSpace();

    bool IsManeuverButtonClicked();



    void Update();

    void Draw();

    
    void DrawMainMenu();
    void HandleMainMenu();
    void DrawHelp();
    
    void DrawTextInputScreen();
    
    void DrawHeroSelect();
    
    void HandleTextInput();

    
    void DrawGame();

    void InitializeSpacePositions();
    void DrawFighters();
    void DrawSingleFighter(Fighters_Names fighter, Vector2 position);
    void Send_User_Info_To_Controller();
    Vector2 GetSpaceScreenPosition(int spaceNumber);


public:

    RaylibUI(Controller* control);


    void Run();

};


#endif