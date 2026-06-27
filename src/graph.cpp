#include "../headers/graph.hpp"
#include "../headers/space.hpp"
Graph* Graph::Get_Map_Graph_Pointer()
{
    if(Object_Instance != nullptr)
    {
        return Object_Instance;
    }
    Object_Instance = new Graph;
    Object_Instance->Initialize_Graph();
    Is_Graph_Initiated = true;
    return Object_Instance;
}

void Graph::Initialize_Graph()
{
    if(Is_Graph_Initiated)
    {
        return;
    }

    std::array <ZONE_COLORS, 3> temp_array;
    Space temp_space_object;


    //filling the temp object with space 1 info
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, true, 1, temp_array);
    
    //adding this to the vector of any space that space 1 is connected to 
    Game_Map_Graph[2].push_back(temp_space_object);
    Game_Map_Graph[7].push_back(temp_space_object);
    //connected via secret path
    Game_Map_Graph[6].push_back(temp_space_object);
    Game_Map_Graph[16].push_back(temp_space_object);
    Game_Map_Graph[24].push_back(temp_space_object);


    //now for space 2
    temp_space_object.Set_Info(false, false, false, 2, temp_array);
    Game_Map_Graph[1].push_back(temp_space_object);
    Game_Map_Graph[9].push_back(temp_space_object);

    //space 3
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 3, temp_array);
    Game_Map_Graph[4].push_back(temp_space_object);
    Game_Map_Graph[9].push_back(temp_space_object);
    Game_Map_Graph[10].push_back(temp_space_object);
    
    //space 4
    temp_space_object.Set_Info(false, false, false, 4, temp_array);
    Game_Map_Graph[3].push_back(temp_space_object);
    Game_Map_Graph[10].push_back(temp_space_object);
    Game_Map_Graph[11].push_back(temp_space_object);

    //space 5
    temp_array = {ZONE_COLORS::YELLOW, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 5, temp_array);
    Game_Map_Graph[6].push_back(temp_space_object);
    Game_Map_Graph[11].push_back(temp_space_object);
    Game_Map_Graph[12].push_back(temp_space_object);

    //space 6
    temp_space_object.Set_Info(false, false, true, 6, temp_array);
    Game_Map_Graph[5].push_back(temp_space_object);
    //connected via secret path
    Game_Map_Graph[1].push_back(temp_space_object);
    Game_Map_Graph[16].push_back(temp_space_object);
    Game_Map_Graph[24].push_back(temp_space_object);

    //space 7
    temp_array = {ZONE_COLORS::CYAN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 7, temp_array);
    Game_Map_Graph[1].push_back(temp_space_object);
    Game_Map_Graph[8].push_back(temp_space_object);
    Game_Map_Graph[13].push_back(temp_space_object);
    
    //space 8 
    temp_space_object.Set_Info(false, false, false, 8, temp_array);
    Game_Map_Graph[7].push_back(temp_space_object);
    Game_Map_Graph[15].push_back(temp_space_object);
    
    //space 9
    temp_array = {ZONE_COLORS::CYAN, ZONE_COLORS::BROWN, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 9, temp_array);
    Game_Map_Graph[2].push_back(temp_space_object);
    Game_Map_Graph[3].push_back(temp_space_object);
    Game_Map_Graph[15].push_back(temp_space_object);
    
    //space 10
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 10, temp_array);
    Game_Map_Graph[3].push_back(temp_space_object);
    Game_Map_Graph[4].push_back(temp_space_object);
    Game_Map_Graph[11].push_back(temp_space_object);
    
    //space 11
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::GREEN, ZONE_COLORS::YELLOW};
    temp_space_object.Set_Info(true, false, false, 11, temp_array);
    Game_Map_Graph[4].push_back(temp_space_object);
    Game_Map_Graph[5].push_back(temp_space_object);
    Game_Map_Graph[10].push_back(temp_space_object);
    Game_Map_Graph[12].push_back(temp_space_object);
    Game_Map_Graph[21].push_back(temp_space_object);
    
    //space 12
    temp_array = {ZONE_COLORS::YELLOW, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 12, temp_array);
    Game_Map_Graph[5].push_back(temp_space_object);
    Game_Map_Graph[11].push_back(temp_space_object);
    Game_Map_Graph[17].push_back(temp_space_object);
    
    //space 13
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 13, temp_array);
    Game_Map_Graph[7].push_back(temp_space_object);
    Game_Map_Graph[14].push_back(temp_space_object);
    Game_Map_Graph[18].push_back(temp_space_object);
    
    //space 14
    temp_space_object.Set_Info(false, false, false, 14, temp_array);
    Game_Map_Graph[13].push_back(temp_space_object);
    Game_Map_Graph[15].push_back(temp_space_object);
    
    
    //space 15
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::CYAN, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 15, temp_array);
    Game_Map_Graph[8].push_back(temp_space_object);
    Game_Map_Graph[9].push_back(temp_space_object);
    Game_Map_Graph[14].push_back(temp_space_object);
    
    //space 16
    temp_array = {ZONE_COLORS::GREEN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, true, 16, temp_array);
    Game_Map_Graph[20].push_back(temp_space_object);
    Game_Map_Graph[21].push_back(temp_space_object);
    //via teleport
    Game_Map_Graph[1].push_back(temp_space_object);
    Game_Map_Graph[6].push_back(temp_space_object);
    Game_Map_Graph[24].push_back(temp_space_object);
    
    
    //space 17
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 17, temp_array);
    Game_Map_Graph[21].push_back(temp_space_object);
    Game_Map_Graph[23].push_back(temp_space_object);
    
    //space 18
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::PINK, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 18, temp_array);
    Game_Map_Graph[13].push_back(temp_space_object);
    Game_Map_Graph[19].push_back(temp_space_object);
    Game_Map_Graph[24].push_back(temp_space_object);
    
    //space 19
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 19, temp_array);
    Game_Map_Graph[18].push_back(temp_space_object);
    Game_Map_Graph[20].push_back(temp_space_object);
    
    //space 20
    temp_array = {ZONE_COLORS::GREEN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 20, temp_array);
    Game_Map_Graph[16].push_back(temp_space_object);
    Game_Map_Graph[19].push_back(temp_space_object);
    Game_Map_Graph[26].push_back(temp_space_object);
    
    //space 21
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 21, temp_array);
    Game_Map_Graph[11].push_back(temp_space_object);
    Game_Map_Graph[16].push_back(temp_space_object);
    Game_Map_Graph[17].push_back(temp_space_object);
    Game_Map_Graph[22].push_back(temp_space_object);
    Game_Map_Graph[27].push_back(temp_space_object);
    Game_Map_Graph[28].push_back(temp_space_object);
    
    //space 22
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 22, temp_array);
    Game_Map_Graph[21].push_back(temp_space_object);
    Game_Map_Graph[23].push_back(temp_space_object);
    
    //space 23
    temp_space_object.Set_Info(false, false, false, 23, temp_array);
    Game_Map_Graph[17].push_back(temp_space_object);
    Game_Map_Graph[22].push_back(temp_space_object);
    Game_Map_Graph[29].push_back(temp_space_object);
    
    //space 24
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, true, 24, temp_array);
    Game_Map_Graph[18].push_back(temp_space_object);
    Game_Map_Graph[25].push_back(temp_space_object);
    //via teleport
    Game_Map_Graph[1].push_back(temp_space_object);
    Game_Map_Graph[6].push_back(temp_space_object);
    Game_Map_Graph[16].push_back(temp_space_object);
    
    //space 26
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 26, temp_array);
    Game_Map_Graph[20].push_back(temp_space_object);
    Game_Map_Graph[27].push_back(temp_space_object);
    Game_Map_Graph[30].push_back(temp_space_object);
    Game_Map_Graph[31].push_back(temp_space_object);
    
    //space 27
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 27, temp_array);
    Game_Map_Graph[21].push_back(temp_space_object);
    Game_Map_Graph[26].push_back(temp_space_object);
    Game_Map_Graph[28].push_back(temp_space_object);
    Game_Map_Graph[31].push_back(temp_space_object);
    
    //space 28
    temp_space_object.Set_Info(false, false, false, 28, temp_array);
    Game_Map_Graph[21].push_back(temp_space_object);
    Game_Map_Graph[27].push_back(temp_space_object);
    Game_Map_Graph[29].push_back(temp_space_object);
    Game_Map_Graph[32].push_back(temp_space_object);
    
    //space 29
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::PURPLE, ZONE_COLORS::NON};
    temp_space_object.Set_Info(true, false, false, 29, temp_array);
    Game_Map_Graph[23].push_back(temp_space_object);
    Game_Map_Graph[28].push_back(temp_space_object);
    Game_Map_Graph[32].push_back(temp_space_object);
    

    //space 30
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    temp_space_object.Set_Info(false, false, false, 30, temp_array);
    Game_Map_Graph[25].push_back(temp_space_object);
    Game_Map_Graph[26].push_back(temp_space_object);
    Game_Map_Graph[31].push_back(temp_space_object);
    
    //space 31
    temp_space_object.Set_Info(false, false, false, 31, temp_array);
    Game_Map_Graph[26].push_back(temp_space_object);
    Game_Map_Graph[27].push_back(temp_space_object);
    Game_Map_Graph[30].push_back(temp_space_object);
    
    //space 32
    temp_space_object.Set_Info(false, false, false, 32, temp_array);
    Game_Map_Graph[28].push_back(temp_space_object);
    Game_Map_Graph[29].push_back(temp_space_object);
    
}
