#include "../headers/controller.hpp"
#include "../headers/raylib/RaylibUI.hpp"

int main()
{
        std::ifstream check("../saves.dat", std::ios::binary);
        if (!check)
        {
            std::ofstream create("../saves.dat", std::ios::binary);
        
            if (!create)
            {
                std::cerr<<"couldn't create file\n";
                return 1;
            }

            create.close();
        }
    check.close();
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
