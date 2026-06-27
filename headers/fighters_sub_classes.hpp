#ifndef HERO_CLASSES_HPP
#define HERO_CLASSES_HPP
#include "fighter_abstract.hpp"

class Dracula : public Fighter_Base_Class //singleton
{
    public:
        static Dracula* Get_Instance();
    private:
        static Dracula* Object_Instance;
        

};


class Sherlock : public Fighter_Base_Class //singleton
{
    public:
        static Sherlock* Get_Instance();
    private:
        static Sherlock* Object_Instance;

};

Dracula* Dracula::Object_Instance = nullptr;
Sherlock* Sherlock::Object_Instance = nullptr;


#endif
