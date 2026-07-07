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