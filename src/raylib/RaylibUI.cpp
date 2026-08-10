#include "../../headers/raylib/RaylibUI.hpp"



RaylibUI::RaylibUI()
{
    current_screen = Screen::MAIN_MENU;

    running = true;

    current_input = "";
    selected_hero = -1;
    user_number = 1;
}



void RaylibUI::Run()
{

    InitWindow(
        1280,
        720,
        "Unmatched"
    );


    SetTargetFPS(60);



    while(running && !WindowShouldClose())
    {

        Update();


        BeginDrawing();


        ClearBackground(DARKGRAY);


        Draw();


        EndDrawing();

    }



    CloseWindow();

}




void RaylibUI::Update()
{

    switch(current_screen)
    {

        case Screen::MAIN_MENU:

            if(IsKeyPressed(KEY_ENTER))
            {
                current_screen = Screen::USER1_NAME;
                current_input = "";
            }

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
                mouse.y < 500)
                {
                    selected_hero = 0;

                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        current_screen = Screen::USER2_HERO_SELECT;
                    }
                    else
                    {
                        current_screen = Screen::GAME;
                    }
                }


                if(mouse.x > 500 &&
                mouse.x < 700 &&
                mouse.y > 250 &&
                mouse.y < 500)
                {
                    selected_hero = 1;

                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        current_screen = Screen::USER2_HERO_SELECT;
                    }
                    else
                    {
                        current_screen = Screen::GAME;
                    }
                }


                if(mouse.x > 850 &&
                mouse.x < 1050 &&
                mouse.y > 250 &&
                mouse.y < 500)
                {
                    selected_hero = 2;


                    if(current_screen == Screen::USER1_HERO_SELECT)
                    {
                        current_screen = Screen::USER2_HERO_SELECT;
                    }
                    else
                    {
                        current_screen = Screen::GAME;
                    }
                }

            }
            break;


        case Screen::GAME:

            break;



        case Screen::EXIT:

            running = false;

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


        case Screen::GAME:


            DrawText(
                "GAME SCREEN",
                500,
                300,
                40,
                WHITE
            );


            break;



        case Screen::EXIT:

            break;


    }

}






void RaylibUI::DrawMainMenu()
{

    DrawText(
        "UNMATCHED",
        450,
        150,
        50,
        WHITE
    );


    DrawText(
        "Press ENTER to Start",
        430,
        350,
        30,
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
        450,
        200,
        40,
        WHITE
    );



    DrawText(
        current_input.c_str(),
        450,
        300,
        35,
        GREEN
    );


    DrawText(
        "Press ENTER when done",
        400,
        400,
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

        current_input = "";


        switch(current_screen)
        {


            case Screen::USER1_NAME:

                current_screen = Screen::USER1_AGE;

                break;



            case Screen::USER1_AGE:

                current_screen = Screen::USER2_NAME;

                break;



            case Screen::USER2_NAME:

                current_screen = Screen::USER2_AGE;

                break;



            case Screen::USER2_AGE:

                current_screen = Screen::USER1_HERO_SELECT;

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


    // draw heroes
    DrawRectangle(
        150,
        250,
        200,
        250,
        RED
    );


    DrawRectangle(
        500,
        250,
        200,
        250,
        BLUE
    );


    DrawRectangle(
        850,
        250,
        200,
        250,
        GREEN
    );


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
        "Alice",
        920,
        520,
        25,
        WHITE
    );

}