#include "../headers/controller.hpp"
#include "../headers/raylib/RaylibUI.hpp"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    Controller controller;
    RaylibUI ui;
    ui.Run();

    return 0;
}
