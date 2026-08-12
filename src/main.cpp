#include "../headers/controller.hpp"
#include "../headers/raylib/RaylibUI.hpp"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    Controller controller;

    //temp
    controller.Set_Fighter_Space_Number(
    Fighters_Names::DRACULA,
    5
    );

    RaylibUI ui(&controller);
    ui.Run();

    return 0;
}
