#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "space.hpp"
#include <vector>
#include <map>




class Graph // a singleton object
{
    public:
        static Graph* Get_Map_Graph_Pointer();
        void Initialize_Graph();
        ~Graph();


    private:
        static bool Is_Graph_Initiated;
        static Graph* Object_Instance;
        std::map <int, std::vector<Space>> Game_Map_Graph;//key is space number and value is the set of vetecies


};

Graph* Graph::Object_Instance = nullptr;
bool Graph::Is_Graph_Initiated = false;

#endif