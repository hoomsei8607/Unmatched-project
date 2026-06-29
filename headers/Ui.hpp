#ifndef UI_HPP
#define UI_HPP

enum class SCREEN_STATE{MENU, GAME_LOOP, GAME_OVER, PROGRAM_SHOULD_TEMINATE, NONE};

class User_Interface
{
    public:
        User_Interface();
        bool Manage_Screen();
        void Starting_Menu_Screen();
        void Game_Loop_Screen();
        // void Finished_Game_Screen();
        
    private:
        SCREEN_STATE Current_Screen_State;

};


#endif