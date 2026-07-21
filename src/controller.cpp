#include "../headers/controller.hpp"
#include "../headers/fighters_sub_classes.hpp"
#include "../headers/structs.hpp"
#include "../headers/cards.hpp"
#include "../headers/Ui_GameLoop_Screen_Related_Function.hpp"
#include <stdexcept>
#include <algorithm>
#include <random>

#include <iostream>
#include <chrono>
#include <thread>

Controller::Controller()
{
    Space_To_Array_Index_Map[1] = {2, 12};   
    Space_To_Array_Index_Map[2] = {0, 19};   
    Space_To_Array_Index_Map[3] = {0, 31};   
    Space_To_Array_Index_Map[4] = {0, 37};   
    Space_To_Array_Index_Map[5] = {0, 49};   
    Space_To_Array_Index_Map[6] = {0, 55};   
    Space_To_Array_Index_Map[7] = {4, 6};   
    Space_To_Array_Index_Map[8] = {2, 18};   
    Space_To_Array_Index_Map[9] = {0, 25};   
    Space_To_Array_Index_Map[10] = {2, 36};   
    Space_To_Array_Index_Map[11] = {0, 42};   
    Space_To_Array_Index_Map[12] = {2, 48};   
    Space_To_Array_Index_Map[13] = {6, 1};   
    Space_To_Array_Index_Map[14] = {6, 18};   
    Space_To_Array_Index_Map[15] = {4, 24};   
    Space_To_Array_Index_Map[16] = {6, 30};   
    Space_To_Array_Index_Map[17] = {6, 67};   
    Space_To_Array_Index_Map[18] = {8, 7};   
    Space_To_Array_Index_Map[19] = {8, 18};   
    Space_To_Array_Index_Map[20] = {8, 24};   
    Space_To_Array_Index_Map[21] = {6, 42};   
    Space_To_Array_Index_Map[22] = {8, 48};   
    Space_To_Array_Index_Map[23] = {8, 62};   
    Space_To_Array_Index_Map[24] = {10, 12};   
    Space_To_Array_Index_Map[25] = {10, 18};   
    Space_To_Array_Index_Map[26] = {8, 36};   
    Space_To_Array_Index_Map[27] = {10, 42};   
    Space_To_Array_Index_Map[28] = {10, 49};   
    Space_To_Array_Index_Map[29] = {10, 60};   
    Space_To_Array_Index_Map[30] = {10, 31};   
    Space_To_Array_Index_Map[31] = {10, 37};   
    Space_To_Array_Index_Map[32] = {10, 55};   

    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)] = Dracula::Get_Instance();
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)] = new Dracula_Sister(1);
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)] = new Dracula_Sister(2);
    Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)] = new Dracula_Sister(3);

    sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)] = Sherlock::Get_Instance();
    sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)] = Watson::Get_Instance();

    dracula_deck={cards::FEEDING_FRENZY,cards::FEEDING_FRENZY,cards::MISTFORM,cards::MISTFORM,cards::AMBUSH,cards::AMBUSH,cards::BAPTISM_OF_BLOOD,cards::BAPTISM_OF_BLOOD,cards::BEASTFORM,cards::BEASTFORM,cards::DASH,cards::DASH,cards::DASH
    ,cards::EXPLOIT,cards::EXPLOIT,cards::EXPLOIT,cards::LOOK_INTO_MY_EYES,cards::LOOK_INTO_MY_EYES,cards::LOOK_INTO_MY_EYES,cards::PREY_UPON,cards::PREY_UPON,
    cards::RAVENING_SEDUCTION,cards::RAVENING_SEDUCTION,cards::RAVENING_SEDUCTION,cards::THIRST_FOR_SUSTENANCE,cards::THIRST_FOR_SUSTENANCE,cards::THIRST_FOR_SUSTENANCE,cards::FEINT,cards::FEINT,cards::FEINT};
    sherlock_deck={cards::AMINISTER_AID,cards::AMINISTER_AID,cards::CONFIRM_SUSPICION,cards::CONFIRM_SUSPICION,cards::CONFIRM_SUSPICION,cards::COUNTERPUNCH,cards::COUNTERPUNCH,cards::COUNTERPUNCH,cards::DEDUCE_STRATEGY,cards::DEDUCE_STRATEGY,cards::DEDUCE_STRATEGY
    ,cards::EDUCATION_NEVER_ENDS,cards::EDUCATION_NEVER_ENDS,cards::ELEMENTARY,cards::ELEMENTARY,cards::ELIMINATE_THE_IMPOSSIBLE,cards::ELIMINATE_THE_IMPOSSIBLE
    ,cards::FEINT,cards::FEINT,cards::FEINT,cards::FIXED_POINT_IN_A_CHANGING_AGE,cards::FIXED_POINT_IN_A_CHANGING_AGE,cards::MASTER_OF_DISGUISE,cards::MASTER_OF_DISGUISE,cards::THE_GAME_IS_AFOOT,cards::THE_GAME_IS_AFOOT,cards::SERVICE_REVOLVER,cards::SERVICE_REVOLVER,cards::STUDY_METHODS,cards::STUDY_METHODS};

    std::random_device rd;
    std::mt19937 random_number_generator(rd());
    
    //shuffling the deck
    for(int i = 0 ; i < 3 ; i++)
    {
        std::shuffle(dracula_deck.begin(), dracula_deck.end(), random_number_generator);
        std::shuffle(sherlock_deck.begin(), sherlock_deck.end(), random_number_generator);
    }

    Who_Won_The_Combat = USER::NONE;

}

void Controller::Set_Who_Has_Won_The_Combat_Variable(USER user)
{
    Who_Won_The_Combat = user;
}


void Controller::Set_User1_And_User2_Info(const User1_And_User2_Info& info_struct) 
{
    //user1 info
    user1.Set_Hero_Name_String(info_struct.User1_Hero_Name);
    user1.Set_Hero_Name_Type(info_struct.User1_Hero_Type);
    user1.Set_Age(info_struct.User1_Age);
    user1.Set_Name(info_struct.User1_Name);
    
    //user2 info
    user2.Set_Hero_Name_String(info_struct.User2_Hero_Name);
    user2.Set_Hero_Name_Type(info_struct.User2_Hero_Type);
    user2.Set_Age(info_struct.User2_Age);
    user2.Set_Name(info_struct.User2_Name);
}

void Controller::Fill_Users_Info_Struct(User1_And_User2_Info& info_struct) const
{
    info_struct.User1_Age = user1.Return_User_Age();
    info_struct.User1_Hero_Name = user1.Return_Hero_Name_String();
    info_struct.User1_Hero_Type = user1.Return_Hero_Type();
    info_struct.User1_Name = user1.Return_UserName();
    
    info_struct.User2_Age = user2.Return_User_Age();
    info_struct.User2_Hero_Name = user2.Return_Hero_Name_String();
    info_struct.User2_Hero_Type = user2.Return_Hero_Type();
    info_struct.User2_Name = user2.Return_UserName();

}


Controller::~Controller()
{
    Dracula::Destroy_Object();
    Watson::Destroy_Object();
    Sherlock::Destroy_Object();
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)];
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)];
    delete Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)];
}


CARD_EFFECT_TYPE Controller::Return_Selected_Card_Effect_Type(USER user_turn, int index)
{
    CARD_EFFECT_TYPE to_be_returned;
    if(user_turn == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->get_effect();
    }
    else
    {
        to_be_returned = User2_Hand[index]->get_effect();
    }
    return to_be_returned;
}

std::string Controller::Get_Card_Immediate_Result_Log(USER user_turn, int index)
{
    std::string to_be_returned;
    if(user_turn == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->Get_Card_Effect_Log();
    }
    else
    {
        to_be_returned = User2_Hand[index]->Get_Card_Effect_Log();
    }
    return to_be_returned;
}

cards Controller::Return_Selected_Card_Name_As_An_Enum(USER user_turn, int index)
{
    cards to_be_returned;
    if(user_turn == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->Get_Card_Name_Enum();
    }
    else
    {
        to_be_returned = User2_Hand[index]->Get_Card_Name_Enum();
    }
    return to_be_returned;
}

ftxui::Element Controller::Return_A_Single_Card_Graphical_Representation(USER user_turn, int selected_card)
{
    ftxui::Element element_to_be_returned;


    if(selected_card == -1)
    {
        element_to_be_returned = ftxui::vbox({ftxui::text("EMPTY SELECTION")}) | ftxui::border;
        return element_to_be_returned;
    }

    if(user_turn == USER::USER1 )
    {

        

        element_to_be_returned = ftxui::vbox({
            
            ftxui::text(User1_Hand[selected_card]->get_card_name()) | ftxui::center,
            ftxui::hbox({ftxui::text("OWNER: "), ftxui::text(User1_Hand[selected_card]->Get_Card_Owner_Name_As_String())}),
            ftxui::hbox({ftxui::text("CARD VALUE: "), ftxui::text(std::to_string(User1_Hand[selected_card]->get_card_value()))}),
            ftxui::hbox({ftxui::text("CARD BOOST VALUE: "), ftxui::text(std::to_string(User1_Hand[selected_card]->get_Card_Boost_Value()))}),
            ftxui::hbox({ftxui::text("CARD TYPE: "), ftxui::text(User1_Hand[selected_card]->Get_Card_Type_As_String())}),
            ftxui::separator(),
            ftxui::paragraph(User1_Hand[selected_card]->Get_Card_Effect_As_String())
            
        }) | ftxui::border;
    }
    else if(user_turn == USER::USER2)
    {
        element_to_be_returned = ftxui::vbox({
            
            ftxui::text(User2_Hand[selected_card]->get_card_name()) | ftxui::center,
            ftxui::hbox({ftxui::text("OWNER: "), ftxui::text(User2_Hand[selected_card]->Get_Card_Owner_Name_As_String())}),
            ftxui::hbox({ftxui::text("CARD VALUE: "), ftxui::text(std::to_string(User2_Hand[selected_card]->get_card_value()))}),
            ftxui::hbox({ftxui::text("CARD BOOST VALUE: "), ftxui::text(std::to_string(User2_Hand[selected_card]->get_Card_Boost_Value()))}),
            ftxui::hbox({ftxui::text("CARD TYPE: "), ftxui::text(User2_Hand[selected_card]->Get_Card_Type_As_String())}),
            ftxui::separator(),
            ftxui::paragraph(User2_Hand[selected_card]->Get_Card_Effect_As_String())
            
        }) | ftxui::border;
    }
    
    return element_to_be_returned;
}

void Controller::Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct) const
{
    Fighter_Base_Class* Base_Fighter_Class_Pointer = nullptr;

    switch (fighter_name)
    {
        case Fighters_Names::DRACULA:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)];
            break;
                
        case Fighters_Names::SHERLOCK:
            Base_Fighter_Class_Pointer = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)];
            break;
                
        case Fighters_Names::WATSON:
            Base_Fighter_Class_Pointer = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)];
            break;
                
        case Fighters_Names::SIS1:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)];
            break;
            
        case Fighters_Names::SIS2:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)];
            break;

        case Fighters_Names::SIS3:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)];
            break;
        
    }
    info_struct.Current_Hp = Base_Fighter_Class_Pointer->Return_Fighter_Current_Hp();
    info_struct.Initial_Hp = Base_Fighter_Class_Pointer->Return_Fighter_Initial_Hp();
    info_struct.Move_Value = Base_Fighter_Class_Pointer->Return_Fighter_Current_Move_Value();
    info_struct.Range = Base_Fighter_Class_Pointer->Return_Fighter_Attacking_Range();
}

HERO_NAME Controller::Return_Younger_Hero_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user2.Return_Hero_Type();
    }
    return user1.Return_Hero_Type();
}

void Controller::Set_Fighter_Space_Number(Fighters_Names fighter_name, int new_space) 
{
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SHERLOCK:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::WATSON:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS1:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS2:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::SIS3:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    default:
        break;
    }
}

void Controller::Convert_Space_Number_To_Row_And_Column_Index(int space_number, Space_Row_And_Column_In_Array& info_struct)
{
    if(space_number < 1 || space_number > 32 )
    {
        return;
    }
    info_struct.column_index = Space_To_Array_Index_Map[space_number].column_index;
    info_struct.row_index = Space_To_Array_Index_Map[space_number].row_index;
} 

int Controller::Return_Hero_Space_Number(Fighters_Names fighter_name) const
{
    switch (fighter_name)
    {
            
        case Fighters_Names::DRACULA:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS1:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS2:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SIS3:
            return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Return_Fighter_Current_Space();
            
        
        case Fighters_Names::SHERLOCK:
            return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Space();
            
            
        case Fighters_Names::WATSON:
            return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Space();
           
    }
    return -1;
}

bool Controller::Is_User_Hand_Empty(USER user_turn)
{
    if(user_turn == USER::USER1)
    {
       return User1_Hand.empty();
    }
    else
    {
        return User2_Hand.empty();
    }
}

std::string Controller::Conver_Fighter_Name_Enum_To_String(Fighters_Names fighter_name)
{
    std::string to_be_returned;
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        to_be_returned = "DRACULA";
        break;
    
    case Fighters_Names::SIS1:
        to_be_returned = "SISTER1";
        break;
    
    case Fighters_Names::SIS2:
        to_be_returned = "SISTER2";
        break;
    
    case Fighters_Names::SIS3:
        to_be_returned = "SISTER3";
        break;
    
    case Fighters_Names::SHERLOCK:
        to_be_returned = "SHERLOCK";
        break;
    
    case Fighters_Names::WATSON:
        to_be_returned = "WATSON";
        break;
    
    }
    return to_be_returned;
}

void Controller::Boost_Fighter_Move_Value(Fighters_Names fighter_name, int boost_value)
{
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Boost_Move_Value(boost_value);
        break;
    
    case Fighters_Names::SIS1:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Boost_Move_Value(boost_value);
        break;
    
    case Fighters_Names::SIS2:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Boost_Move_Value(boost_value);
        break;
    
    case Fighters_Names::SIS3:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Boost_Move_Value(boost_value);
        break;
    
    case Fighters_Names::SHERLOCK:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Boost_Move_Value(boost_value);
        break;
    
    case Fighters_Names::WATSON:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Boost_Move_Value(boost_value);
        break;
    
    }
}

void Controller::Reset_Fighter_Move_Value(Fighters_Names fighter_name)
{
        switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Reset_Move_Value();
        break;
    
    case Fighters_Names::SIS1:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Reset_Move_Value();
        break;
    
    case Fighters_Names::SIS2:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Reset_Move_Value();
        break;
    
    case Fighters_Names::SIS3:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Reset_Move_Value();
        break;
    
    case Fighters_Names::SHERLOCK:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Reset_Move_Value();
        break;
    
    case Fighters_Names::WATSON:
        sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Reset_Move_Value();
        break;
    
    }
}

void Controller::Set_Younger_User_Variable_Value()
{
    if(user1.Return_User_Age() > user2.Return_User_Age())
    {
        Younger_User = USER::USER2;
    }
    else
    {
        Younger_User = USER::USER1;
    }
    User_Turn = Younger_User;
}

void Controller::Change_User_Turn()
{
    if(User_Turn == USER::USER1)
    {
        User_Turn = USER::USER2;
    }
    else if(User_Turn == USER::USER2)
    {
        User_Turn = USER::USER1;
    }
}

int Controller::Return_card_Value(USER user_turn, int index)
{
    int to_be_returned;

    if(user_turn == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->get_card_value();
    }
    else if (user_turn == USER::USER2)
    {
        to_be_returned = User2_Hand[index]->get_card_value();
    }
    return to_be_returned;
}

void Controller::Disable_Card_Effect(USER user, int index)
{
    if(user == USER::USER1)
    {
        User1_Hand[index]->Disable_Card_Effect_Boolian();
    }
    else
    {
        User2_Hand[index]->Disable_Card_Effect_Boolian();
    }
}

USER Controller::Return_User_Turn() const
{
    return User_Turn;
}

USER Controller::Return_Younger_User() const
{
    return Younger_User;
}

USER Controller::Return_Older_User() const
{
    if(Return_Younger_User() == USER::USER1)
    {
        return USER::USER2;
    }
    else
    {
        return USER::USER1;
    }
}

std::string Controller::Return_Older_User_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user1.Return_UserName();
    }
    return user2.Return_UserName();
}

std::string Controller::Return_Younger_User_Name() const
{
    if(std::stoi(user1.Return_User_Age()) > std::stoi(user2.Return_User_Age()))
    {
        return user2.Return_UserName();
    }
    return user1.Return_UserName();
}

int Controller::Return_Fighter_Move_Value(Fighters_Names fighter_name) const
{
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Return_Fighter_Current_Move_Value();
    
    case Fighters_Names::SIS1:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SIS2:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SIS3:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Return_Fighter_Current_Move_Value();
        
    case Fighters_Names::SHERLOCK:
        return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Move_Value();
    case Fighters_Names::WATSON:
        return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Move_Value();
        
    }   
    return -1;
}

void Controller::Set_Current_User_Action(USER_ACTION user_action)
{
    this->current_user_action = user_action;
}


bool Controller::Manage_UserAction_Numbers_And_Return_True_TO_Change_Turn()
{
    switch (current_user_action)
    {
    case USER_ACTION::USER1_ACTION1:
        current_user_action = USER_ACTION::USER1_ACTION2;
        return false;
    
    case USER_ACTION::USER2_ACTION1:
        current_user_action = USER_ACTION::USER2_ACTION2;
        return false;
    
    case USER_ACTION::USER1_ACTION2:
        current_user_action = USER_ACTION::USER2_ACTION1;
        return true;
    
    case USER_ACTION::USER2_ACTION2:
        current_user_action = USER_ACTION::USER1_ACTION1;
        return true;
    
    }
    return false;
}
bool Controller::Return_Is_Fighter_Alive(Fighters_Names name) const
{
    switch (name)
    {
    case Fighters_Names::DRACULA:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SIS1:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SIS2:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SIS3:
        return Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SHERLOCK:
        return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->return_is_fighter_alive();
        break;
    case Fighters_Names::WATSON:
        return sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->return_is_fighter_alive();
        break;
    }
    return false;
}

std::string Controller::Return_User1_Username() const
{
    return user1.Return_UserName();
}
std::string Controller::Return_User2_Username() const
{
    return user2.Return_UserName();
}

HERO_NAME Controller::Return_User1_Hero_Name() const
{
    return user1.Return_Hero_Type();
}
HERO_NAME Controller::Return_User2_Hero_Name() const
{
    return user2.Return_Hero_Type();
}

void Controller::Initialize_Users_hands()
{
    if(user1.Return_Hero_Type() == HERO_NAME::DRACULA )
    {
        for(int i = 0 ; i < 5 ; i++)
        {
            user1.user_draw(dracula_deck.back());
            Instantiate_Card_Object(USER::USER1, dracula_deck.back());
            dracula_deck.pop_back();

            user2.user_draw(sherlock_deck.back());
            Instantiate_Card_Object(USER::USER2, sherlock_deck.back());
            sherlock_deck.pop_back();
        }
    }
    else
    {
        for(int i = 0 ; i < 5 ; i++)
        {
            user1.user_draw(sherlock_deck.back());
            Instantiate_Card_Object(USER::USER1, sherlock_deck.back());
            sherlock_deck.pop_back();

            user2.user_draw(dracula_deck.back());
            Instantiate_Card_Object(USER::USER2, dracula_deck.back());
            dracula_deck.pop_back();
        }

    }
}

void Controller::Instantiate_Card_Object(USER user, cards card_name)
{
    if(dracula_deck.empty())
    {
        return;
    }
    if(sherlock_deck.empty())
    {
        return;
    }
    Card_Base_Class* temp_card_ptr = nullptr;
    HERO_NAME user_hero;
    if(user == USER::USER1)
    {
        user_hero = user1.Return_Hero_Type();            
    }
    else
    {
        user_hero = user2.Return_Hero_Type();
    }

    if(user_hero == HERO_NAME::DRACULA)
    {
        switch (dracula_deck.back())
        {
        case cards::FEEDING_FRENZY: 
            temp_card_ptr = new dracula_feedingfrenzy;
            break;
        
        case cards::MISTFORM : 
            temp_card_ptr = new dracula_mistform;
            break;
        
        case cards::AMBUSH : 
            temp_card_ptr = new dracula_ambush;
            break;
        
        case cards::BAPTISM_OF_BLOOD : 
            temp_card_ptr = new dracula_baptism_of_blood;
            break;
        
        case cards::BEASTFORM : 
            temp_card_ptr = new dracula_beastform;
            break;
        
        case cards::DASH : 
            temp_card_ptr = new dracula_dash;
            break;
        
        case cards::EXPLOIT : 
            temp_card_ptr = new dracula_exploit;
            break;
        
        case cards::LOOK_INTO_MY_EYES : 
            temp_card_ptr = new dracula_look_into_my_eyes;
            break;
        
        case cards::PREY_UPON : 
            temp_card_ptr = new dracula_prey_upon;
            break;
        
        case cards::RAVENING_SEDUCTION : 
            temp_card_ptr = new dracula_ravening_seduction;
            break;
        
        case cards::THIRST_FOR_SUSTENANCE : 
            temp_card_ptr = new dracula_thirst_For_sustenance;
            break;
        
        case cards::FEINT : 
            temp_card_ptr = new feint;
            break;
        }
    }
    else
    {
        switch (sherlock_deck.back())
        {
        case cards::AMINISTER_AID :
            temp_card_ptr = new holmes_administer_aid;
            break;
        case cards::CONFIRM_SUSPICION :
            temp_card_ptr = new holmes_confirm_suspicion;
            break;
        case cards::COUNTERPUNCH :
            temp_card_ptr = new holmes_counterpunch;
            break;
        case cards::DEDUCE_STRATEGY :
            temp_card_ptr = new holmes_deduce_strategy;
            break;
        case cards::EDUCATION_NEVER_ENDS :
            temp_card_ptr = new holmes_education_never_ends;
            break;
        case cards::ELEMENTARY :
            temp_card_ptr = new holmes_elementary;
            break;
        case cards::ELIMINATE_THE_IMPOSSIBLE :
            temp_card_ptr = new holmes_eliminate_the_impossible;
            break;
        case cards::FEINT :
            temp_card_ptr = new feint;
            break;
        case cards::FIXED_POINT_IN_A_CHANGING_AGE :
            temp_card_ptr = new holmes_fixed_point_in_a_changing_age;
            break;
        case cards::MASTER_OF_DISGUISE :
            temp_card_ptr = new holmes_master_of_disguise;
            break;
        case cards::THE_GAME_IS_AFOOT :
            temp_card_ptr = new holmes_the_game_is_afoot;
            break;
        case cards::SERVICE_REVOLVER :
            temp_card_ptr = new holmes_service_revolver;
            break;
        case cards::STUDY_METHODS :
            temp_card_ptr = new holmes_study_methods;
            break;
        
        }

        
    }
    if(user == USER::USER1)
    {
        User1_Hand.push_back(temp_card_ptr);
    }
    else
    {
        User2_Hand.push_back(temp_card_ptr);
    }

}

ftxui::Element Controller::Return_Hand_Elements_For_Render(USER user_turn)
{
    std::vector<ftxui::Element> Hand_Cards_As_Elements;
    if(user_turn == USER::USER1)
    {
        for(auto card: User1_Hand)
        {
            ftxui::Element element = ftxui::vbox({
            ftxui::text(card->get_card_name()) | ftxui::center,
            ftxui::hbox({ftxui::text("OWNER: "), ftxui::text(card->Get_Card_Owner_Name_As_String())}),
            ftxui::hbox({ftxui::text("CARD VALUE: "), ftxui::text(std::to_string(card->get_card_value()))}),
            ftxui::hbox({ftxui::text("CARD BOOST VALUE: "), ftxui::text(std::to_string(card->get_Card_Boost_Value()))}),
            ftxui::hbox({ftxui::text("CARD TYPE: "), ftxui::text(card->Get_Card_Type_As_String())}),
            ftxui::separator(),
            ftxui::paragraph(card->Get_Card_Effect_As_String())
            }) | ftxui::border;
            Hand_Cards_As_Elements.push_back(element);
        }
    }
    else
    {
        for(auto card: User2_Hand)
        {
            ftxui::Element element = ftxui::vbox({
            ftxui::text(card->get_card_name()) | ftxui::center,
            ftxui::hbox({ftxui::text("OWNER: "), ftxui::text(card->Get_Card_Owner_Name_As_String())}),
            ftxui::hbox({ftxui::text("CARD VALUE: "), ftxui::text(std::to_string(card->get_card_value()))}),
            ftxui::hbox({ftxui::text("CARD BOOST VALUE: "), ftxui::text(std::to_string(card->get_Card_Boost_Value()))}),
            ftxui::hbox({ftxui::text("CARD TYPE: "), ftxui::text(card->Get_Card_Type_As_String())}),
            ftxui::separator(),
            ftxui::paragraph(card->Get_Card_Effect_As_String())
            }) | ftxui::border;
            Hand_Cards_As_Elements.push_back(element);
        }
    }
    return ftxui::hbox({Hand_Cards_As_Elements});
}

std::vector<std::string> Controller::Return_Hand_As_String(USER user_turn)
{
    std::vector<std::string> To_Be_Returned;
    if(user_turn == USER::USER1)
    {
        for(auto card : User1_Hand)
        {
            To_Be_Returned.push_back(card->get_card_name());
        }
    }
    else
    {
        for(auto card : User2_Hand)
        {
            To_Be_Returned.push_back(card->get_card_name());
        }
    }
    return To_Be_Returned;
}

bool Controller::Is_Selected_Card_A_Scheme_Card(USER user_turn, int index)
{
    if(user_turn == USER::USER1)
    {
        if(User1_Hand[index]->get_type() == CARD_TYPE::SCHEME)
        {
            return true;
        }
    }
    else
    {
        if(User2_Hand[index]->get_type() == CARD_TYPE::SCHEME)
        {
            return true;
        }
    }
    return false;
}
int Controller::return_card_boost_value(int card,USER user_turn)
{
    if (user_turn==USER::USER1)
    {
        return User1_Hand[card]->get_Card_Boost_Value();
    }
    else if (user_turn==USER::USER2)
    {
        return User2_Hand[card]->get_Card_Boost_Value();
    }
    throw std::logic_error("Invalid user when returning card boost value");
}
void Controller::discard(int card,USER user_turn)
{
    if (user_turn==USER::USER1)
    {
        if(card < 0 || card >= static_cast<int>(User1_Hand.size()))
        {
            return;
        }
        delete User1_Hand[card];
        User1_Hand.erase(User1_Hand.begin() + card);
        user1.user_discard(card);
    }
    else if (user_turn==USER::USER2)
    {
        if(card < 0 || card >= static_cast<int>(User2_Hand.size()))
        {
            return;
        }
        delete User2_Hand[card];
        User2_Hand.erase(User2_Hand.begin()+card);
        user2.user_discard(card);
    }
}

void Controller::Draw_Card_For_User(USER user_turn, cards card)
{
    if(user_turn == USER::USER1)
    {
        user1.user_draw(card);
    }
    else if(user_turn == USER::USER2)
    {
        user2.user_draw(card);
    }
}

void Controller::draw(USER user)
{
    if(user==USER::USER1)
    {   
        if (user1.Return_Hero_Type()==HERO_NAME::DRACULA)
        {
            Instantiate_Card_Object(user,dracula_deck.back());
            user1.user_draw(dracula_deck.back());
            dracula_deck.pop_back();
            return;
        }
        else if (user1.Return_Hero_Type()==HERO_NAME::SHERLOCK)
        {
            Instantiate_Card_Object(user,sherlock_deck.back());
            user1.user_draw(sherlock_deck.back());
            sherlock_deck.pop_back();
            return;
        }
    }
    else if(user==USER::USER2)
    {   
        if (user2.Return_Hero_Type()==HERO_NAME::DRACULA)
        {
            Instantiate_Card_Object(user,dracula_deck.back());
            user2.user_draw(dracula_deck.back());
            dracula_deck.pop_back();
            return;
        }
        else if (user2.Return_Hero_Type()==HERO_NAME::SHERLOCK)
        {
            Instantiate_Card_Object(user,sherlock_deck.back());
            user2.user_draw(sherlock_deck.back());
            sherlock_deck.pop_back();
            return;
        }
    }
}

void Controller::change_fighter_health(Fighters_Names fighter ,int amount)
{
    switch (fighter)
    {
    case Fighters_Names::DRACULA :
        Dracula_And_Sisters[0]->change_health(amount);
        break;
    case Fighters_Names::SIS1 :
        Dracula_And_Sisters[1]->change_health(amount);
        break;
    case Fighters_Names::SIS2 :
        Dracula_And_Sisters[2]->change_health(amount);
        break;
    case Fighters_Names::SIS3 :
        Dracula_And_Sisters[3]->change_health(amount);
        break;
    case Fighters_Names::SHERLOCK :
        sherlock_And_Watson[0]->change_health(amount);
        break;
    case Fighters_Names::WATSON :
        sherlock_And_Watson[1]->change_health(amount);
        break;
    default:
        break;
    }
    
    
}

ftxui::Element Controller::Return_Hand_Elements_For_Boost_Screen_Render(int selected_card_for_boost)
{
    std::vector<Card_Base_Class*> temp_vector;
    if(User_Turn == USER::USER1)
    {
        temp_vector = User1_Hand;
    }
    else
    {
        temp_vector = User2_Hand;
    }

    temp_vector.erase(temp_vector.begin() + selected_card_for_boost);
    std::vector<ftxui::Element> temp_element_vector;
    for(auto card : temp_vector)
    {
        ftxui::Element element = ftxui::vbox({
        ftxui::text(card->get_card_name()) | ftxui::center,
        ftxui::hbox({ftxui::text("OWNER: "), ftxui::text(card->Get_Card_Owner_Name_As_String())}),
        ftxui::hbox({ftxui::text("CARD VALUE: "), ftxui::text(std::to_string(card->get_card_value()))}),
        ftxui::hbox({ftxui::text("CARD BOOST VALUE: "), ftxui::text(std::to_string(card->get_Card_Boost_Value()))}),
        ftxui::hbox({ftxui::text("CARD TYPE: "), ftxui::text(card->Get_Card_Type_As_String())}),
        ftxui::separator(),
        ftxui::paragraph(card->Get_Card_Effect_As_String())
        }) | ftxui::border;
        temp_element_vector.push_back(element);
    }
    return ftxui::hbox({temp_element_vector});

}

std::vector<Card_Base_Class*> Controller::Return_A_Copy_Of_User_Hand(USER user_turn)
{
    if(user_turn == USER::USER1)
    {
        return User1_Hand;
    }
    else if(user_turn == USER::USER2)
    {
        return User2_Hand;
    }
    return {};
}

CARD_TYPE Controller::Return_Selected_Card_Type(USER user_turn, int index)
{
    if(user_turn == USER::USER1)
    {
        return User1_Hand[index]->get_type();
    }
    else if(user_turn == USER::USER2)
    {
        return User2_Hand[index]->get_type();
    }
    throw std::logic_error("Invalid user when returning selected card type");
}

void Controller::Set_Selected_Enemy(Fighters_Names selected_enemy)
{
    Selected_Enemy_Hero = selected_enemy;
}

Fighters_Names Controller::Get_Selected_Enemy()
{
    return Selected_Enemy_Hero;
}

Fighters_Names Controller::Return_Fighter_Base_On_Space_Number(int space_number)
{
    Fighters_Names return_if_not_found = Fighters_Names::NONE;
    for(auto fighter : Dracula_And_Sisters)
    {
        if(fighter->Return_Fighter_Current_Space() == space_number)
        {
            return fighter->Get_Fighter_Name();
             
        }
    }
    for(auto fighter : sherlock_And_Watson)
    {
        if(fighter->Return_Fighter_Current_Space() == space_number)
        {
            return fighter->Get_Fighter_Name();
        }
    }
    return return_if_not_found;
    
}

ATTACKING_RANGE Controller::Return_Fighter_Attacking_Range(Fighters_Names selected_fighter)
{
    HERO_NAME user_hero;
    ATTACKING_RANGE to_be_returned;
    if(User_Turn == USER::USER1)
    {
        user_hero = user1.Return_Hero_Type();
    }
    else if(User_Turn == USER::USER2)
    {
        user_hero = user2.Return_Hero_Type();
    }

    if(user_hero == HERO_NAME::DRACULA)
    {
        switch (selected_fighter)
        {
        case Fighters_Names::DRACULA:
            to_be_returned = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        case Fighters_Names::SIS1:
            to_be_returned = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        case Fighters_Names::SIS2:
            to_be_returned = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        case Fighters_Names::SIS3:
            to_be_returned = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        }
    }
    else
    {
        switch (selected_fighter)
        {
        case Fighters_Names::SHERLOCK:
            to_be_returned = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        case Fighters_Names::WATSON:
            to_be_returned = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Attacking_Range_Enum_Type();
            break;
        
        }
    }
    return to_be_returned;
}

void Controller::Set_User_Turn(USER user_turn)
{
    this->User_Turn = user_turn;
}

std::string Controller::Return_Card_Name(USER user_turn, int index)
{
    std::string to_be_returned;
    if(user_turn == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->get_card_name();
    }
    else if(user_turn == USER::USER2)
    {   
        to_be_returned = User2_Hand[index]->get_card_name();
    }
    return to_be_returned;
}

bool Controller::Should_Card_Effect_Be_Executed(USER user, int index)
{
    bool to_be_returned;
    if(user == USER::USER1)
    {
        to_be_returned = User1_Hand[index]->Is_Card_Effect_Available();
    }
    else
    {
        to_be_returned = User2_Hand[index]->Is_Card_Effect_Available();
    }
    return to_be_returned;

}

void Controller::Call_Card_Effect_Function(USER user_turn, cards card_name, int index, Fighters_Names selected_enemy, int choice,int selected_card)
{
    std::vector<Card_Base_Class*>* pointer_to_user_hand;
    if(user_turn == USER::USER1)
    {
        pointer_to_user_hand = &User1_Hand;
    }
    else if(user_turn == USER::USER2)
    {
        pointer_to_user_hand = &User2_Hand;
    }

    if(!(*pointer_to_user_hand)[index]->Is_Card_Effect_Available())
    {
        return;
    }

    switch (card_name)
    {
    case cards::AMBUSH:
    {
        dracula_ambush* ptr = nullptr;
        ptr = dynamic_cast<dracula_ambush*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for ambush card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    case cards::AMINISTER_AID:
    {
        holmes_administer_aid* ptr = nullptr;
        ptr = dynamic_cast<holmes_administer_aid*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for aminister aid card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    case cards::BAPTISM_OF_BLOOD:
    {
        dracula_baptism_of_blood* ptr = nullptr;
        ptr = dynamic_cast<dracula_baptism_of_blood*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for baptism of blood card"); 
        }
            ptr->card_effect((*this));
        break;
    }
    
    case cards::BEASTFORM:
    {
        dracula_beastform* ptr = nullptr;
        ptr = dynamic_cast<dracula_beastform*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for beastform card"); 
        }
        ptr->card_effect((*this));
        break;
    }
    
    case cards::CONFIRM_SUSPICION:
    {
        holmes_confirm_suspicion* ptr = nullptr;
        ptr = dynamic_cast<holmes_confirm_suspicion*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for confirm suspicion card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::COUNTERPUNCH:
    {
        holmes_counterpunch* ptr = nullptr;
        ptr = dynamic_cast<holmes_counterpunch*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for holmes counter punsh card"); 
        }
        if(selected_enemy == Fighters_Names::NONE)
        {
            throw std::logic_error("no enemy has been selected for the card effect");
        }
        ptr->card_effect((*this), selected_enemy, user_turn);
        break;

    }
    
    case cards::DASH:
    {
        dracula_dash* ptr = nullptr;
        ptr = dynamic_cast<dracula_dash*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula dash card"); 
        }
        ptr->card_effect((*this));
        break;
    }
    
    case cards::DEDUCE_STRATEGY:
    {
        holmes_deduce_strategy* ptr = nullptr;
        ptr = dynamic_cast<holmes_deduce_strategy*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for deduce strategy card"); 
        }
        ptr->card_effect((*this), user_turn,selected_card);
        break;
    }
    
    case cards::EDUCATION_NEVER_ENDS:
    {
        holmes_education_never_ends* ptr = nullptr;
        ptr = dynamic_cast<holmes_education_never_ends*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for education never ends card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::ELEMENTARY:
    {
        holmes_elementary* ptr = nullptr;
        ptr = dynamic_cast<holmes_elementary*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for holems elementary card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::ELIMINATE_THE_IMPOSSIBLE:
    {
        holmes_eliminate_the_impossible* ptr = nullptr;
        ptr = dynamic_cast<holmes_eliminate_the_impossible*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for holmes eliminate the impossible card"); 
        }
        if(choice == -1)
        {
            throw std::logic_error("card has not been choosen from enemy deck");
        }
        ptr->card_effect((*this), user_turn, choice);
        break;
    }
    
    case cards::EXPLOIT:
    {
        dracula_exploit* ptr = nullptr;
        ptr = dynamic_cast<dracula_exploit*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula exploit card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::FEEDING_FRENZY:
    {
        dracula_feedingfrenzy* ptr = nullptr;
        ptr = dynamic_cast<dracula_feedingfrenzy*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for feeding frenzy card"); 
        }
        if(selected_enemy == Fighters_Names::NONE)
        {
            throw std::logic_error("no enemy has been selected for the card effect");
        }
        ptr->card_effect((*this), selected_enemy);
        break;
    }
    
    case cards::FEINT:
    {
        feint* ptr = nullptr;
        ptr = dynamic_cast<feint*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for feint card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::FIXED_POINT_IN_A_CHANGING_AGE:
    {
        holmes_fixed_point_in_a_changing_age* ptr = nullptr;
        ptr = dynamic_cast<holmes_fixed_point_in_a_changing_age*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for fixed point changing type card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }   
    
    case cards::LOOK_INTO_MY_EYES:
    {
        dracula_look_into_my_eyes* ptr = nullptr;
        ptr = dynamic_cast<dracula_look_into_my_eyes*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula look into my eyes card"); 
        }
        ptr->card_effect((*this),user_turn,selected_card);
        break;
    }
    
    case cards::MASTER_OF_DISGUISE:
    {
        holmes_master_of_disguise* ptr = nullptr;
        ptr = dynamic_cast<holmes_master_of_disguise*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for master of disguise card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }
    
    case cards::MISTFORM:
    {
        dracula_mistform* ptr = nullptr;
        ptr = dynamic_cast<dracula_mistform*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula mistform card"); 
        }
        ptr->card_effect((*this));
        break;
    }

    case cards::PREY_UPON:
    {
        dracula_prey_upon* ptr = nullptr;
        ptr = dynamic_cast<dracula_prey_upon*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula prey upon card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }    
    
    case cards::RAVENING_SEDUCTION:
    {
        dracula_ravening_seduction* ptr = nullptr;
        ptr = dynamic_cast<dracula_ravening_seduction*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula ravening seduction card"); 
        }
        ptr->card_effect();
        break;
    }    
    
    case cards::SERVICE_REVOLVER:
    {
        break;
    }    
    
    case cards::STUDY_METHODS:
    {
        holmes_study_methods* ptr = nullptr;
        ptr = dynamic_cast<holmes_study_methods*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for holmes study method card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }    
    
    case cards::THE_GAME_IS_AFOOT:
    {
        holmes_the_game_is_afoot* ptr = nullptr;
        ptr = dynamic_cast<holmes_the_game_is_afoot*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for holmes game is afoot card"); 
        }
        ptr->card_effect((*this), user_turn);
        break;
    }    
    
    case cards::THIRST_FOR_SUSTENANCE:
    {
        dracula_thirst_For_sustenance* ptr = nullptr;
        ptr = dynamic_cast<dracula_thirst_For_sustenance*>((*pointer_to_user_hand)[index]);
        if(ptr == nullptr)
        {
            throw std::logic_error("Couldn't down cast for dracula thirst for sustenance card"); 
        }
        ptr->card_effect((*this),user_turn);
        break;
    }   
    }
}

void Controller::Boost_Selected_Card_Value(USER user_turn, int index, int boost_value)
{
    if(user_turn == USER::USER1)
    {
        User1_Hand[index]->Boost_Card_Value(boost_value);
    }
    else if(user_turn == USER::USER2)
    {
        User2_Hand[index]->Boost_Card_Value(boost_value);
    }
}

Fighters_Names Controller::Return_Card_Owner_Name(USER user_turn, int index)
{
    if(user_turn == USER::USER1)
    {
        return User1_Hand[index]->get_owner();
    }
    else
    {
        return User2_Hand[index]->get_owner();
    }
}

void Controller::change_value_with_boost(USER user_turn , int card_index)
{
    if (user_turn==USER::USER1)
    {
        User1_Hand[card_index]->set_card_value(User1_Hand[card_index]->get_Card_Boost_Value());
    }
    if (user_turn==USER::USER2)
    {
        User2_Hand[card_index]->set_card_value(User2_Hand[card_index]->get_Card_Boost_Value());
    }
    
}
int Controller::get_attacker_selected_card_index()
{
    return attacker_selected_card_index;
}
int Controller::get_defender_selected_card_index()
{
    return defender_selected_card_index;
}

USER Controller::return_who_won_the_combat() const
{
    return Who_Won_The_Combat;
}

Fighters_Names Controller::Which_Fighter_Is_Currently_Selected(HERO_NAME hero_of_the_team)
{
    Fighters_Names to_be_returned;

    if(hero_of_the_team == HERO_NAME::DRACULA)
    {
        if(Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::DRACULA;
        }
        if(Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::SIS1;
        }
        if(Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::SIS2;
        }
        if(Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::SIS3;
        }
    }
    if(hero_of_the_team == HERO_NAME::SHERLOCK)
    {
        if(sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::WATSON;
        }
        if(sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Is_Fighter_Selected())
        {
            to_be_returned = Fighters_Names::SHERLOCK;
        }
    }
    return to_be_returned;
}

void Controller::Select_Fighter(Fighters_Names fighter_name)
{
    for(auto fighter : Dracula_And_Sisters)
    {
        if(fighter->Get_Fighter_Name() == fighter_name)
        {
            fighter->Select_Fighter();
            return;
        }
    }
    for(auto fighter : sherlock_And_Watson)
    {
        if(fighter->Get_Fighter_Name() == fighter_name)
        {
            fighter->Select_Fighter();
            return;
        }
    }
}

bool Controller::Is_Any_Of_Dracula_Sisters_Dead()
{
    for(int i = 0 ; i < 4 ; i++)
    {
        if(i == static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA))
        {
            continue;
        }

        if(!Dracula_And_Sisters[i]->return_is_fighter_alive())
        {
            return true;
        }
    }
    return false;
}


void Controller::Revive_The_Selected_Fighter(Fighters_Names fighter_name, int space_to_place_the_fighter_at)
{
    Fighter_Base_Class* pointer_to_the_fighter_object;
    switch (fighter_name)
    {
    case Fighters_Names::DRACULA:
        pointer_to_the_fighter_object = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)];
        break;
    
    case Fighters_Names::SIS1:
        pointer_to_the_fighter_object = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)];
        break;
    
    case Fighters_Names::SIS2:
        pointer_to_the_fighter_object = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)];
        break;
    
    case Fighters_Names::SIS3:
        pointer_to_the_fighter_object = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)];
        break;
    
    case Fighters_Names::SHERLOCK:
        pointer_to_the_fighter_object = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)];
        break;
    
    case Fighters_Names::WATSON:
        pointer_to_the_fighter_object = sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)];
        break;
    
    default:
        pointer_to_the_fighter_object = nullptr;
        break;
    }
    pointer_to_the_fighter_object->Reset_All_Info_For_Revive(space_to_place_the_fighter_at);
}

Fighters_Names Controller::Return_Dead_Sister_Number()
{
    Fighters_Names to_be_returned;
    for(int i = 0 ; i < 4 ; i++)
    {
        if(i == static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA))
        {
            continue;
        }
        if(!Dracula_And_Sisters[i]->return_is_fighter_alive())
        {
            to_be_returned = Dracula_And_Sisters[i]->Get_Fighter_Name();
            break;
        }
    }
    return to_be_returned;
}

std::vector<Fighters_Names> Controller::Return_Alive_Fighters(HERO_NAME which_crew)
{
    std::vector<Fighters_Names> to_be_returned;
    switch (which_crew)
    {
    case HERO_NAME::DRACULA:
        for(auto fighter : Dracula_And_Sisters)
        {
            if(fighter->return_is_fighter_alive())
            {
                to_be_returned.push_back(fighter->Get_Fighter_Name());
            }
        }
        break;
    
    case HERO_NAME::SHERLOCK:
        for(auto fighter : sherlock_And_Watson)
        {
            if(fighter->return_is_fighter_alive())
            {
                to_be_returned.push_back(fighter->Get_Fighter_Name());
            }
        }
        break;
    
    default:
        break;
    }
    return to_be_returned;
}

std::vector<int> Controller::Return_Sisters_Space_Numbers()
{
    std::vector<int> to_be_returned;
    for(int i = 0 ; i < 4 ; i++)
    {
        if(i == static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA))
        {
            continue;
        }
        if(Dracula_And_Sisters[i]->return_is_fighter_alive())
        {
            to_be_returned.push_back(Dracula_And_Sisters[i]->Return_Fighter_Current_Space());
        }
    }
    return to_be_returned;
}

void Controller::Set_Card_Value(USER user_turn, int card_index, int card_value)
{
    if(user_turn == USER::USER1)
    {
        User1_Hand[card_index]->set_card_value(card_value);
    }
    else
    {
        User2_Hand[card_index]->set_card_value(card_value);
    }
}

bool Controller::Does_Card_Exist_In_Hand_With_The_Corresponding_Value(USER user_turn, int card_value)
{
    if(user_turn == USER::USER1)
    {
        for(auto card : User1_Hand)
        {
            if(card->get_type() != CARD_TYPE::ATTACK  && card->get_type() != CARD_TYPE::DEFENCE)
            {
                continue;
            }
            if(card->get_card_value() == card_value)
            {
                return true;
            }
        }
    }
    else
    {
        for(auto card : User2_Hand)
        {
            if(card->get_type() != CARD_TYPE::ATTACK  && card->get_type() != CARD_TYPE::DEFENCE)
            {
                continue;
            }
            if(card->get_card_value() == card_value)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Controller::Return_Card_Indexes_That_Match_The_Given_Value(USER user_turn, int card_value)
{
    std::vector<int> to_be_returned;
    if(user_turn == USER::USER1)
    {
        for(int i = 0 ; i < User1_Hand.size() ; i++)
        {
            if(User1_Hand[i]->get_type() != CARD_TYPE::ATTACK && User1_Hand[i]->get_type() != CARD_TYPE::DEFENCE)
            {
                continue;
            }
            if(User1_Hand[i]->get_card_value() == card_value)
            {
                to_be_returned.push_back(i);
            }
        }
    }
    else
    {
        for(int i = 0 ; i < User1_Hand.size() ; i++)
        {
            if(User2_Hand[i]->get_type() != CARD_TYPE::ATTACK && User2_Hand[i]->get_type() != CARD_TYPE::DEFENCE)
            {
                continue;
            }
            if(User2_Hand[i]->get_card_value() == card_value)
            {
                to_be_returned.push_back(i);
            }
        }

    }
    return to_be_returned;
}

void Controller::Deselect_All_Selected_Fighters()
{
    for(auto fighter : Dracula_And_Sisters)
    {
        if(fighter->Is_Fighter_Selected())
        {
            fighter->Deselect_Fighter();
        }
    }
    for(auto fighter : sherlock_And_Watson)
    {
        if(fighter->Is_Fighter_Selected())
        {
            fighter->Deselect_Fighter();
        }
    }
}

bool Controller::Is_Game_Over()
{
    if(!Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->return_is_fighter_alive())
    {
        return true;
    }
    if(!sherlock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->return_is_fighter_alive())
    {
        return true;
    }
    return false;
}


USER Controller::Return_Who_won_The_Game() const
{
    HERO_NAME dead_hero_name;
    USER who_won;
    if(!Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->return_is_fighter_alive())
    {
        dead_hero_name = HERO_NAME::DRACULA;
    }
    else
    {
        dead_hero_name = HERO_NAME::SHERLOCK;
    }
    if(user1.Return_Hero_Type() == dead_hero_name)
    {
        who_won = USER::USER2;
    }
    else
    {
        who_won = USER::USER1;
    }
    return who_won;
}


void Controller::Update_Map()
{
    map_and_user_info = ftxui::paragraphAlignCenter({Return_Map_To_Be_Rendered(6, fighters_printing_info_array)}) | ftxui::border;
}

void Controller::Discard_Cards_If_Deck_Has_More_Than_7_Cards(USER user_turn)
{
    if(user_turn == USER::USER1)
    {
        if(User1_Hand.size() <= 7 )
        {
            return;
        }
        for(; User1_Hand.size() > 7 ;)
        {
            discard(0, user_turn);
        }
    }
    else
    {
        if(User2_Hand.size() <= 7)
        {
            return;
        }
        for(; User2_Hand.size() > 7 ;)
        {
            discard(0, user_turn);
        }

    }
}