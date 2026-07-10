#ifndef CARD_ABSTRACT_HPP
#define CARD_ABSTRACT_HPP
#include "enums.hpp"
#include <string>
#include "fighter_abstract.hpp"
class Card_Base_Class
{
    public:
    int get_card_value();
    int get_Card_Boost_Value();
    CARD_EFFECT_TYPE get_effect();
    CARD_TYPE get_type();
    CARD_OWNER get_owner();
    bool get_is_discarded();
    int get_card_number();
    std::string get_card_name();
    std::string Get_Card_Owner_Name_As_String();
    std::string Get_Card_Type_As_String();
    std::string Get_Card_Effect_Timing_As_String();
    std::string Get_Card_Effect_As_String();
    std::string Get_Card_Effect_Log();
    void Boost_Card_Value(int boost_value);
    virtual void Just_To_Make_Polymorphism_Available();
    void set_card_value(int value);
    void set_card_boost(int boost);
    cards Get_Card_Name_Enum();
    
    protected:
    int Card_Value;
    int Card_Boost_Value;
    CARD_EFFECT_TYPE effect;
    CARD_TYPE type;
    CARD_OWNER owner;
    cards card_name_enum;
    bool is_discarded;   
    int card_number;        
    std::string card_name;
    std::string card_effect_description;
    std::string card_effect_log;
};

#endif