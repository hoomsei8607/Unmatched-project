#include "../headers/controller.hpp"
#include "../headers/fighters_sub_classes.hpp"
#include "../headers/structs.hpp"
#include "../headers/cards.hpp"
#include <algorithm>
#include <random>

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

    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)] = Sherlock::Get_Instance();
    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)] = Watson::Get_Instance();

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

void Controller::Fill_Fighter_Info_Struct(Fighters_Names fighter_name, Fighter_Info& info_struct) const
{
    Fighter_Base_Class* Base_Fighter_Class_Pointer = nullptr;

    switch (fighter_name)
    {
        case Fighters_Names::DRACULA:
            Base_Fighter_Class_Pointer = Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)];
            break;
                
        case Fighters_Names::SHERLOCK:
            Base_Fighter_Class_Pointer = Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)];
            break;
                
        case Fighters_Names::WATSON:
            Base_Fighter_Class_Pointer = Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)];
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
        Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Set_Current_Fighter_Space_Number(new_space);
        break;
    
    case Fighters_Names::WATSON:
        Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Set_Current_Fighter_Space_Number(new_space);
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
            return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Space();
            
            
        case Fighters_Names::WATSON:
            return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Space();
           
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

USER Controller::Return_User_Turn() const
{
    return User_Turn;
}

USER Controller::Return_Younger_User() const
{
    return Younger_User;
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
        return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->Return_Fighter_Current_Move_Value();
    case Fighters_Names::WATSON:
        return Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->Return_Fighter_Current_Move_Value();
        
    default:
        break;
    }   
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
}
bool Controller::Return_Is_Fighter_Alive(Fighters_Names name) const
{
    switch (name)
    {
    case Fighters_Names::DRACULA:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::DRACULA)]->return_is_fighter_alive();
        break;
    
    case Fighters_Names::SIS1:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS1)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SIS2:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS2)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SIS3:
        Dracula_And_Sisters[static_cast<int>(Dracula_And_Sisters_Array_Index::SIS3)]->return_is_fighter_alive();
        break;
    case Fighters_Names::SHERLOCK:
    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::SHERLOCK)]->return_is_fighter_alive();
        break;
    case Fighters_Names::WATSON:
    Sherklock_And_Watson[static_cast<int>(Sherlock_And_Watson_Array_Index::WATSON)]->return_is_fighter_alive();
        break;
    }
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
            user1.draw(dracula_deck.back());
            Instantiate_Card_Object(USER::USER1, dracula_deck.back());
            dracula_deck.pop_back();

            user2.draw(sherlock_deck.back());
            Instantiate_Card_Object(USER::USER2, sherlock_deck.back());
            sherlock_deck.pop_back();
        }
    }
    else
    {
        for(int i = 0 ; i < 5 ; i++)
        {
            user1.draw(sherlock_deck.back());
            Instantiate_Card_Object(USER::USER1, sherlock_deck.back());
            sherlock_deck.pop_back();

            user2.draw(dracula_deck.back());
            Instantiate_Card_Object(USER::USER2, dracula_deck.back());
            dracula_deck.pop_back();
        }

    }
}

void Controller::Instantiate_Card_Object(USER user, cards card_name)
{
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
            temp_card_ptr = new dracula_feint;
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
            temp_card_ptr = new holmes_feint;
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
int Controller::return_card_boost_value(int card,USER user_turn)
{
    if (user_turn==USER::USER1)
    {
        return User2_Hand[card]->get_Card_Boost_Value();
    }
    else if (user_turn==USER::USER2)
    {
        return User1_Hand[card]->get_Card_Boost_Value();
    }                           
}
void Controller::discard(int card,USER user_turn)
{
    if (user_turn==USER::USER1)
    {
        User1_Hand.erase(User1_Hand.begin()+card);
        user1.discard(card);
    }
    else if (user_turn==USER::USER2)
    {
        User2_Hand.erase(User1_Hand.begin()+card);
        user2.discard(card);
    }
    
    
}