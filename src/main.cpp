#include "../headers/graph.hpp"
#include "../headers/controller.hpp"
#include "../headers/Ui.hpp"

int main()
{
    User_Interface Interface_Controller;
    while (true)
    {
        if(Interface_Controller.Manage_Screen())
        {}
        else
        {
            break;
        }
    }
    
    return 0;
}