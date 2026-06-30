#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "user.hpp"
#include "structs.hpp"
class Controller
{
    public:
        void Set_User1_And_User2_Info(User1_And_User2_Info info_struct);

    private:
        User user1;
        User user2;
        
};
#endif