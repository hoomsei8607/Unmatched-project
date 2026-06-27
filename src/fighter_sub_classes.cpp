#include "../headers/fighters_sub_classes.hpp"

Dracula* Dracula::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Dracula;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;
}

Sherlock* Sherlock::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Sherlock;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;

}