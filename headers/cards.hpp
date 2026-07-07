#include "card_abstract.hpp"
#include "graph.hpp"

class dracula_feedingfrenzy : public Card_Base_Class
{
    public:
    dracula_feedingfrenzy();
    void card_effect(Controller& controler);
    
};
class dracula_mistform : public Card_Base_Class
{
    public:
    dracula_mistform();
    void card_effect(Controller& controler);
};
class dracula_ambush : public Card_Base_Class
{
    public:
    dracula_ambush();
    void card_effect(User &useerhandler);
};
class dracula_baptism_of_blood : public Card_Base_Class
{
    public:
    dracula_baptism_of_blood();
    void card_effect(Controller& controler,Fighter_Base_Class& fighters);
};
class dracula_beastform : public Card_Base_Class
{
    public:
    dracula_beastform();
    void card_effect(User &user_handler);
};
class dracula_dash : public Card_Base_Class
{
    public:
    dracula_dash();
    void card_effect(Controller& controler);
};
class dracula_exploit : public Card_Base_Class
{
    public:
    dracula_exploit();
    void card_effect(User &user_handler);
};
class dracula_look_into_my_eyes : public Card_Base_Class
{
    public:
    dracula_look_into_my_eyes();
    void card_effect(User &user_handler);
};
class dracula_prey_upon : public Card_Base_Class
{
    public:
    dracula_prey_upon();
    void card_effect(Controller& controler);
};
class dracula_ravening_seduction : public Card_Base_Class
{
    public:
    dracula_ravening_seduction();
    void card_effect();
};
class dracula_thirst_For_sustenance : public Card_Base_Class
{
    public:
    dracula_thirst_For_sustenance();
    void card_effect();
};
class dracula_feint : public Card_Base_Class
{
    public:
    dracula_feint();
    void card_effect();
};
class holmes_administer_aid : public Card_Base_Class
{
    public:
    holmes_administer_aid();
    void card_effect(User &user_handler,Fighter_Base_Class& fighters);
};
class holmes_confirm_suspicion : public Card_Base_Class
{
    public:
    holmes_confirm_suspicion();
};
class holmes_counterpunch : public Card_Base_Class
{
    public:
    holmes_counterpunch();
};
class holmes_deduce_strategy : public Card_Base_Class
{
    public:
    holmes_deduce_strategy();
};
class holmes_education_never_ends : public Card_Base_Class
{
    public:
    holmes_education_never_ends();
};
class holmes_elementary : public Card_Base_Class
{
    public:
    holmes_elementary();
};
class holmes_eliminate_the_impossible : public Card_Base_Class
{
    public:
    holmes_eliminate_the_impossible();
};
class holmes_feint : public Card_Base_Class
{
    public:
    holmes_feint();
};
class holmes_fixed_point_in_a_changing_age : public Card_Base_Class
{
    public:
    holmes_fixed_point_in_a_changing_age();
};
class holmes_master_of_disguise : public Card_Base_Class
{
    public:
    holmes_master_of_disguise();
};
class holmes_the_game_is_afoot : public Card_Base_Class
{
    public:
    holmes_the_game_is_afoot();
};
class holmes_service_revolver : public Card_Base_Class
{
    public:
    holmes_service_revolver();
};
class holmes_study_methods : public Card_Base_Class
{
    public:
    holmes_study_methods();
};