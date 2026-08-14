#include "../../headers/controller.hpp"
#include "../../headers/graph.hpp"
#include "../../headers/raylib/RaylibUI.hpp"
#include <algorithm>
#include <raylib.h>
#include <cmath>


float Distance(Vector2 a, Vector2 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return std::sqrt(dx * dx + dy * dy);
}


RaylibUI::RaylibUI(Controller* control)
{

    current_screen = Screen::MAIN_MENU;
    first_hero_selected = false;

    running = true;


    current_input = "";



    player1.hero = -1;

    player2.hero = -1;



    for(int i = 0; i < 3; i++)
    {
        hero_taken[i] = false;
    }

    controller = control;

    sidekick_placement_active = false;
    placement_user = USER::NONE;
    current_sidekick_index = 0;


    maneuver_button = {
        1350,
        0,
        180,
        60
    };

    fight_button = {
        1150,
        0,
        180,
        60
    };

    confirm_card_button = {
        GetScreenWidth() / 2.0f - 70,
        600,
        140,
        55
    };

    back_button = {
        20,
        20,
        150,
        55
    };

skip_button = {
        GetScreenWidth() / 2.0f + 100,
        580,
        150,
        55
    };


}


void RaylibUI::Run()
{

    InitWindow(
        1880,
        1150,
        "Unmatched"
    );


    SetTargetFPS(60);
    draculaResized = LoadTexture("../assets/dracula/DracArtResized.png");
    sherlockResized = LoadTexture("../assets/sherlock/holmsArtResized.png");
    invisibleResized = LoadTexture("../assets/invisibleMan/invArtResized.png");

    dracula_image = LoadTexture("../assets/dracula/dracula.png");
    sister1_image = LoadTexture("../assets/dracula/sis1.png");
    sister2_image = LoadTexture("../assets/dracula/sis2.png");
    sister3_image = LoadTexture("../assets/dracula/sis3.png");

    sherlock_image = LoadTexture("../assets/sherlock/sherlockTran.png");
    watson_image = LoadTexture("../assets/sherlock/drwatson.png");

    invisible_man_image = LoadTexture("../assets/invisibleMan/tranInv.png");

    //card textures: dracula
    ambushDrac = LoadTexture("../assets/cards/dracula/ambush.png");
    baptismBloodDrac = LoadTexture("../assets/cards/dracula/baptism-of-blood.png");
    beastformDrac = LoadTexture("../assets/cards/dracula/beastform.png");
    dashDrac = LoadTexture("../assets/cards/dracula/dash.png");
    domybiddingDrac = LoadTexture("../assets/cards/dracula/do-my-bidding.png");
    exploitDrac = LoadTexture("../assets/cards/dracula/exploit.png");
    feedingfrenzyDrac = LoadTexture("../assets/cards/dracula/feeding-frenzy.png");
    feintDrac = LoadTexture("../assets/cards/dracula/feint (1).png");
    lookintomyeyesDrac = LoadTexture("../assets/cards/dracula/look-into-my-eyes.png");
    mistformDrac = LoadTexture("../assets/cards/dracula/mistform.png");
    preyuponDrac = LoadTexture("../assets/cards/dracula/prey-upon.png");
    raveningseductionDrac = LoadTexture("../assets/cards/dracula/ravening-seduction.png");
    thirstforsustenanceDrac = LoadTexture("../assets/cards/dracula/thirst-for-sustenance.png");


    //card textures: sherlock
    admisiteraidSher = LoadTexture("../assets/cards/holms/administer-aid.png");
    confirmsuspicionSher = LoadTexture("../assets/cards/holms/confirm-suspicion.png");
    counterpunchSher = LoadTexture("../assets/cards/holms/counterpunch.png");
    deducestrategySher = LoadTexture("../assets/cards/holms/deduce-strategy.png");
    educationenverendsSher = LoadTexture("../assets/cards/holms/education-never-ends.png");
    elementarySher = LoadTexture("../assets/cards/holms/elementary.png");
    eliminatetheimpossibleSher = LoadTexture("../assets/cards/holms/eliminate-the-impossible.png");
    feintSher = LoadTexture("../assets/cards/holms/feint (2).png");
    fixedpointSher = LoadTexture("../assets/cards/holms/fixed-point-in-a-changing-age.png");
    masterofdisguiseSher = LoadTexture("../assets/cards/holms/master-of-disguise.png");
    servicerevolverSher = LoadTexture("../assets/cards/holms/service-revolver.png");
    studymethodsSher = LoadTexture("../assets/cards/holms/study-methods.png");
    thegameisafootSher = LoadTexture("../assets/cards/holms/the-game-is-afoot.png");

    //card texturs: invisible man
    codednotesInv = LoadTexture("../assets/cards/invisibleMan/coded-notes.png");
    cofoundInv = LoadTexture("../assets/cards/invisibleMan/confound.png");
    covertprepInv = LoadTexture("../assets/cards/invisibleMan/covert-preparation.png");
    dreamingofrevengeInv = LoadTexture("../assets/cards/invisibleMan/dreaming-of-revenge.png");
    emergefrommistInv = LoadTexture("../assets/cards/invisibleMan/emerge-from-mist.png");
    impossibletoseeInv = LoadTexture("../assets/cards/invisibleMan/impossible-to-see.png");
    intothinairInv = LoadTexture("../assets/cards/invisibleMan/into-thin-air.png");
    lurkingInv = LoadTexture("../assets/cards/invisibleMan/lurking.png");
    reignofterrorInv = LoadTexture("../assets/cards/invisibleMan/reign-of-terror.png");
    rollingfogInv = LoadTexture("../assets/cards/invisibleMan/rolling-fog.png");
    slipawayInv = LoadTexture("../assets/cards/invisibleMan/slip-away.png");
    steplightlyInv = LoadTexture("../assets/cards/invisibleMan/step-lightly.png");
    vanishInv = LoadTexture("../assets/cards/invisibleMan/vanish.png");

    mapImage = LoadTexture("../assets/board.jpeg");
    InitializeSpacePositions();

    while(running && !WindowShouldClose())
    {

        Update();


        BeginDrawing();


        ClearBackground(DARKGRAY);


        Draw();


        EndDrawing();

    }

    UnloadTexture(draculaResized);
    UnloadTexture(sherlockResized);
    UnloadTexture(invisibleResized);
    UnloadTexture(mapImage);
    UnloadTexture(dracula_image);
    UnloadTexture(sister1_image);
    UnloadTexture(sister2_image);
    UnloadTexture(sister3_image);
    UnloadTexture(sherlock_image);
    UnloadTexture(watson_image);
    UnloadTexture(invisible_man_image);

    CloseWindow();

}




void RaylibUI::Update()
{

    switch(current_screen)
    {

        case Screen::MAIN_MENU:

            HandleMainMenu();

        break;


        case Screen::USER1_NAME:

        case Screen::USER1_AGE:

        case Screen::USER2_NAME:

        case Screen::USER2_AGE:

            HandleTextInput();

            break;



        case Screen::USER1_HERO_SELECT:

        case Screen::USER2_HERO_SELECT:


            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {

                Vector2 mouse = GetMousePosition();


                if(mouse.x > 150 &&
                mouse.x < 350 &&
                mouse.y > 250 &&
                mouse.y < 450 && !hero_taken[0])
                {
                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        player1.hero = 0;
                    }
                    else
                    {
                        player2.hero = 0;
                    }

                    if(!first_hero_selected)
                    {
                        first_hero_selected = true;

                        if(hero_selection_user == USER::USER1)
                        {
                            current_screen = Screen::USER2_HERO_SELECT;
                        }
                        else
                        {
                            current_screen = Screen::USER1_HERO_SELECT;
                        }
                    }
                    else
                    {
                        Send_User_Info_To_Controller();
                        controller->Initialize_Hero_Space_Numbers();
                        controller->Initialize_Users_hands();
                        Start_SideKick_Placement();
                        current_screen = Screen::GAME;
                    }
                    hero_taken[0] = true;
                }


                if(mouse.x > 500 &&
                mouse.x < 700 &&
                mouse.y > 250 &&
                mouse.y < 450 && !hero_taken[1])
                {
                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        player1.hero = 1;
                    }
                    else
                    {
                        player2.hero = 1;
                    }
                    if(!first_hero_selected)
                    {
                        first_hero_selected = true;

                        if(hero_selection_user == USER::USER1)
                        {
                            current_screen = Screen::USER2_HERO_SELECT;
                        }
                        else
                        {
                            current_screen = Screen::USER1_HERO_SELECT;
                        }
                    }
                    else
                    {
                        Send_User_Info_To_Controller();
                        controller->Initialize_Hero_Space_Numbers();
                        controller->Initialize_Users_hands();
                        Start_SideKick_Placement();
                        current_screen = Screen::GAME;
                    }
                    hero_taken[1] = true;
                }


                if(mouse.x > 850 &&
                mouse.x < 1050 &&
                mouse.y > 250 &&
                mouse.y < 450 && !hero_taken[2])
                {
                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        player1.hero = 2;
                    }
                    else
                    {
                        player2.hero = 2;
                    }

                    if(!first_hero_selected)
                    {
                        first_hero_selected = true;

                        if(hero_selection_user == USER::USER1)
                        {
                            current_screen = Screen::USER2_HERO_SELECT;
                        }
                        else
                        {
                            current_screen = Screen::USER1_HERO_SELECT;
                        }
                    }
                    else
                    {
                        Send_User_Info_To_Controller();
                        controller->Initialize_Hero_Space_Numbers();
                        controller->Initialize_Users_hands();
                        Start_SideKick_Placement();
                        current_screen = Screen::GAME;
                    }
                    hero_taken[2] = true;
                }

            }
            break;


        case Screen::GAME:

            Handle_SideKick_Placement();

            if(!sidekick_placement_active)
            {
                Handle_Fighter_Selection();
                Handle_Maneuver();
                Handle_Fight();
            }

            break;


        case Screen::FIGHT:

            if(
                fight_screen_state == FightScreenState::ATTACKER_CARD_SELECTION ||
                fight_screen_state == FightScreenState::DEFENDER_CARD_SELECTION
            )
            {
                HandleFightCardSelection();
            }
            else
            {
                HandleCombatPhaseScreens();
            }

            break;
            
        case Screen::EXIT:

            running = false;

            break;
            
    
        case Screen::HELP:
    
            if(IsKeyPressed(KEY_ESCAPE))    
            {
                current_screen = Screen::MAIN_MENU;
            }
    
            break;
    }

}





void RaylibUI::Draw()
{

    switch(current_screen)
    {


        case Screen::MAIN_MENU:

            DrawMainMenu();

            break;



        case Screen::USER1_NAME:

        case Screen::USER1_AGE:

        case Screen::USER2_NAME:

        case Screen::USER2_AGE:

            DrawTextInputScreen();

            break;



        case Screen::USER1_HERO_SELECT:

        case Screen::USER2_HERO_SELECT:

            DrawHeroSelect();

            break;


        case Screen::HELP:

            DrawHelp();

            break;


        case Screen::GAME:

            DrawGame();

            break;


        case Screen::FIGHT:

            DrawFightScreen();

            break;
            

        case Screen::EXIT:

        break;


    }

}




void RaylibUI::DrawMainMenu()
{

    DrawText(
        "UNMATCHED",
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 100,
        50,
        WHITE
    );



    DrawRectangle(
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 220,
        300,
        60,
        DARKBLUE
    );


    DrawText(
        "START GAME",
        MAP_OFFSET_X + 510,
        MAP_OFFSET_Y + 240,
        25,
        WHITE
    );



    DrawRectangle(
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 310,
        300,
        60,
        DARKBLUE
    );


    DrawText(
        "LOAD GAME",
        MAP_OFFSET_X + 520,
        MAP_OFFSET_Y + 330,
        25,
        WHITE
    );



    DrawRectangle(
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 400,
        300,
        60,
        DARKBLUE
    );


    DrawText(
        "HELP",
        MAP_OFFSET_X + 570,
        MAP_OFFSET_Y + 420,
        25,
        WHITE
    );



    DrawRectangle(
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 490,
        300,
        60,
        DARKBLUE
    );


    DrawText(
        "EXIT",
        MAP_OFFSET_X + 570,
        MAP_OFFSET_Y + 510,
        25,
        WHITE
    );

}



void RaylibUI::DrawTextInputScreen()
{

    std::string title;



    switch(current_screen)
    {

        case Screen::USER1_NAME:

            title = "Player 1 Name";

            break;


        case Screen::USER1_AGE:

            title = "Player 1 Age";

            break;


        case Screen::USER2_NAME:

            title = "Player 2 Name";

            break;


        case Screen::USER2_AGE:

            title = "Player 2 Age";

            break;


        default:

            title = "";

            break;

    }



    DrawText(
        title.c_str(),
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 200,
        40,
        WHITE
    );



    DrawText(
        current_input.c_str(),
        MAP_OFFSET_X + 450,
        MAP_OFFSET_Y + 300,
        35,
        GREEN
    );


    DrawText(
        "Press ENTER when done",
        MAP_OFFSET_X + 400,
        MAP_OFFSET_Y + 400,
        25,
        WHITE
    );

}






void RaylibUI::HandleTextInput()
{

    int key = GetCharPressed();



    while(key > 0)
    {
        bool age_screen =
            current_screen == Screen::USER1_AGE ||
            current_screen == Screen::USER2_AGE;


        if(age_screen)
        {
            if(key >= '0' && key <= '9')
            {
                current_input.push_back((char)key);
            }
        }
        else
        {
            if(key >= 32 && key <= 126)
            {
                current_input.push_back((char)key);
            }
        }

        key = GetCharPressed();

    }





    if(IsKeyPressed(KEY_BACKSPACE))
    {

        if(!current_input.empty())
        {
            current_input.pop_back();
        }

    }




    if(IsKeyPressed(KEY_ENTER))
    {
        if(current_input.empty())
        {
            return;
        }


        switch(current_screen)
        {
            case Screen::USER1_NAME:

                player1.name = current_input;

                current_input = "";

                current_screen = Screen::USER1_AGE;

                break;


            case Screen::USER1_AGE:

                player1.age = std::stoi(current_input);

                current_input = "";

                current_screen = Screen::USER2_NAME;

                break;


            case Screen::USER2_NAME:

                player2.name = current_input;

                current_input = "";

                current_screen = Screen::USER2_AGE;

                break;

            case Screen::USER2_AGE:

                player2.age = std::stoi(current_input);

                current_input = "";

                hero_selection_user =
                    controller->Set_Starting_User_By_Ages(player1.age, player2.age);

                if(hero_selection_user == USER::USER1)
                {
                    current_screen = Screen::USER1_HERO_SELECT;
                }
                else
                {
                    current_screen = Screen::USER2_HERO_SELECT;
                }

                break;

            default:

                break;
        }
    }
}


void RaylibUI::DrawHeroSelect()
{

    if(current_screen == Screen::USER1_HERO_SELECT)
    {
        DrawText(
            "Player 1 Choose Your Hero",
            350,
            100,
            40,
            WHITE
        );
    }
    else
    {
        DrawText(
            "Player 2 Choose Your Hero",
            350,
            100,
            40,
            WHITE
        );
    }



    DrawTexture(draculaResized, 150, 250, WHITE);
    DrawTexture(sherlockResized, 500, 250, WHITE);
    DrawTexture(invisibleResized, 850, 250, WHITE);
    if(hero_taken[0])
    {
        DrawTexture(draculaResized, 150, 250, GRAY);
    }
    if(hero_taken[1])
    {
        DrawTexture(sherlockResized, 500, 250, GRAY);
    }
    if(hero_taken[2])
    {
        DrawTexture(invisibleResized, 850, 250, GRAY);
    }
    
        DrawText(
            "Dracula",
            200,
            520,
            25,
            WHITE
        );


    DrawText(
        "Sherlock",
        550,
        520,
        25,
        WHITE
    );


    DrawText(
        "INVISIBLE MAN",
        920,
        520,
        25,
        WHITE
    );

}

void RaylibUI::HandleMainMenu()
{

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

        Vector2 mouse = GetMousePosition();



        if(mouse.x > MAP_OFFSET_X + 450 &&
           mouse.x < MAP_OFFSET_X + 750 &&
           mouse.y > MAP_OFFSET_Y + 220 &&
           mouse.y < MAP_OFFSET_Y + 280)
        {
            current_screen = Screen::USER1_NAME;

            current_input = "";
        }



        if(mouse.x > MAP_OFFSET_X + 450 &&
           mouse.x < MAP_OFFSET_X + 750 &&
           mouse.y > MAP_OFFSET_Y + 400 &&
           mouse.y < MAP_OFFSET_Y + 460)
        {
            current_screen = Screen::HELP;
        }



        if(mouse.x > MAP_OFFSET_X + 450 &&
           mouse.x < MAP_OFFSET_X + 750 &&
           mouse.y > MAP_OFFSET_Y + 490 &&
           mouse.y < MAP_OFFSET_Y + 550)
        {
            running = false;
        }

    }

}

void RaylibUI::DrawHelp()
{

    DrawText(
        "UNMATCHED HELP",
        400,
        200,
        40,
        WHITE
    );


    DrawText(
        "Choose heroes and defeat your opponent!",
        300,
        300,
        25,
        WHITE
    );


    DrawText(
        "Press ESC to return",
        450,
        500,
        25,
        WHITE
    );

}

void RaylibUI::DrawGame()
{
    DrawTexture(mapImage, MAP_OFFSET_X, MAP_OFFSET_Y, WHITE);

    for(int i = 1; i <= 32; i++)
    {
        DrawText(
            std::to_string(i).c_str(),
            MAP_OFFSET_X + space_positions[i].x,
            MAP_OFFSET_Y + space_positions[i].y,
            35,
            WHITE
        );
    }

    Draw_Placement_Highlights();
    DrawManeuverAvailableSpaces();
    DrawFighters();
    DrawManeuverButton();
    DrawFightButton();

    if(selected_fighter != Fighters_Names::NONE)
    {
        DrawRectangleRec(back_button, BLUE);

        DrawText(
            "BACK",
            back_button.x + 45,
            back_button.y + 18,
            20,
            WHITE
        );
    }

    DrawFighterHUD();
    
}



void RaylibUI::InitializeSpacePositions()
{
    space_positions[1] = {97,112};
    space_positions[2] = {265,67};
    space_positions[3] = {495,97};
    space_positions[4] = {740,101};
    space_positions[5] = {1015,106};
    space_positions[6] = {1188,112};
    space_positions[7] = {81,260 };
    space_positions[8] = {230,273};
    space_positions[9] = {364,209};
    space_positions[10] = {654,210};
    space_positions[11] = {882,210};
    space_positions[12] = {1098,216};
    space_positions[13] = {120,468};
    space_positions[14] = {267,428};
    space_positions[15] = {407,373};
    space_positions[16] = {714,402};
    space_positions[17] = {1083,375};
    space_positions[18] = {190,646};
    space_positions[19] = {410,568};
    space_positions[20] = {585,478};
    space_positions[21] = {880,471};
    space_positions[22] = {1021,504};
    space_positions[23] = {1176,481};
    space_positions[24] = {269,757};
    space_positions[25] = {409,722};
    space_positions[26] = {545,744};
    space_positions[27] = {634,640};
    space_positions[28] = {804,664};
    space_positions[29] = {973,672};
    space_positions[30] = {1191,658};
    space_positions[31] = {697,757};
    space_positions[32] = {1089,757};
}

void RaylibUI::DrawFighters()
{
    for(int i = 1; i <= 32; i++)
    {
        Fighters_Names fighter =
            controller->Return_Fighter_Base_On_Space_Number(i);

        if(fighter != Fighters_Names::NONE)
        {
            Vector2 position =
                GetSpaceScreenPosition(i);

            DrawSingleFighter(
                fighter,
                position
            );
        }
    }



    if(fight_selection_mode)
    {
        std::set<int> available_enemy_spaces =
            controller->Return_Fight_Available_Enemy_Spaces(
                selected_fighter
            );

        for(int space : available_enemy_spaces)
        {
            Vector2 position =
                GetSpaceScreenPosition(space);

            DrawCircleLines(
                position.x,
                position.y,
                50.0f,
                YELLOW
            );

            DrawCircleLines(
                position.x,
                position.y,
                54.0f,
                YELLOW
            );
        }
    }
}

void RaylibUI::DrawSingleFighter(Fighters_Names fighter, Vector2 position)
{
    switch(fighter)
    {

        case Fighters_Names::DRACULA:

            DrawTexture(
                dracula_image,
                position.x - dracula_image.width / 2,
                position.y - dracula_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::SIS1:

            DrawTexture(
                sister1_image,
                position.x - sister1_image.width / 2,
                position.y - sister1_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::SIS2:

            DrawTexture(
                sister2_image,
                position.x - sister2_image.width / 2,
                position.y - sister2_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::SIS3:

            DrawTexture(
                sister3_image,
                position.x - sister3_image.width / 2,
                position.y - sister3_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::SHERLOCK:

            DrawTexture(
                sherlock_image,
                position.x - sherlock_image.width / 2,
                position.y - sherlock_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::WATSON:

            DrawTexture(
                watson_image,
                position.x - watson_image.width / 2,
                position.y - watson_image.height / 2,
                WHITE
            );

        break;


        case Fighters_Names::INVISIBLE_MAN:

            DrawTexture(
                invisible_man_image,
                position.x - invisible_man_image.width / 2,
                position.y - invisible_man_image.height / 2,
                WHITE
            );

        break;


        default:

        break;
    }

}

void RaylibUI::Send_User_Info_To_Controller()
{
    User1_And_User2_Info info_struct;

    info_struct.User1_Name = player1.name;
    info_struct.User1_Age = std::to_string(player1.age);
    info_struct.User2_Name = player2.name;
    info_struct.User2_Age = std::to_string(player2.age);

    info_struct.User1_Hero_Type = static_cast<HERO_NAME>(player1.hero);
    info_struct.User2_Hero_Type = static_cast<HERO_NAME>(player2.hero);

    switch(info_struct.User1_Hero_Type)
    {
        case HERO_NAME::DRACULA:
            info_struct.User1_Hero_Name = "Dracula";
            break;

        case HERO_NAME::SHERLOCK:
            info_struct.User1_Hero_Name = "Sherlock";
            break;

        case HERO_NAME::INVISIBLE_MAN:
            info_struct.User1_Hero_Name = "Invisible Man";
            break;
    }

    switch(info_struct.User2_Hero_Type)
    {
        case HERO_NAME::DRACULA:
            info_struct.User2_Hero_Name = "Dracula";
            break;

        case HERO_NAME::SHERLOCK:
            info_struct.User2_Hero_Name = "Sherlock";
            break;

        case HERO_NAME::INVISIBLE_MAN:
            info_struct.User2_Hero_Name = "Invisible Man";
            break;
    }

    controller->Set_User1_And_User2_Info(info_struct);
}

Vector2 RaylibUI::GetSpaceScreenPosition(int space_number)
{
    return {
        static_cast<float>(MAP_OFFSET_X + space_positions[space_number].x),
        static_cast<float>(MAP_OFFSET_Y + space_positions[space_number].y)
    };
}

void RaylibUI::Start_SideKick_Placement()
{
    sidekick_placement_active = true;

    placement_user = controller->Return_Younger_User();

    available_placement_spaces =
        controller->Return_Available_Placement_Spaces(placement_user);

    current_sidekick_index = 0;

    sidekicks_to_place.clear();

    HERO_NAME hero;

    if(placement_user == USER::USER1)
    {
        hero = controller->Return_User1_Hero_Name();
    }
    else
    {
        hero = controller->Return_User2_Hero_Name();
    }

    if(hero == HERO_NAME::DRACULA)
    {
        sidekicks_to_place = {
            Fighters_Names::SIS1,
            Fighters_Names::SIS2,
            Fighters_Names::SIS3
        };
    }
    else if(hero == HERO_NAME::SHERLOCK)
    {
        sidekicks_to_place = {
            Fighters_Names::WATSON
        };
    }
    else if(hero == HERO_NAME::INVISIBLE_MAN)
    {
        // No sidekicks.
    }

    if(sidekicks_to_place.empty())
    {
        Finish_SideKick_Placement();
    }
}

void RaylibUI::Handle_SideKick_Placement()
{
    if(!sidekick_placement_active)
    {
        return;
    }

    if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    Vector2 mouse = GetMousePosition();

    for(int space : available_placement_spaces)
    {
        Vector2 position = GetSpaceScreenPosition(space);

        
        if(Distance(mouse, position) <= 35.0f)
        {
            Fighters_Names fighter =
                sidekicks_to_place[current_sidekick_index];

        controller->Set_Fighter_Space_Number(
            fighter,
            space
        );

        Graph* game_graph = Graph::Get_Map_Graph_Pointer();

        game_graph->Set_User_Occupying_Space(
            placement_user,
            space
        );

            available_placement_spaces.erase(
                std::remove(
                    available_placement_spaces.begin(),
                    available_placement_spaces.end(),
                    space
                ),
                available_placement_spaces.end()
            );

            current_sidekick_index++;

            if(current_sidekick_index >=
               static_cast<int>(sidekicks_to_place.size()))
            {
                Finish_SideKick_Placement();
            }

            return;
        }
    }
}

void RaylibUI::Draw_Placement_Highlights()
{
    if(!sidekick_placement_active)
    {
        return;
    }

    for(int space : available_placement_spaces)
    {
        Vector2 position = GetSpaceScreenPosition(space);

        DrawCircle(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            40,
            Fade(GREEN, 0.35f)
        );

        DrawCircleLines(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            40,
            GREEN
        );
    }
}

void RaylibUI::Finish_SideKick_Placement()
{
    USER next_user;

    if(placement_user == controller->Return_Younger_User())
    {
        next_user = controller->Return_Older_User();
    }
    else
    {
        sidekick_placement_active = false;
        placement_user = USER::NONE;
        available_placement_spaces.clear();
        sidekicks_to_place.clear();

        return;
    }

    placement_user = next_user;

    available_placement_spaces =
        controller->Return_Available_Placement_Spaces(
            placement_user
        );

    current_sidekick_index = 0;

    sidekicks_to_place.clear();

    HERO_NAME hero;

    if(placement_user == USER::USER1)
    {
        hero = controller->Return_User1_Hero_Name();
    }
    else
    {
        hero = controller->Return_User2_Hero_Name();
    }

    if(hero == HERO_NAME::DRACULA)
    {
        sidekicks_to_place = {
            Fighters_Names::SIS1,
            Fighters_Names::SIS2,
            Fighters_Names::SIS3
        };
    }
    else if(hero == HERO_NAME::SHERLOCK)
    {
        sidekicks_to_place = {
            Fighters_Names::WATSON
        };
    }

    if(sidekicks_to_place.empty())
    {
        sidekick_placement_active = false;
    }
}


void RaylibUI::DrawManeuverButton()
{
    if (selected_fighter == Fighters_Names::NONE)
    {
        return;
    }

    DrawRectangleRec(maneuver_button, BLUE);

    const char* text;

    if (selected_maneuver_space == -1)
    {
        text = "MANEUVER";
    }
    else
    {
        text = "CONFIRM";
    }

    DrawText(
        text,
        (maneuver_button.x + 25),
        (maneuver_button.y + 20),
        20,
        WHITE
    );
}

bool RaylibUI::IsManeuverButtonClicked()
{
    return
        CheckCollisionPointRec(
            GetMousePosition(),
            maneuver_button
        )
        &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool RaylibUI::IsFightButtonClicked()
{
    return
        CheckCollisionPointRec(
            GetMousePosition(),
            fight_button
        )
        &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}



void RaylibUI::DrawManeuverAvailableSpaces()
{
    if (!maneuver_mode)
    {
        return;
    }

    for (int space_number : maneuver_available_spaces)
    {
        Vector2 position = GetSpaceScreenPosition(space_number);

        if (space_number == selected_maneuver_space)
        {
            DrawCircle(
                (position.x),
                (position.y),
                38,
                YELLOW
            );
        }
        else
        {
            DrawCircle(
                (position.x),
                (position.y),
                32,
                Fade(GREEN, 0.5f)
            );
        }
    }
}

void RaylibUI::DrawFightButton()
{
    if(selected_fighter == Fighters_Names::NONE)
    {
        return;
    }

    if(!controller->Can_Fighter_Fight(selected_fighter))
    {
        return;
    }

    DrawRectangleRec(
        fight_button,
        BLUE
    );

    const char* text;

    if(fight_selection_mode)
    {
        text = "SELECT";
    }
    else
    {
        text = "FIGHT";
    }

    DrawText(
        text,
        fight_button.x + 45,
        fight_button.y + 20,
        20,
        WHITE
    );
}

int RaylibUI::GetClickedManeuverSpace()
{
    if (!maneuver_mode)
    {
        return -1;
    }

    Vector2 mouse_position = GetMousePosition();

    for (int space_number : maneuver_available_spaces)
    {
        Vector2 space_position = GetSpaceScreenPosition(space_number);

        if (CheckCollisionPointCircle(
                mouse_position,
                space_position,
                35.0f))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                return space_number;
            }
        }
    }

    return -1;
}


void RaylibUI::Handle_Fighter_Selection()
{
    if(maneuver_mode)
    {
        return;
    }

    if(IsBackButtonClicked())
    {
        TraceLog(
            LOG_INFO,
            "Fight selection cancelled with BACK"
        );

        fight_selection_mode = false;

        controller->Set_Selected_Enemy(
            Fighters_Names::NONE
        );

        return;
    }

    if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    Vector2 mouse = GetMousePosition();

    for(int space = 1; space <= 32; space++)
    {
        Vector2 position = GetSpaceScreenPosition(space);

        if(CheckCollisionPointCircle(mouse, position, 40.0f))
        {
            Fighters_Names fighter =
                controller->Return_Fighter_Base_On_Space_Number(space);

            if(fighter == Fighters_Names::NONE)
            {
                return;
            }

            if(!controller->Can_User_Select_Fighter(
                    controller->Return_User_Turn(),
                    fighter))
            {
                TraceLog(
                    LOG_INFO,
                    "This fighter cannot be controlled by the current user."
                );

                return;
            }

            selected_fighter = fighter;
            selected_fighter_space = space;

            TraceLog(
                LOG_INFO,
                "Selected fighter: %s",
                controller->Conver_Fighter_Name_Enum_To_String(
                    selected_fighter
                ).c_str()
            );

            return;
        }
    }
}

void RaylibUI::Handle_Maneuver()
{
    if(selected_fighter == Fighters_Names::NONE)
    {
        return;
    }

    if(maneuver_mode)
    {
        if(IsBackButtonClicked())
        {
            TraceLog(
                LOG_INFO,
                "Maneuver cancelled with BACK"
            );

            maneuver_mode = false;
            maneuver_available_spaces.clear();
            selected_maneuver_space = -1;

            return;
        }



        if(IsManeuverButtonClicked() && selected_maneuver_space != -1)
        {
            TraceLog(
                LOG_INFO,
                "Confirming maneuver to space %d",
                selected_maneuver_space
            );

            if(controller->Move_Fighter(
                    selected_fighter,
                    selected_maneuver_space))
            {
                TraceLog(LOG_INFO, "Maneuver successful");

                selected_fighter_space = selected_maneuver_space;

                maneuver_mode = false;
                maneuver_available_spaces.clear();
                selected_maneuver_space = -1;

                selected_fighter = Fighters_Names::NONE;
                selected_fighter_space = -1;
            }
            else
            {
                TraceLog(LOG_ERROR, "Maneuver failed");
            }

            return;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int clicked_space = GetClickedManeuverSpace();

            if(clicked_space != -1)
            {
                selected_maneuver_space = clicked_space;

                TraceLog(
                    LOG_INFO,
                    "Selected maneuver destination: %d",
                    clicked_space
                );

                return;
            }
            maneuver_mode = false;
            maneuver_available_spaces.clear();
            selected_maneuver_space = -1;

            selected_fighter = Fighters_Names::NONE;
            selected_fighter_space = -1;

            TraceLog(
                LOG_INFO,
                "Maneuver cancelled"
            );

            return;
        }

        return;
    }

    if(IsManeuverButtonClicked())
    {
        maneuver_available_spaces =
            controller->Return_Maneuver_Available_Spaces(
                selected_fighter
            );

        if(maneuver_available_spaces.empty())
        {
            TraceLog(
                LOG_INFO,
                "No available maneuver spaces"
            );

            return;
        }

        maneuver_mode = true;
        selected_maneuver_space = -1;

        TraceLog(
            LOG_INFO,
            "Maneuver mode activated"
        );

        for(int space : maneuver_available_spaces)
        {
            TraceLog(
                LOG_INFO,
                "Available space: %d",
                space
            );
        }
    }
}

void RaylibUI::Handle_Fight()
{
    if(selected_fighter == Fighters_Names::NONE)
    {
        return;
    }

    if(!controller->Can_Fighter_Fight(selected_fighter))
    {
        return;
    }



    if(!fight_selection_mode)
    {
        if(IsFightButtonClicked())
        {
            controller->Set_Selected_Enemy(
                Fighters_Names::NONE
            );

            fight_selection_mode = true;

            TraceLog(
                LOG_INFO,
                "Fight selection mode activated"
            );
        }

        return;
    }



    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse = GetMousePosition();

        for(int space = 1; space <= 32; space++)
        {
            Vector2 position =
                GetSpaceScreenPosition(space);

            if(!CheckCollisionPointCircle(
                    mouse,
                    position,
                    40.0f))
            {
                continue;
            }

            Fighters_Names fighter =
                controller->Return_Fighter_Base_On_Space_Number(space);

            if(fighter == Fighters_Names::NONE)
            {
                return;
            }

            if(!controller->Can_User_Select_Fighter(controller->Return_User_Turn(), fighter))
            {
                std::set<int> available_enemy_spaces =
                    controller->Return_Fight_Available_Enemy_Spaces(selected_fighter);

                if(available_enemy_spaces.find(space) != available_enemy_spaces.end())
                {
                    controller->Set_Selected_Enemy(fighter);

                    TraceLog(
                        LOG_INFO,
                        "Enemy selected: %s",
                        controller->Conver_Fighter_Name_Enum_To_String(
                            fighter
                        ).c_str()
                    );
                }
                else
                {
                    TraceLog(
                        LOG_INFO,
                        "This enemy is outside attack range."
                    );
                }

                return;
            }

            TraceLog(
                LOG_INFO,
                "Clicked own fighter - not an enemy."
            );

            return;
        }
    }



    if(IsFightButtonClicked())
    {
        if(controller->Get_Selected_Enemy()
            == Fighters_Names::NONE)
        {
            TraceLog(
                LOG_INFO,
                "No enemy selected"
            );

            return;
        }

        TraceLog(
            LOG_INFO,
            "Enemy confirmed"
        );
        fight_screen_state = FightScreenState::ATTACKER_CARD_SELECTION;

        selected_attacker_card = -1;
        selected_defender_card = -1;

        current_screen = Screen::FIGHT;

        fight_selection_mode = false;
    }
}

void RaylibUI::DrawFightScreen()
{
    ClearBackground(DARKGRAY);

    if(fight_screen_state == FightScreenState::COMBAT_RESULT)
    {
        DrawCombatResult();
        return;
    }

    USER attacker_user =
        controller->Return_User_Turn();

    USER defender_user;

    if(attacker_user == USER::USER1)
        defender_user = USER::USER2;
    else
        defender_user = USER::USER1;

    Fighters_Names attacker =
        selected_fighter;

    Fighters_Names defender =
        controller->Get_Selected_Enemy();

    DrawText(
        "FIGHT",
        GetScreenWidth() / 2 - 50,
        30,
        40,
        WHITE
    );


    DrawText(
        "ATTACKER",
        300,
        100,
        25,
        WHITE
    );

    DrawText(
        controller->Conver_Fighter_Name_Enum_To_String(
            attacker
        ).c_str(),
        300,
        135,
        25,
        WHITE
    );

    DrawFightHero(
        attacker,
        {250, 180}
    );


    DrawText(
        "VS",
        GetScreenWidth() / 2 - 25,
        220,
        35,
        WHITE
    );


    DrawText(
        "DEFENDER",
        1100,
        100,
        25,
        WHITE
    );

    DrawText(
        controller->Conver_Fighter_Name_Enum_To_String(
            defender
        ).c_str(),
        1100,
        135,
        25,
        WHITE
    );

    DrawFightHero(
        defender,
        {1050, 180}
    );

    switch(fight_screen_state)
    {
        case FightScreenState::ATTACKER_CARD_SELECTION:

            DrawText(
                "CHOOSE AN ATTACK CARD",
                GetScreenWidth() / 2 - 180,
                500,
                25,
                YELLOW
            );

            DrawAttackerHand();

            break;


        case FightScreenState::DEFENDER_CARD_SELECTION:

            DrawText(
                "DEFENDER: CHOOSE A DEFENCE CARD",
                GetScreenWidth() / 2 - 250,
                500,
                25,
                YELLOW
            );

            DrawDefenderHand();
            DrawRectangleRec(
                skip_button,
                BLUE
            );

        DrawText(
            "SKIP",
            skip_button.x + 50,
            skip_button.y + 15,
            20,
            WHITE
        );

            break;


        case FightScreenState::BEFORE_COMBAT:

            DrawText(
                "BEFORE COMBAT",
                GetScreenWidth() / 2 - 120,
                500,
                30,
                YELLOW
            );

            DrawText(
                combat_phase_log.c_str(),
                250,
                560,
                22,
                WHITE
            );

            DrawText(
                "CLICK TO CONTINUE",
                GetScreenWidth() / 2 - 100,
                650,
                22,
                LIGHTGRAY
            );

            break;


        case FightScreenState::DURING_COMBAT:

            DrawText(
                "DURING COMBAT",
                GetScreenWidth() / 2 - 120,
                500,
                30,
                YELLOW
            );

            DrawText(
                combat_phase_log.c_str(),
                250,
                560,
                22,
                WHITE
            );

            DrawText(
                "CLICK TO CONTINUE",
                GetScreenWidth() / 2 - 100,
                650,
                22,
                LIGHTGRAY
            );

            break;


        case FightScreenState::COMBAT_RESULT:

            DrawCombatResult();

            break;


        case FightScreenState::AFTER_COMBAT:

            DrawText(
                "AFTER COMBAT",
                GetScreenWidth() / 2 - 120,
                500,
                30,
                YELLOW
            );

            DrawText(
                combat_phase_log.c_str(),
                250,
                560,
                22,
                WHITE
            );

            DrawText(
                "CLICK TO CONTINUE",
                GetScreenWidth() / 2 - 100,
                650,
                22,
                LIGHTGRAY
            );

            break;
    }
    if(
        fight_screen_state == FightScreenState::ATTACKER_CARD_SELECTION ||
        fight_screen_state == FightScreenState::DEFENDER_CARD_SELECTION)
    {
        DrawRectangleRec(
            back_button,
            DARKGRAY
        );

        DrawText(
            "BACK",
            back_button.x + 45,
            back_button.y + 18,
            20,
            WHITE
        );
    }

}

void RaylibUI::DrawAttackerHand()
{
    USER attacker = controller->Return_User_Turn();

    std::vector<Card_Base_Class*> hand =
        controller->Return_A_Copy_Of_User_Hand(attacker);

    const int max_cards = 7;

    int card_count = static_cast<int>(hand.size());

    if(card_count > max_cards)
        card_count = max_cards;

    const int card_width = 140;
    const int card_height = 190;
    const int spacing = 15;

    int total_width =
        card_count * card_width +
        (card_count - 1) * spacing;

    int start_x = (GetScreenWidth() - total_width) / 2;
    int y = 650;

    for(int i = 0; i < card_count; i++)
    {
        
        int x = start_x + i * (card_width + spacing);

        Rectangle card_rect = {
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(card_width),
            static_cast<float>(card_height)
        };

        bool selected = (i == selected_attacker_card);
        cards card_name =
            hand[i]->Get_Card_Name_Enum();

        DrawCardTexture(
            card_name,
            card_rect
        );

        if(selected)
        {
            DrawRectangleLinesEx(
                card_rect,
                6,
                YELLOW
            );
        }
        else
        {
            DrawRectangleLinesEx(
                card_rect,
                3,
                BLACK
            );
        }
    }

    if(fight_screen_state == FightScreenState::ATTACKER_CARD_SELECTION)
    {
        if(selected_attacker_card != -1)
        {
            DrawRectangleRec(
                confirm_card_button,
                GREEN
            );

            DrawText(
                "CONFIRM",
                confirm_card_button.x + 28,
                confirm_card_button.y + 13,
                20,
                WHITE
            );
        }
    }


}

void RaylibUI::DrawDefenderHand()
{
    USER attacker = controller->Return_User_Turn();

    USER defender;

    if(attacker == USER::USER1)
        defender = USER::USER2;
    else
        defender = USER::USER1;

    std::vector<Card_Base_Class*> hand =
        controller->Return_A_Copy_Of_User_Hand(defender);

    const int max_cards = 7;

    int card_count = static_cast<int>(hand.size());

    if(card_count > max_cards)
        card_count = max_cards;

    const int card_width = 140;
    const int card_height = 190;
    const int spacing = 15;

    int total_width =
        card_count * card_width +
        (card_count - 1) * spacing;

    int start_x = (GetScreenWidth() - total_width) / 2;
    int y = 650;

    for(int i = 0; i < card_count; i++)
    {
        int x = start_x + i * (card_width + spacing);

        Rectangle card_rect = {
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(card_width),
            static_cast<float>(card_height)
        };

        bool selected = (i == selected_defender_card);

        cards card_name = hand[i]->Get_Card_Name_Enum();

        DrawCardTexture(
            card_name,
            card_rect
        );

        if(selected)
        {
            DrawRectangleLinesEx(
                card_rect,
                6,
                YELLOW
            );
        }
        else
        {
            DrawRectangleLinesEx(
                card_rect,
                3,
                BLACK
            );
        }

        if(fight_screen_state == FightScreenState::DEFENDER_CARD_SELECTION)
        {
            if(selected_defender_card != -1)
            {
                DrawRectangleRec(
                    confirm_card_button,
                    GREEN
                );

                DrawText(
                    "CONFIRM",
                    confirm_card_button.x + 28,
                    confirm_card_button.y + 13,
                    20,
                    WHITE
                );
            }
        }



    }
}


void RaylibUI::DrawFightHero(Fighters_Names fighter, Vector2 position)
{
    DrawSingleFighter(fighter, position);
}


bool RaylibUI::IsCardUsableInFight(USER user, int card_index)
{
    std::vector<Card_Base_Class*> hand =
        controller->Return_A_Copy_Of_User_Hand(user);

    if(card_index < 0 ||
       card_index >= static_cast<int>(hand.size()))
    {
        return false;
    }

    Card_Base_Class* card = hand[card_index];

    if(card == nullptr)
    {
        return false;
    }

    Fighters_Names fighter_using_card;

    if(fight_screen_state ==
       FightScreenState::ATTACKER_CARD_SELECTION)
    {
        fighter_using_card = selected_fighter;
    }
    else if(fight_screen_state ==
            FightScreenState::DEFENDER_CARD_SELECTION)
    {
        fighter_using_card =
            controller->Get_Selected_Enemy();
    }
    else
    {
        return false;
    }

    if(!IsCardOwnedByFighter(
            fighter_using_card,
            card->get_owner()))
    {
        TraceLog(
            LOG_INFO,
            "Card %d does not belong to fighter %d",
            card_index,
            static_cast<int>(fighter_using_card)
        );

        return false;
    }

    CARD_TYPE type = card->get_type();

    if(fight_screen_state ==
       FightScreenState::ATTACKER_CARD_SELECTION)
    {
        return type == CARD_TYPE::ATTACK ||
               type == CARD_TYPE::VERSATILE;
    }

    if(fight_screen_state ==
       FightScreenState::DEFENDER_CARD_SELECTION)
    {
        return type == CARD_TYPE::DEFENCE ||
               type == CARD_TYPE::VERSATILE;
    }

    return false;
}

void RaylibUI::HandleFightCardSelection()
{

    if(IsBackButtonClicked())
    {
        TraceLog(
            LOG_INFO,
            "Fight cancelled with BACK"
        );

        fight_screen_state =
            FightScreenState::ATTACKER_CARD_SELECTION;

        selected_attacker_card = -1;
        selected_defender_card = -1;

        fight_selection_mode = false;

        controller->Set_Selected_Enemy(
            Fighters_Names::NONE
        );

        current_screen = Screen::GAME;

        return;
    }

    if(fight_screen_state == FightScreenState::DEFENDER_CARD_SELECTION)
    {
        if(IsSkipButtonClicked())
        {
            TraceLog(
                LOG_INFO,
                "Defender skipped card selection"
            );

            selected_defender_card = -1;

            fight_screen_state =
                FightScreenState::BEFORE_COMBAT;

            return;
        }
    }



    if(IsConfirmCardButtonClicked())
    {
        if(fight_screen_state ==
        FightScreenState::ATTACKER_CARD_SELECTION)
        {
            if(selected_attacker_card == -1)
            {
                TraceLog(
                    LOG_INFO,
                    "No attacker card selected."
                );

                return;
            }

            TraceLog(
                LOG_INFO,
                "Attacker card confirmed: %d",
                selected_attacker_card
            );

            fight_screen_state =
                FightScreenState::DEFENDER_CARD_SELECTION;

            selected_defender_card = -1;

            return;
        }

        if(fight_screen_state ==
        FightScreenState::DEFENDER_CARD_SELECTION)
        {
            if(selected_defender_card == -1)
            {
                TraceLog(
                    LOG_INFO,
                    "No defender card selected."
                );

                return;
            }
            TraceLog(
                LOG_INFO,
                "Defender card confirmed: %d",
                selected_defender_card
            );

            fight_screen_state = FightScreenState::BEFORE_COMBAT;

            return;

    }
}


    USER attacker =
        controller->Return_User_Turn();

    USER defender;

    if(attacker == USER::USER1)
        defender = USER::USER2;
    else
        defender = USER::USER1;

    USER current_user;

    if(
        fight_screen_state ==
        FightScreenState::ATTACKER_CARD_SELECTION
    )
    {
        current_user = attacker;
    }
    else
    {
        current_user = defender;
    }

    std::vector<Card_Base_Class*> hand =
        controller->Return_A_Copy_Of_User_Hand(
            current_user
        );

    int card_count =
        static_cast<int>(hand.size());

    if(card_count > 7)
        card_count = 7;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse =
            GetMousePosition();

        const int card_width = 140;
        const int card_height = 190;
        const int spacing = 15;

        int total_width =
            card_count * card_width +
            (card_count - 1) * spacing;

        int start_x =
            (GetScreenWidth() - total_width) / 2;

        int y = 650;

        for(int i = 0; i < card_count; i++)
        {
            int x =
                start_x +
                i * (card_width + spacing);

            Rectangle card_rect = {
                static_cast<float>(x),
                static_cast<float>(y),
                static_cast<float>(card_width),
                static_cast<float>(card_height)
            };

            if(!CheckCollisionPointRec(
                    mouse,
                    card_rect))
            {
                continue;
            }

            if(!IsCardUsableInFight(
                    current_user,
                    i))
            {
                TraceLog(
                    LOG_INFO,
                    "Card %d cannot be used in this part of combat.",
                    i
                );

                return;
            }


            if(fight_screen_state == FightScreenState::ATTACKER_CARD_SELECTION)
            {
                selected_attacker_card = i;

                TraceLog(
                    LOG_INFO,
                    "Attacker card highlighted: %d",
                    i
                );

                return;
            }

            else
            {
                selected_defender_card = i;

                TraceLog(
                    LOG_INFO,
                    "Defender selected card: %d",
                    i
                );

            }

            return;
        }
    }
}

bool RaylibUI::IsConfirmCardButtonClicked()
{
    return
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(
            GetMousePosition(),
            confirm_card_button
        );
}

Texture2D RaylibUI::GetCardTexture(cards card)
{
    switch(card)
    {
        // Dracula
        case cards::AMBUSH:
            return ambushDrac;

        case cards::BAPTISM_OF_BLOOD:
            return baptismBloodDrac;

        case cards::BEASTFORM:
            return beastformDrac;

        case cards::DASH:
            return dashDrac;

        case cards::EXPLOIT:
            return exploitDrac;

        case cards::FEEDING_FRENZY:
            return feedingfrenzyDrac;

        case cards::FEINT:
            // IMPORTANT:
            // Your project has two Feint textures, one for each deck.
            // We will handle this properly based on owner later.
            return feintDrac;

        case cards::LOOK_INTO_MY_EYES:
            return lookintomyeyesDrac;

        case cards::MISTFORM:
            return mistformDrac;

        case cards::PREY_UPON:
            return preyuponDrac;

        case cards::RAVENING_SEDUCTION:
            return raveningseductionDrac;

        case cards::THIRST_FOR_SUSTENANCE:
            return thirstforsustenanceDrac;


        // Sherlock
        case cards::AMINISTER_AID:
            return admisiteraidSher;

        case cards::CONFIRM_SUSPICION:
            return confirmsuspicionSher;

        case cards::COUNTERPUNCH:
            return counterpunchSher;

        case cards::DEDUCE_STRATEGY:
            return deducestrategySher;

        case cards::EDUCATION_NEVER_ENDS:
            return educationenverendsSher;

        case cards::ELEMENTARY:
            return elementarySher;

        case cards::ELIMINATE_THE_IMPOSSIBLE:
            return eliminatetheimpossibleSher;

        case cards::FIXED_POINT_IN_A_CHANGING_AGE:
            return fixedpointSher;

        case cards::MASTER_OF_DISGUISE:
            return masterofdisguiseSher;

        case cards::SERVICE_REVOLVER:
            return servicerevolverSher;

        case cards::STUDY_METHODS:
            return studymethodsSher;

        case cards::THE_GAME_IS_AFOOT:
            return thegameisafootSher;

        default:
            return Texture2D{};
    }
}

void RaylibUI::DrawCardTexture(cards card, Rectangle destination)
{
    Texture2D texture = GetCardTexture(card);

    if(texture.id == 0)
    {
        DrawRectangleRec(destination, WHITE);

        DrawText(
            "MISSING",
            destination.x + 10,
            destination.y + 10,
            16,
            RED
        );

        return;
    }

    Rectangle source = {
        0,
        0,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        {0, 0},
        0.0f,
        WHITE
    );
}



void RaylibUI::ExecuteBeforeCombat()
{
    USER attacker = controller->Return_User_Turn();

    USER defender;

    if(attacker == USER::USER1)
        defender = USER::USER2;
    else
        defender = USER::USER1;

    combat_phase_log.clear();

    if(controller->Return_Selected_Card_Effect_Type(
            attacker,
            selected_attacker_card)
       == CARD_EFFECT_TYPE::IMMEDIATE)
    {
        if(controller->Should_Card_Effect_Be_Executed(
                attacker,
                selected_attacker_card))
        {
            controller->Call_Card_Effect_Function(
                attacker,
                controller->Return_Selected_Card_Name_As_An_Enum(
                    attacker,
                    selected_attacker_card
                ),
                selected_attacker_card
            );

            combat_phase_log +=
                controller->Get_Card_Immediate_Result_Log(
                    attacker,
                    selected_attacker_card
                );
        }
    }

    if(selected_defender_card != -1)
    {
        if(controller->Return_Selected_Card_Effect_Type(
                defender,
                selected_defender_card)
           == CARD_EFFECT_TYPE::IMMEDIATE)
        {
            if(controller->Should_Card_Effect_Be_Executed(
                    defender,
                    selected_defender_card))
            {
                controller->Call_Card_Effect_Function(
                    defender,
                    controller->Return_Selected_Card_Name_As_An_Enum(
                        defender,
                        selected_defender_card
                    ),
                    selected_defender_card
                );

                combat_phase_log +=
                    controller->Get_Card_Immediate_Result_Log(
                        defender,
                        selected_defender_card
                    );
            }
        }
    }

    if(combat_phase_log.empty())
    {
        combat_phase_log = "NO EFFECTS OCCURRED";
    }

    fight_screen_state =
        FightScreenState::DURING_COMBAT;
}

void RaylibUI::ExecuteDuringCombat()
{
    USER attacker = controller->Return_User_Turn();

    USER defender;

    if(attacker == USER::USER1)
        defender = USER::USER2;
    else
        defender = USER::USER1;

    combat_phase_log.clear();

    if(selected_defender_card != -1)
    {
        if(controller->Return_Selected_Card_Effect_Type(
                defender,
                selected_defender_card)
           == CARD_EFFECT_TYPE::DURING_COMBAT)
        {
            if(controller->Should_Card_Effect_Be_Executed(
                    defender,
                    selected_defender_card))
            {
                controller->Call_Card_Effect_Function(
                    defender,
                    controller->Return_Selected_Card_Name_As_An_Enum(
                        defender,
                        selected_defender_card
                    ),
                    selected_defender_card,
                    Fighters_Names::NONE,
                    -1,
                    selected_attacker_card
                );

                combat_phase_log +=
                    controller->Get_Card_Immediate_Result_Log(
                        defender,
                        selected_defender_card
                    );
            }
        }
    }

    if(controller->Return_Selected_Card_Effect_Type(
            attacker,
            selected_attacker_card)
       == CARD_EFFECT_TYPE::DURING_COMBAT)
    {
        if(controller->Should_Card_Effect_Be_Executed(
                attacker,
                selected_attacker_card))
        {
            controller->Call_Card_Effect_Function(
                attacker,
                controller->Return_Selected_Card_Name_As_An_Enum(
                    attacker,
                    selected_attacker_card
                ),
                selected_attacker_card,
                Fighters_Names::NONE,
                -1,
                selected_defender_card
            );

            combat_phase_log +=
                controller->Get_Card_Immediate_Result_Log(
                    attacker,
                    selected_attacker_card
                );
        }
    }

    if(combat_phase_log.empty())
    {
        combat_phase_log = "NO EFFECTS OCCURRED";
    }

    attacker_card_value =
        controller->Return_card_Value(
            attacker,
            selected_attacker_card
        );

    if(selected_defender_card == -1)
    {
        defender_card_value = 0;
    }
    else
    {
        defender_card_value =
            controller->Return_card_Value(
                defender,
                selected_defender_card
            );
    }

    combat_damage =
        attacker_card_value - defender_card_value;

    
    if(combat_damage > 0)
    {
        controller->Set_Who_Has_Won_The_Combat_Variable(
            attacker
        );

        controller->change_fighter_health(
            controller->Get_Selected_Enemy(),
            -combat_damage
        );

        combat_result_text =
            "ATTACKER WON THE COMBAT";
    }
    else
    {
        controller->Set_Who_Has_Won_The_Combat_Variable(
            defender
        );

        combat_damage = 0;

        combat_result_text =
            "DEFENDER WON THE COMBAT";
    }

    fight_screen_state =
        FightScreenState::AFTER_COMBAT;
}

void RaylibUI::ExecuteAfterCombat()
{
    USER attacker = controller->Return_User_Turn();

    USER defender;

    if(attacker == USER::USER1)
        defender = USER::USER2;
    else
        defender = USER::USER1;

    combat_phase_log.clear();

    if(controller->Return_Selected_Card_Effect_Type(
            attacker,
            selected_attacker_card)
       == CARD_EFFECT_TYPE::AFTER_COMBAT)
    {
        if(controller->Should_Card_Effect_Be_Executed(
                attacker,
                selected_attacker_card))
        {
            controller->Call_Card_Effect_Function(
                attacker,
                controller->Return_Selected_Card_Name_As_An_Enum(
                    attacker,
                    selected_attacker_card
                ),
                selected_attacker_card
            );

            combat_phase_log +=
                controller->Get_Card_Immediate_Result_Log(
                    attacker,
                    selected_attacker_card
                );
        }
    }

    if(selected_defender_card != -1)
    {
        if(controller->Return_Selected_Card_Effect_Type(
                defender,
                selected_defender_card)
           == CARD_EFFECT_TYPE::AFTER_COMBAT)
        {
            if(controller->Should_Card_Effect_Be_Executed(
                    defender,
                    selected_defender_card))
            {
                controller->Call_Card_Effect_Function(
                    defender,
                    controller->Return_Selected_Card_Name_As_An_Enum(
                        defender,
                        selected_defender_card
                    ),
                    selected_defender_card
                );

                combat_phase_log +=
                    controller->Get_Card_Immediate_Result_Log(
                        defender,
                        selected_defender_card
                    );
            }
        }
    }

    if(combat_phase_log.empty())
    {
        combat_phase_log = "NO EFFECTS OCCURRED";
    }

    fight_screen_state =
        FightScreenState::COMBAT_RESULT;
}


void RaylibUI::DrawCombatResult()
{
    ClearBackground(DARKGRAY);
    DrawText(
        "COMBAT RESULT",
        GetScreenWidth() / 2 - 120,
        100,
        35,
        WHITE
    );

    DrawText(
        combat_result_text.c_str(),
        GetScreenWidth() / 2 - 180,
        180,
        28,
        YELLOW
    );

    DrawText(
        TextFormat(
            "ATTACK VALUE: %d",
            attacker_card_value
        ),
        350,
        280,
        25,
        WHITE
    );

    DrawText(
        TextFormat(
            "DEFENCE VALUE: %d",
            defender_card_value
        ),
        850,
        280,
        25,
        WHITE
    );

    DrawText(
        TextFormat(
            "DAMAGE DEALT: %d",
            combat_damage
        ),
        GetScreenWidth() / 2 - 100,
        350,
        25,
        WHITE
    );

    DrawText(
        "CLICK TO CONTINUE",
        GetScreenWidth() / 2 - 100,
        500,
        22,
        LIGHTGRAY
    );
}

bool RaylibUI::IsCardOwnedByFighter(
    Fighters_Names fighter,
    Fighters_Names card_owner)
{
    if(card_owner == Fighters_Names::ANY)
    {
        return true;
    }

    if(card_owner == Fighters_Names::SISTERS)
    {
        return fighter == Fighters_Names::SIS1 ||
               fighter == Fighters_Names::SIS2 ||
               fighter == Fighters_Names::SIS3;
    }

    return fighter == card_owner;
}

void RaylibUI::HandleCombatPhaseScreens()
{
    if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    switch(fight_screen_state)
    {
        case FightScreenState::BEFORE_COMBAT:
            ExecuteBeforeCombat();
            break;

        case FightScreenState::DURING_COMBAT:
            ExecuteDuringCombat();
            break;

        case FightScreenState::AFTER_COMBAT:
            ExecuteAfterCombat();
            break;

        case FightScreenState::COMBAT_RESULT:

            current_screen = Screen::GAME;
            controller->Discard_Cards_If_Deck_Has_More_Than_7_Cards(controller->Return_User_Turn());
            if(controller->Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn())
            {
                controller->Change_User_Turn();
            }
            selected_fighter = Fighters_Names::NONE;
            selected_maneuver_space = -1;
            fight_selection_mode = false;

            break;

        default:
            break;
    }
}

bool RaylibUI::IsBackButtonClicked()
{
    return
        CheckCollisionPointRec(
            GetMousePosition(),
            back_button
        )
        &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}


bool RaylibUI::IsSkipButtonClicked()
{
    return
        CheckCollisionPointRec(
            GetMousePosition(),
            skip_button
        )
        &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void RaylibUI::DrawFighterHUD()
{
    if(selected_fighter == Fighters_Names::NONE)
    {
        return;
    }

    Fighter_Base_Class* fighter =
        controller->Get_Fighter(selected_fighter);

    if(fighter == nullptr)
    {
        return;
    }

    DrawRectangle(
        0,
        300,
        MAP_OFFSET_X,
        GetScreenHeight(),
        Fade(BLACK, 0.85f)
    );

    DrawText(
        "FIGHTER INFO",
        40,
        360,
        32,
        WHITE
    );

    DrawLine(
        40,
        405,
        MAP_OFFSET_X - 40,
        105,
        GRAY
    );

    std::string fighter_name =
        controller->Conver_Fighter_Name_Enum_To_String(
            selected_fighter
        );

    DrawText(
        "FIGHTER:",
        40,
        445,
        22,
        LIGHTGRAY
    );

    DrawText(
        fighter_name.c_str(),
        40,
        480,
        30,
        WHITE
    );

    DrawText(
        "HEALTH:",
        40,
        540,
        22,
        LIGHTGRAY
    );

    DrawText(
        std::to_string(
            fighter->Return_Fighter_Current_Hp()
        ).c_str(),
        40,
        575,
        30,
        WHITE
    );

    DrawText(
        "MOVE:",
        250,
        640,
        22,
        LIGHTGRAY
    );

    DrawText(
        std::to_string(
            fighter->Return_Fighter_Current_Move_Value()
        ).c_str(),
        250,
        675,
        30,
        WHITE
    );

    // Current space
    DrawText(
        "SPACE:",
        40,
        640,
        22,
        LIGHTGRAY
    );

    DrawText(
        std::to_string(
            fighter->Return_Fighter_Current_Space()
        ).c_str(),
        40,
        675,
        30,
        WHITE
    );
}