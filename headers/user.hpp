#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <vector>
#include "enums.hpp"
#include "card_abstract.hpp"
class User
{
    public:
        void Set_Age(const std::string& age);
        void Set_Name(const std::string& name);
        void Set_Hero_Name_Type(HERO_NAME hero_name_type);
        void Set_Hero_Name_String(const std::string& hero_name_string);
        void discard(int choice);
        void draw();

        std::string Return_UserName() const;
        std::string Return_Hero_Name_String() const;
        HERO_NAME Return_Hero_Type() const;
        std::string Return_User_Age() const;

        std::vector <Card_Base_Class*> user_hand;
        std::vector <dracula_cards> dracula_user_discarded;
        std::vector <sherlock_cards> sherlock_user_discarded;

    private:
        std::string age;
        std::string name;
        HERO_NAME hero_name_type;
        std::string hero_name_string;
        

};

#endif