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

        FIGHT,

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

    //card textures: dracula
    Texture2D ambushDrac;
    Texture2D baptismBloodDrac;
    Texture2D beastformDrac;
    Texture2D dashDrac;
    Texture2D domybiddingDrac;
    Texture2D exploitDrac;
    Texture2D feedingfrenzyDrac;
    Texture2D feintDrac;
    Texture2D lookintomyeyesDrac;
    Texture2D mistformDrac;
    Texture2D preyuponDrac;
    Texture2D raveningseductionDrac;
    Texture2D thirstforsustenanceDrac;


    //card textures: sherlock
    Texture2D admisiteraidSher;
    Texture2D confirmsuspicionSher;
    Texture2D counterpunchSher;
    Texture2D deducestrategySher;
    Texture2D educationenverendsSher;
    Texture2D elementarySher;
    Texture2D eliminatetheimpossibleSher;
    Texture2D feintSher;
    Texture2D fixedpointSher;
    Texture2D masterofdisguiseSher;
    Texture2D servicerevolverSher;
    Texture2D studymethodsSher;
    Texture2D thegameisafootSher;

    //card texturs: invisible man
    Texture2D codednotesInv;
    Texture2D cofoundInv;
    Texture2D covertprepInv;
    Texture2D dreamingofrevengeInv;
    Texture2D emergefrommistInv;
    Texture2D impossibletoseeInv;
    Texture2D intothinairInv;
    Texture2D lurkingInv;
    Texture2D reignofterrorInv;
    Texture2D rollingfogInv;
    Texture2D slipawayInv;
    Texture2D steplightlyInv;
    Texture2D vanishInv;

    const int MAP_OFFSET_X = 600;
    const int MAP_OFFSET_Y = 150;

    USER placement_user;
    bool sidekick_placement_active;
    int current_sidekick_index;
    std::vector<int> available_placement_spaces;
    std::vector<Fighters_Names> sidekicks_to_place;

    bool maneuver_mode = false;
    Fighters_Names selected_fighter = Fighters_Names::NONE;
    int selected_fighter_space = -1;
    bool fight_selection_mode = false;
    std::set<int> maneuver_available_spaces;
    int selected_maneuver_space = -1;


    Rectangle maneuver_button;
    Rectangle fight_button;
    Rectangle confirm_card_button;

    Rectangle back_button;
    Rectangle skip_button;

    enum class FightScreenState
    {
        ATTACKER_CARD_SELECTION,
        DEFENDER_CARD_SELECTION,

        BEFORE_COMBAT,
        DURING_COMBAT,
        COMBAT_RESULT,
        AFTER_COMBAT
    };


    void ExecuteBeforeCombat();
    void ExecuteDuringCombat();
    void ExecuteAfterCombat();
    void DrawCombatResult();
    void HandleCombatPhaseScreens();

    FightScreenState fight_screen_state = FightScreenState::ATTACKER_CARD_SELECTION;

    int selected_attacker_card = -1;
    int selected_defender_card = -1;
    int attacker_card_value = 0;
    int defender_card_value = 0;
    int combat_damage = 0;

    std::string combat_phase_log;
    std::string combat_result_text;





    void Start_SideKick_Placement();
    void Handle_SideKick_Placement();
    void Draw_Placement_Highlights();
    void Finish_SideKick_Placement();
    void DrawManeuverButton();
    void DrawManeuverAvailableSpaces();
    void Handle_Fighter_Selection();
    void Handle_Maneuver();

    void DrawFightButton();

    void DrawFightScreen();

    void DrawFighterHUD();


    void DrawFightHero(Fighters_Names fighter, Vector2 position);
    void DrawAttackerHand();
    void DrawDefenderHand();
    void HandleFightCardSelection();

    bool IsCardOwnedByFighter(Fighters_Names fighter, Fighters_Names card_owner);
    bool IsCardUsableInFight(USER user, int card_index);

    void Handle_Fight();

    int GetClickedManeuverSpace();

    bool IsManeuverButtonClicked();
    bool IsFightButtonClicked();
    bool IsConfirmCardButtonClicked();
    bool IsBackButtonClicked();
    bool IsSkipButtonClicked();

    Texture2D GetCardTexture(cards card);
    void DrawCardTexture(cards card, Rectangle destination);


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