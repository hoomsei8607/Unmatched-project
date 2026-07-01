#include "../headers/fighters_sub_classes.hpp"
#include "../headers/fighters_sub_classes.hpp"

Dracula* Dracula::Object_Instance = nullptr;
Watson* Watson::Object_Instance = nullptr;
Sherlock* Sherlock::Object_Instance = nullptr;


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

Watson* Watson::Get_Instance()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Watson;
    //if is the younger fighter current hero space should be 1
    //else space 2
    return Object_Instance;
}

void Sherlock::Destroy_Object()
{
    if(Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}

void Dracula::Destroy_Object()
{
    if(Dracula::Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}

void Watson::Destroy_Object()
{
    if(Object_Instance != nullptr)
    {
        delete Object_Instance;
        Object_Instance = nullptr;
    }
}
Dracula_Sister::Dracula_Sister(int sis_number)
{
    this->sister_number = sis_number;
}