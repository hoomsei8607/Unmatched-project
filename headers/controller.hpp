#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "user.hpp"
#include "structs.hpp"
#include <string>
#include <vector>
#include <map>
#include "fighter_abstract.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

class Controller
{
    public:
        Controller();

        void Set_User1_And_User2_Info(const User1_And_User2_Info& info_struct);
        void Fill_Users_Info_Struct(User1_And_User2_Info& info_struct) const; 
        void Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct) const;
        void Set_Fighter_Space_Number(Fighters_Names fighter_name, int new_space);
        void Convert_Space_Number_To_Row_And_Column_Index(int space_number, Space_Row_And_Column_In_Array& info_struct);
        void Set_Younger_User_Variable_Value();
        void Change_User_Turn();
        void Boost_Fighter_Move_Value(Fighters_Names fighter_name, int boost_value);
        void Reset_Fighter_Move_Value(Fighters_Names fighter_name);
        void Initialize_Users_hands();
        void Instantiate_Card_Object(USER user, cards card_name);
        void discard(int card,USER user_turn);
        void draw(USER user);
        void Set_User_Turn(USER user_turn);
        void change_fighter_health(Fighters_Names fighter,int amount);
        void Call_Card_Effect_Function(USER user_turn, cards card_name, int index, Fighters_Names selected_enemy = Fighters_Names::NONE, int choice = -1,int selected_card=-1);
        void Boost_Selected_Card_Value(USER user_turn, int index, int boost_value);
        void Draw_Card_For_User(USER user_turn, cards card);
        void Set_Current_User_Action(USER_ACTION user_action);
        void change_value_with_boost(USER user_turn , int card_index);
        void Set_Who_Has_Won_The_Combat_Variable(USER user);
        void Disable_Card_Effect(USER user, int index);
        void Set_Selected_Enemy(Fighters_Names selected_enemy);
        void Select_Fighter(Fighters_Names fighter_name);
        void Revive_The_Selected_Fighter(Fighters_Names figher_name, int space_to_place_the_fighter_at);
        void Set_Card_Value(USER user_turn, int card_index, int card_value);

        int Return_Fighter_Move_Value(Fighters_Names fighter_name) const;
        int Return_Hero_Space_Number(Fighters_Names fighter_Name) const;
        int return_card_boost_value(int card,USER user_turn);
        int Return_card_Value(USER user_turn, int index);
        int get_attacker_selected_card_index();
        int get_defender_selected_card_index();
        
        bool Is_User_Hand_Empty(USER user_turn);
        bool Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn();
        bool Return_Is_Fighter_Alive(Fighters_Names name) const;
        bool Is_Selected_Card_A_Scheme_Card(USER user_turn, int index);
        bool Should_Card_Effect_Be_Executed(USER user, int index);
        bool Is_Any_Of_Dracula_Sisters_Dead();
        bool Does_Card_Exist_In_Hand_With_The_Corresponding_Value(USER user_turn, int card_value); // this function only searches for attack or defence cards

        USER Return_User_Turn() const;
        USER Return_Younger_User() const;
        USER Return_Older_User() const;
        USER return_who_won_the_combat() const;
        
        std::string Return_Card_Name(USER user_turn, int index);
        std::string Conver_Fighter_Name_Enum_To_String(Fighters_Names fighter_name);
        std::string Return_Younger_User_Name() const;
        std::string Return_Older_User_Name() const;
        std::string Return_User1_Username() const;
        std::string Return_User2_Username() const;
        std::string Get_Card_Immediate_Result_Log(USER user_turn, int index);
        
        HERO_NAME Return_Younger_Hero_Name() const;
        HERO_NAME Return_User1_Hero_Name() const;
        HERO_NAME Return_User2_Hero_Name() const;
        
        ftxui::Element Return_Hand_Elements_For_Render(USER user_turn);
        ftxui::Element Return_Hand_Elements_For_Boost_Screen_Render(int selected_card_to_be_boosted);
        ftxui::Element Return_A_Single_Card_Graphical_Representation(USER user_turn, int selected_Card);
        
        std::vector<Card_Base_Class*> Return_A_Copy_Of_User_Hand(USER user_turn);
        std::vector<std::string> Return_Hand_As_String(USER user_turn);
        std::vector<Fighters_Names> Return_Alive_Fighters(HERO_NAME which_crew);
        std::vector<int> Return_Sisters_Space_Numbers();
        std::vector<int> Return_Card_Indexes_That_Match_The_Given_Value(USER user_turn, int card_value); //this function works only for attack and defence cards only
        
        CARD_TYPE Return_Selected_Card_Type(USER user_turn, int index);
        
        CARD_EFFECT_TYPE Return_Selected_Card_Effect_Type(USER user_turn, int index);
        
        cards Return_Selected_Card_Name_As_An_Enum(USER user_turn, int index);
        
        ATTACKING_RANGE Return_Fighter_Attacking_Range(Fighters_Names selected_fighter);
        
        
        Fighters_Names Which_Fighter_Is_Currently_Selected(HERO_NAME hero_of_team);
        Fighters_Names Return_Fighter_Base_On_Space_Number(int space_number);
        Fighters_Names Get_Selected_Enemy();
        Fighters_Names Return_Card_Owner_Name(USER user_turn, int index);
        Fighters_Names Return_Dead_Sister_Number();

        ~Controller();
        Fighters_Print_Info* fighters_printing_info_array;
        int fighters_printing_info_count;
        ftxui::Element map_and_user_info;

    private:
        User user1;
        User user2;
        USER Who_Won_The_Combat;
        USER Younger_User;
        USER User_Turn;
        USER_ACTION current_user_action;

        Fighter_Base_Class* Dracula_And_Sisters[4];
        Fighter_Base_Class* sherlock_And_Watson[2];

        std::vector <Card_Base_Class*>  User1_Hand;
        std::vector <Card_Base_Class*>  User2_Hand;
        std::vector <cards> sherlock_deck;
        std::vector <cards> dracula_deck;

        std::map <int, Space_Row_And_Column_In_Array> Space_To_Array_Index_Map;

        int attacker_selected_card_index;
        int defender_selected_card_index;

        Fighters_Names Selected_Enemy_Hero;
    };
#endif