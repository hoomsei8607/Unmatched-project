#include "../headers/card_abstract.hpp"

int Card_Base_Class::get_card_value()
{
    return Card_Value;
}
int Card_Base_Class::get_Card_Boost_Value()
{
    return Card_Boost_Value;
}
CARD_EFFECT_TYPE Card_Base_Class::get_effect()
{
    return effect;
}
CARD_TYPE Card_Base_Class::get_type()
{
    return type;
}
CARD_OWNER Card_Base_Class::get_owner()
{
    return owner;
}
bool Card_Base_Class::get_is_discarded()
{
    return is_discarded;
}
int Card_Base_Class::get_card_number()
{
    return card_number;
}
std::string Card_Base_Class::get_card_name()
{
    return card_name;
}

std::string Card_Base_Class::Get_Card_Type_As_String()
{
    switch(type)
    {
        case CARD_TYPE::ATTACK:
            return "ATTACK";

        case CARD_TYPE::SCHEME:
            return "SCHEME";

        case CARD_TYPE::DEFENCE:
            return "DEFENCE";

        case CARD_TYPE::VERSATILE:
            return "VERSATILE";
    }
}


std::string Card_Base_Class::Get_Card_Owner_Name_As_String()
{
    switch (owner)
    {
        case  CARD_OWNER::ANY:
            return "ANY";
            
        case  CARD_OWNER::DRACULA:
            return "DRACULA";

        case  CARD_OWNER::SHERLOCK:
            return "SHERLOCK";
        case  CARD_OWNER::WATSON:
            return "WATSON";
        case  CARD_OWNER::SISITERS:
            return "SISTERS";
        }
}
std::string Card_Base_Class::Get_Card_Effect_Timing_As_String()
{

}
std::string Card_Base_Class::Get_Card_Effect_As_String()
{
    return card_effect_description;
}