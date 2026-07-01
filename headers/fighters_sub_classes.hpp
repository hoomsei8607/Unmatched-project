#ifndef HERO_CLASSES_HPP
#define HERO_CLASSES_HPP
#include "fighter_abstract.hpp"

class Dracula : public Fighter_Base_Class //singleton
{
    public:

        static Dracula* Get_Instance();
        Dracula(const Dracula&) = delete;
        static void Destroy_Object();
    private:
        Dracula() = default;
        static Dracula* Object_Instance;

};


class Sherlock : public Fighter_Base_Class //singleton
{
    public:
        static Sherlock* Get_Instance();
        Sherlock(const Sherlock&) = delete;
        static void Destroy_Object();
    private:
        Sherlock() = default;
        static Sherlock* Object_Instance;

};

class Watson : public Fighter_Base_Class
{
    public:
        static Watson* Get_Instance();
        Watson(const Watson&) = delete;
        static void Destroy_Object();

    private:
        Watson() = default;
        static Watson* Object_Instance;
};


class Dracula_Sister : public Fighter_Base_Class
{
    public:
        Dracula_Sister(int sister_number);
    private:
        int sister_number;
};



#endif
