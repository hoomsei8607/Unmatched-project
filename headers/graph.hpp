#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "space.hpp"
#include <vector>
#include <array>
#include <map>
#include <set>




class Graph // a singleton object
{
    public:
        static Graph* Get_Map_Graph_Pointer();
        void Initialize_Graph();
        std::set<int> Available_Spaces_For_Moving(int move_value,  int current_space, USER user_turn);
        void Recursive_Path_Finder(std::set<int>& paths, int current_space, int times_to_call_recursive_function, USER user_turn, int current_step = 0);// call this function with just 4 arguments
        Graph(const Graph&) = delete;
        void Change_Space_Occiupied_Status(int space_number);//if the space is empty changes to occiupied and vice versa
        std::array<ZONE_COLORS,3> return_zone(int space);
        void Set_User_Occupying_Space(USER user_occupying_space, int space_number);
        ~Graph();



    private:
        static bool Is_Graph_Initiated;
        static Graph* Object_Instance;
        Graph() = default;
        std::map <int, std::vector<Space*>> Game_Map_Graph;//key is space number and value is the set of vertecies

        //space objects
        Space s1;
        Space s2;
        Space s3;
        Space s4;
        Space s5;
        Space s6;
        Space s7;
        Space s8;
        Space s9;
        Space s10;
        Space s11;
        Space s12;
        Space s13;
        Space s14;
        Space s15;
        Space s16;
        Space s17;
        Space s18;
        Space s19;
        Space s20;
        Space s21;
        Space s22;
        Space s23;
        Space s24;
        Space s25;
        Space s26;
        Space s27;
        Space s28;
        Space s29;
        Space s30;
        Space s31;
        Space s32;


};



#endif