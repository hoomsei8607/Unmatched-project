#include "../headers/cards.hpp"
#include "../headers/controller.hpp"
#include "../headers/User.hpp"
#include "../headers/fighters_sub_classes.hpp"
#include <ctime>

dracula_feedingfrenzy::dracula_feedingfrenzy()
{
    card_name="Feeding Frenzy";
    Card_Value=2;
    Card_Boost_Value=3;
    owner=CARD_OWNER::DRACULA;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
    card_effect_description="DURING COMBAT: This card's value is\n +1 for each sister in the same zone as\n the opposing fighter.";
}
void dracula_feedingfrenzy::card_effect(Controller& control,Fighters_Names enemy)
{
    int number_of_sisters=0;
    Graph *location =Graph::Get_Map_Graph_Pointer();
    std::array<ZONE_COLORS,3> zone_array_sister1;
    std::array<ZONE_COLORS,3> zone_array_sister2;
    std::array<ZONE_COLORS,3> zone_array_sister3;
    int sisters_number_locations[3];
    sisters_number_locations[0] = control.Return_Hero_Space_Number(Fighters_Names::SIS1);
    sisters_number_locations[1] = control.Return_Hero_Space_Number(Fighters_Names::SIS2);
    sisters_number_locations[2] = control.Return_Hero_Space_Number(Fighters_Names::SIS3);
    zone_array_sister1=location->return_zone(sisters_number_locations[0]);
    zone_array_sister2=location->return_zone(sisters_number_locations[1]);
    zone_array_sister3=location->return_zone(sisters_number_locations[2]);
    if (enemy==Fighters_Names::SHERLOCK)
    {
        int flag=0;
        std::array<ZONE_COLORS,3> zone_array_Sherlock;
        int enemy_location = (control.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
        zone_array_Sherlock=location->return_zone(enemy_location);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister1[i]==zone_array_Sherlock[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister2[i]==zone_array_Sherlock[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister3[i]==zone_array_Sherlock[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
    }
    else if (enemy==Fighters_Names::WATSON)
    {
        int flag=0;
        std::array<ZONE_COLORS,3> zone_array_Watson;
        int enemy_location =(control.Return_Hero_Space_Number(Fighters_Names::WATSON));
        zone_array_Watson=location->return_zone(enemy_location);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister1[i]==zone_array_Watson[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister2[i]==zone_array_Watson[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if(zone_array_sister3[i]==zone_array_Watson[j])
                {
                    flag=1;
                }
            } 
        }
        if (flag==1)
        {
            number_of_sisters++;
            flag=0;
        }
    }
    Card_Value+=number_of_sisters;
}
dracula_mistform::dracula_mistform()
{
    card_name="Mistform";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::DRACULA;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Place dracula in any space. \nGain 1 action";
    
}
 void dracula_mistform::card_effect(Controller& controler)
 {
    //get input from player to where to go(anywhere) and add 1 action
 }
dracula_ambush::dracula_ambush()
{
    card_name="Ambush";
    Card_Value=2;
    Card_Boost_Value=3;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
    card_effect_description="DURING COMBAT: Your opponent\n discards 1 random card. Add its BOOST\n value to this card's attack value";
}
void dracula_ambush::card_effect(Controller& controler,USER user_turn)
{
    //give the enemy user arguement
    
    int enemy_card=rand()%5;
    Card_Value+=controler.return_card_boost_value(enemy_card,user_turn);
    controler.discard(enemy_card,user_turn);

}
dracula_baptism_of_blood::dracula_baptism_of_blood()
{
    card_name="Baptism Of Blood";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::DRACULA;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Recover 2 health. Return a defeated\n sister (if any) to any space in\n dracula's zone. ";
}
void dracula_baptism_of_blood::card_effect(Controller& controler)
{
    controler.change_fighter_health(Fighters_Names::DRACULA,+2);
    int deadsisters[3]={1,1,1};
    
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS1))
    {
        deadsisters[0]=0;
    }
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS2))
    {
        deadsisters[1]=0;
    }
    if (!controler.Return_Is_Fighter_Alive(Fighters_Names::SIS3))
    {
        deadsisters[2]=0;
    }
    //get input and revive one
    
}
dracula_beastform::dracula_beastform()
{
    card_name="Beastform";
    Card_Value=6;
    Card_Boost_Value=4;
    owner=CARD_OWNER::DRACULA;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
    card_effect_description="DURING COMBAT: You may discard\n any number of cards from your hand.\n This card's value is +1 for each card\n you discard.";
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
    card_name="Dash";
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="AFTER COMBAT: Move your fighter up\n to 3 spaces.";
}
void dracula_dash::card_effect(Controller& controler)
{
    //input where to go whithin 3 spaces
}
dracula_exploit::dracula_exploit()
{
    card_name="Exploit";
    Card_Value=4;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="AFTER COMBAT: Draw 1 card.";
}
void dracula_exploit::card_effect(Controller& controler,USER user_turn)
{
    controler.draw(user_turn);
}
dracula_look_into_my_eyes::dracula_look_into_my_eyes()
{
    card_name="Look Into My Eyes";
    Card_Value=1;
    Card_Boost_Value=2;
    owner=CARD_OWNER::DRACULA;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::DEFENCE;
    card_number=3;
    card_effect_description="DURING COMBAT: Add the BOOST value\n from your opponent's attack card to\n the defense value of this card.";
}
void dracula_look_into_my_eyes::card_effect(User &user_handler)
{
    Card_Boost_Value/*+= enemy's played card*/;
}
dracula_prey_upon::dracula_prey_upon()
{
    card_name="Prey Upon";
    Card_Value=0;
    Card_Boost_Value=4;
    owner=CARD_OWNER::DRACULA;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Deal 1 damage to all opposing fighters\n adjacent to dracula. Dracula recovers\n 1 health for each damage dealt.";
}
void dracula_prey_upon::card_effect(Controller& controler,USER user_turn)
{
    int heal_number=0;
    Graph *location =Graph::Get_Map_Graph_Pointer();
    std::vector<int> fighter_space_numbers;
    int dracula_location = (controler.Return_Hero_Space_Number(Fighters_Names::DRACULA));
    int sherlock_location = (controler.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
    int watson_location = (controler.Return_Hero_Space_Number(Fighters_Names::WATSON));
    
    if (!location->Can_Fighter_Use_Attacking_Cards(user_turn,ATTACKING_RANGE::MELEE,dracula_location))
    {
        return;
    }
    if (user_turn==USER::USER1)
    {
    fighter_space_numbers=location->return_enemies_in_melee_range(USER::USER1,dracula_location);    
    }
    else if (user_turn==USER::USER2)
    {
    fighter_space_numbers=location->return_enemies_in_melee_range(USER::USER2,dracula_location);    
    }

    for (auto item:fighter_space_numbers)
    {
        if(sherlock_location==item)
        {
            controler.change_fighter_health(Fighters_Names::SHERLOCK, -1);
            heal_number++;
        }
        if (watson_location==item)
        {
            controler.change_fighter_health(Fighters_Names::WATSON,-1);
            heal_number++;
        }  
    }
    
    controler.change_fighter_health(Fighters_Names::DRACULA , +heal_number);
}
dracula_ravening_seduction::dracula_ravening_seduction()
{
    card_name="Ravening Seduction";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SISITERS;
    type=CARD_TYPE::SCHEME;
    card_number=3;
    card_effect_description="Move any fighter up to 2 spaces.\nAfter moving, deal 1 damage to\n the moved fighter for each sister\n adjacent to them.";
}
void dracula_ravening_seduction::card_effect()
{
    //move any fighter 2 spaces and 1 damage for every sister near the fighter (even the ally fighters)
}
dracula_thirst_For_sustenance::dracula_thirst_For_sustenance()
{
    card_name="Thirst For Sustenance";
    Card_Value=3;
    Card_Boost_Value=3;
    owner=CARD_OWNER::SISITERS;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=3;
    card_effect_description="AFTER COMBAT: If you won the\n combat, place Dracula in any space\n adjacent to the opposing fighter.";
}
void dracula_thirst_For_sustenance::card_effect()
{
    //if win move dracula adjacent to the enemy fighter
}
dracula_feint::dracula_feint()
{
    card_name="Feint";
    Card_Value=2;
    Card_Boost_Value=2;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::IMMEDIATE;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="IMMEDIATELY:Cancel all effects on\n your opponent's card.";
}
void dracula_feint::card_effect()
{
    
}
holmes_administer_aid::holmes_administer_aid()
{
    card_name="Administer Aid";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::WATSON;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Place Dr.Watson in a space adjacent\n to Holmes.Holmes recovers 1 health.\n Draw 1 card.";
}
void holmes_administer_aid::card_effect(Controller& controler,USER user_turn)
{
    //move doctor watson next to holmes
    controler.draw(user_turn);
    controler.change_fighter_health(Fighters_Names::SHERLOCK,+1);

}
holmes_confirm_suspicion::holmes_confirm_suspicion()
{
    card_name="Confirm Suspicion";
    Card_Value=0;
    Card_Boost_Value=1;
    owner=CARD_OWNER::SHERLOCK;
    type=CARD_TYPE::SCHEME;
    card_number=3;
    card_effect_description="Choose an opponent and name a value.\nYour opponent must choose and discard\none card matching that attack or defense\nvalue. Their hero takes damage equal to\nthe BOOST value of the discarded card.\nIf they do not have a card of the named value, they must reveal their hand instead.";
}
void holmes_confirm_suspicion::card_effect(Controller& controler,USER user_turn)
{

}
holmes_counterpunch::holmes_counterpunch()
{
    card_name="Counterpunch";
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::SHERLOCK;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="AFTER COMBAT: IF Holmes is adjacent\nto the opposing fighter, deal 2 damage\nto that fighter. ";
}
void holmes_counterpunch::card_effect(Controller& controler,Fighters_Names enemy_fighter,USER user_turn)
{
    Graph *location =Graph::Get_Map_Graph_Pointer();
    std::vector<int> fighter_space_numbers;
    int enemy_location = (controler.Return_Hero_Space_Number(enemy_fighter));
    int sherlock_location = (controler.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
    
    if (!location->Can_Fighter_Use_Attacking_Cards(user_turn,ATTACKING_RANGE::MELEE,sherlock_location))
    {
        return;
    }
    if (user_turn==USER::USER1)
    {
    fighter_space_numbers=location->return_enemies_in_melee_range(USER::USER1,sherlock_location);    
    }
    else if (user_turn==USER::USER2)
    {
    fighter_space_numbers=location->return_enemies_in_melee_range(USER::USER2,sherlock_location);    
    }

    for (auto item:fighter_space_numbers)
    {
        if(enemy_location==item)
        {
            controler.change_fighter_health(enemy_fighter, -2);
        }
    }
}
holmes_deduce_strategy::holmes_deduce_strategy()
{
    card_name="Deduce Strategy";
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::SHERLOCK;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="DURING COMBAT: You may change the\nprinted value of the opponents's card to\nits BOOST value.(if a card does not have a\nBOOST value,it is treated as 0.) ";
}
void holmes_deduce_strategy::card_effect(Controller& controler,USER user_turn)
{
    // get enemy card info and change boost value and card value
}
holmes_education_never_ends::holmes_education_never_ends()
{
    card_name="Education Never Ends";
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;\
    card_effect_description="AFTER COMBAT: if you won the\ncombat,your opponent draws 1 card.\nIf you lost the combat , you\ndraw 2 cards.";
}
void holmes_education_never_ends::card_effect(Controller& controler,USER user_turn)
{
    if (user_turn==USER::USER1)
    {
        //if(win)
            //{
            controler.draw(USER::USER2);
            //}
        //if(lose)
            //{
            controler.draw(USER::USER1);
            controler.draw(USER::USER1);
            //}
    }
    else if (user_turn==USER::USER2)
    {
        //if(win)
            //{
            controler.draw(USER::USER1);
            //}
        //if(lose)
            //{
            controler.draw(USER::USER2);
            controler.draw(USER::USER2);
            //}
    }
}
holmes_elementary::holmes_elementary()
{
    card_name="Elementary";
    Card_Value=3;
    Card_Boost_Value=3;
    owner=CARD_OWNER::SHERLOCK;
    effect=CARD_EFFECT_TYPE::DURING_COMBAT;
    type=CARD_TYPE::DEFENCE;
    card_number=2;
    card_effect_description="Play this card face up. Predict the printed\nattack value of the opponent's card.\nDURING COMBAT: if you predicted the\ncorrect value, cancel all effects on\n your opponent's card and ignore\nattack value. ";
}
void holmes_elementary::card_effect(Controller& controler,USER user_turn)
{

}
holmes_eliminate_the_impossible::holmes_eliminate_the_impossible()
{
    card_name="Eliminate The Impossible";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SHERLOCK;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Choose an opponent.Look at their\nhand and choose 1 card for them\nto discard";
}
void holmes_eliminate_the_impossible::card_effect(Controller& controler,USER user_turn,int choice)
{
    if(user_turn==USER::USER1)
    {
    controler.discard(choice,USER::USER2);
    }
    else if( user_turn==USER::USER2)
    {
    controler.discard(choice,USER::USER1);
    }
}
holmes_feint::holmes_feint()
{
    card_name="Feint";
    Card_Value=2;
    Card_Boost_Value=1;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::IMMEDIATE;
    type=CARD_TYPE::VERSATILE;
    card_number=3;
    card_effect_description="IMMEDIATELY: Cancel all effects on\nyour opponents's card.";
}
void holmes_feint::card_effect(Controller& controler,USER user_turn)
{

}
holmes_fixed_point_in_a_changing_age::holmes_fixed_point_in_a_changing_age()
{
    card_name="Fixed Point In A Changing Age";
    Card_Value=3;
    Card_Boost_Value=1;
    owner=CARD_OWNER::WATSON;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;
    card_effect_description="AFTER COMBAT: If Dr.Watson is\nadjacent to Holmes,they each\nrecover 1 health.";
}
void holmes_fixed_point_in_a_changing_age::card_effect(Controller& controler,USER user_turn)
{
    bool heal=false;
    Graph *location =Graph::Get_Map_Graph_Pointer();
    std::vector<int> fighter_space_numbers;
    int watson_location = (controler.Return_Hero_Space_Number(Fighters_Names::WATSON));
    int sherlock_location = (controler.Return_Hero_Space_Number(Fighters_Names::SHERLOCK));
    fighter_space_numbers=location->return_adjacent_allies(user_turn,sherlock_location);
    for(auto item:fighter_space_numbers)
    {
        if (watson_location==item)
        {
            controler.change_fighter_health(Fighters_Names::SHERLOCK , +1);
            controler.change_fighter_health(Fighters_Names::WATSON , +1);
        }
    }
}
holmes_master_of_disguise::holmes_master_of_disguise()
{
    card_name="Master Of Disguise";
    Card_Value=0;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SHERLOCK;
    type=CARD_TYPE::SCHEME;
    card_number=2;
    card_effect_description="Choose an opponent.Holmes swaps\nspaces wioth their hero.Deal 1 damage\nto that hero.";
}
holmes_the_game_is_afoot::holmes_the_game_is_afoot()
{
    card_name="The Game Is Afoot";
    Card_Value=5;
    Card_Boost_Value=2;
    owner=CARD_OWNER::SHERLOCK;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
    card_effect_description="AFTER COMBAT: Move Holmes\nup to 3 spaces.";
}
holmes_service_revolver::holmes_service_revolver()
{
    card_name="Service Revolver";
    Card_Value=5;
    Card_Boost_Value=3;
    owner=CARD_OWNER::WATSON;
    //effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::ATTACK;
    card_number=2;
    card_effect_description=" ";
}
holmes_study_methods::holmes_study_methods()
{
    card_name="Study Methods";
    Card_Value=3;
    Card_Boost_Value=2;
    owner=CARD_OWNER::ANY;
    effect=CARD_EFFECT_TYPE::AFTER_COMBAT;
    type=CARD_TYPE::VERSATILE;
    card_number=2;
    card_effect_description="AFTER COMBAT: if you won the\ncombat,look at your opponent's hand. ";
}