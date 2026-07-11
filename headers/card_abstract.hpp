#ifndef CARD_ABSTRACT_HPP
#define CARD_ABSTRACT_HPP
#include "enums.hpp"
#include <string>
#include "fighter_abstract.hpp"
class Card_Base_Class
{
    public:
    Card_Base_Class();
    int get_card_value();
    int get_Card_Boost_Value();
    int get_card_number();

    CARD_EFFECT_TYPE get_effect();

    CARD_TYPE get_type();

    CARD_OWNER get_owner();

    bool get_is_discarded();
    bool Is_Card_Effect_Available();

    void set_card_value(int value);
    void set_card_boost(int boost);
    void Boost_Card_Value(int boost_value);
    void Disable_Card_Effect_Boolian(); 

    std::string get_card_name();
    std::string Get_Card_Owner_Name_As_String();
    std::string Get_Card_Type_As_String();
    std::string Get_Card_Effect_Timing_As_String();
    std::string Get_Card_Effect_As_String();
    std::string Get_Card_Effect_Log();

    virtual void Just_To_Make_Polymorphism_Available();

    cards Get_Card_Name_Enum();
    
    protected:
    int Card_Value;
    int Card_Boost_Value;
    int card_number;        
    CARD_EFFECT_TYPE effect;
    CARD_TYPE type;
    CARD_OWNER owner;
    cards card_name_enum;
    bool is_discarded;   
    bool Should_Card_Effect_Be_Applied;
    std::string card_name;
    std::string card_effect_description;
    std::string card_effect_log;
};

#endif