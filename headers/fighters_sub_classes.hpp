#ifndef HERO_CLASSES_HPP
#define HERO_CLASSES_HPP
#include "fighter_abstract.hpp"

class Dracula : public Fighter_Base_Class
{
public:
    Dracula();
};


class Sherlock : public Fighter_Base_Class
{
public:
    Sherlock();
};


class Watson : public Fighter_Base_Class
{
public:
    Watson();
};


class Dracula_Sister : public Fighter_Base_Class
{
public:
    Dracula_Sister(int sister_number);

private:
    int sister_number;
};


#endif
