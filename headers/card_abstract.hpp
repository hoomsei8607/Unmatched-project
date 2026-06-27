#ifndef CARD_ABSTRACT_HPP
#define CARD_ABSTRACT_HPP
#include "enums.hpp"
class Card_Base_Class
{
    public:
    
    protected:
        int Card_Value;
        int Card_Boost_Value;
        CARD_EFFECT_TYPE effect;
        CARD_TYPE type;
        CARD_OWNER owner;
                    
};

#endif