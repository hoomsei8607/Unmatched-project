#include "../headers/graph.hpp"
#include "../headers/controller.hpp"
#include "../headers/Ui.hpp"
#include <iostream>

int main()
{
    srand(time(0));
    Controller control;
    User_Interface Interface_Controller;
    while (true)
    {

        if(Interface_Controller.Manage_Screen(control))
        {}
        else
        {
            break;
        }
    }
    control.screen.ExitLoopClosure()()
    return 0;
}