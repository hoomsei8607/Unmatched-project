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
            DrawSingleFighter(
                fighter,
                {
                    MAP_OFFSET_X + space_positions[i].x,
                    MAP_OFFSET_Y + space_positions[i].y
                }
            );
        }
    }
}


void RaylibUI::DrawSingleFighter(
    Fighters_Names fighter,
    Vector2 position
)
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

    DrawRectangleRec(maneuver_button, DARKGRAY);

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