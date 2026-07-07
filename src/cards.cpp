#include "../headers/cards.hpp"
#include "../headers/controller.hpp"
#include "../headers/User.hpp"
#include "../headers/fighters_sub_classes.hpp"
#include <ctime>

dracula_feedingfrenzy::dracula_feedingfrenzy()
{
    Card_Value=2;
    Card_Boost_Value=3;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
}
void dracula_feedingfrenzy::card_effect(Controller& control)
{
    int sisters_number_locations[3];
    sisters_number_locations[0] = control.Return_Hero_Space_Number(Fighters_Names::SIS1);
    sisters_number_locations[1] = control.Return_Hero_Space_Number(Fighters_Names::SIS2);
    sisters_number_locations[2] = control.Return_Hero_Space_Number(Fighters_Names::SIS3);
    int sherlock_location = (control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
    int watson_location =(control.Return_Hero_Space_Number(Fighters_Names::WATSON));
    //find fighter places and check for sisters to be the same zone as enemy
    
    

}
dracula_mistform::dracula_mistform()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    
}
 void dracula_mistform::card_effect(Controller& controler)
 {
    //get input from player to where to go(anywhere) and add 1 action
 }
dracula_ambush::dracula_ambush(Fighter_Base_Class &fighter)
{
    Card_Value=2;
    Card_Boost_Value=3;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
}
void dracula_ambush::card_effect(User &user_handler)
{
    //give the enemy user arguement
    srand(time(0));
    int enemy_card=rand()%5;
    Card_Value+=user_handler.user_hand[enemy_card]->get_Card_Boost_Value();
    user_handler.discard(enemy_card);

}
dracula_baptism_of_blood::dracula_baptism_of_blood()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=2;
}
void dracula_baptism_of_blood::card_effect(Controller& controler,Fighter_Base_Class& fighters)

{
    fighters.change_health(+2);
    int deadsisters[3]={0,0,0};
    
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS1))
    {
        deadsisters[0]=1;
    }
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS2))
    {
        deadsisters[1]=1;
    }
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS3))
    {
        deadsisters[2]=1;
    }
    //get input and revive one
    
}
dracula_beastform::dracula_beastform()
{
    Card_Value=6;
    Card_Boost_Value=4;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
}
void dracula_beastform::card_effect(User &user_handler)
{
    int discarded_number;
    //input to choose to discard cards or not
    //if discard:
    //need discard index for calling discard
    Card_Value+=discarded_number;
}
dracula_dash::dracula_dash()
{
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
void dracula_dash::card_effect(Controller& controler)
{
    //input where to go whithin 3 spaces
}
dracula_exploit::dracula_exploit()
{
    Card_Value=4;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
void dracula_exploit::card_effect(User &user_handler)
{
    user_handler.draw();
}
dracula_look_into_my_eyes::dracula_look_into_my_eyes()
{
    Card_Value=1;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::DEFENCE;
    card_number=3;
}
void dracula_look_into_my_eyes::card_effect(User &user_handler)
{
    Card_Boost_Value/*+= enemy's played card*/;
}
dracula_prey_upon::dracula_prey_upon()
{
    Card_Value=0;
    Card_Boost_Value=4;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=2;
}
void dracula_prey_upon::card_effect(Controller& controler)
{
    int dracula_location = (controler.Return_Hero_Space_Number(Fighters_Names::DRACULA));
    int sherlock_location = (controler.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
    int watson_location =(controler.Return_Hero_Space_Number(Fighters_Names::WATSON));

}
dracula_ravening_seduction::dracula_ravening_seduction()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SIDE_KICK;
    type=CARD_TYPE::SCHEME;
    card_number=3;
}
void dracula_ravening_seduction::card_effect()
{
    //move any fighter 2 spaces and 1 damage for every sister near the fighter (even the ally fighters)
}
dracula_thirst_For_sustenance::dracula_thirst_For_sustenance()
{
    Card_Value=3;
    Card_Boost_Value=3;
    owner=CARD_OWNER::SIDE_KICK;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=3;
}
void dracula_thirst_For_sustenance::card_effect()
{
    //if win move dracula adjacent to the enemy fighter
}
dracula_feint::dracula_feint()
{
    Card_Value=2;
    Card_Boost_Value=2;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::IMMEDIATE;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
void dracula_feint::card_effect()
{
    
}
holmes_administer_aid::holmes_administer_aid()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SIDE_KICK;
    type=CARD_TYPE::SCHEME;
    card_number=2;
}
void holmes_administer_aid::card_effect(User &user_handler,Fighter_Base_Class& fighters)
{
    //move doctor watson next to holmes
    user_handler.draw();
    fighters.change_health(+1);

}
holmes_confirm_suspicion::holmes_confirm_suspicion()
{
    Card_Value=0;
    Card_Boost_Value=1;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=3;
}
holmes_counterpunch::holmes_counterpunch()
{
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
holmes_deduce_strategy::holmes_deduce_strategy()
{
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
holmes_education_never_ends::holmes_education_never_ends()
{
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;
}
holmes_elementary::holmes_elementary()
{
    Card_Value=3;
    Card_Boost_Value=3;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::DEFENCE;
    card_number=2;
}
holmes_eliminate_the_impossible::holmes_eliminate_the_impossible()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=2;
}
holmes_feint::holmes_feint()
{
    Card_Value=2;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::IMMEDIATE;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
}
holmes_fixed_point_in_a_changing_age::holmes_fixed_point_in_a_changing_age()
{
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::SIDE_KICK;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;
}
holmes_master_of_disguise::holmes_master_of_disguise()
{
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    type=CARD_TYPE::SCHEME;
    card_number=2;
}
holmes_the_game_is_afoot::holmes_the_game_is_afoot()
{
    Card_Value=5;
    Card_Boost_Value=2;
    owner=CARD_OWNER::HERO;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
}
holmes_service_revolver::holmes_service_revolver()
{
    Card_Value=5;
    Card_Boost_Value=3;
    owner=CARD_OWNER::SIDE_KICK;
    //effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
}
holmes_study_methods::holmes_study_methods()
{
    Card_Value=3;
    Card_Boost_Value=2;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;
}