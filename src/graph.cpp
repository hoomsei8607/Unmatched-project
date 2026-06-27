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
    s1.Set_Info(false, false, true, 1, temp_array);

    //adding this to the vector of any space that space 1 is connected to 
    Game_Map_Graph[2].push_back(&s1);
    Game_Map_Graph[7].push_back(&s1);
    //connected via secret path
    Game_Map_Graph[6].push_back(&s1);
    Game_Map_Graph[16].push_back(&s1);
    Game_Map_Graph[24].push_back(&s1);


    //now for space 2
    s2.Set_Info(false, false, false, 2, temp_array);
    Game_Map_Graph[1].push_back(&s2);
    Game_Map_Graph[9].push_back(&s2);

    //space 3
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s3.Set_Info(false, false, false, 3, temp_array);
    Game_Map_Graph[4].push_back(&s3);
    Game_Map_Graph[9].push_back(&s3);
    Game_Map_Graph[10].push_back(&s3);
    
    //space 4
    s4.Set_Info(false, false, false, 4, temp_array);
    Game_Map_Graph[3].push_back(&s4);
    Game_Map_Graph[10].push_back(&s4);
    Game_Map_Graph[11].push_back(&s4);

    //space 5
    temp_array = {ZONE_COLORS::YELLOW, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s5.Set_Info(false, false, false, 5, temp_array);
    Game_Map_Graph[6].push_back(&s5);
    Game_Map_Graph[11].push_back(&s5);
    Game_Map_Graph[12].push_back(&s5);

    //space 6
    s6.Set_Info(false, false, true, 6, temp_array);
    Game_Map_Graph[5].push_back(&s6);
    //connected via secret path
    Game_Map_Graph[1].push_back(&s6);
    Game_Map_Graph[16].push_back(&s6);
    Game_Map_Graph[24].push_back(&s6);

    //space 7
    temp_array = {ZONE_COLORS::CYAN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s7.Set_Info(false, false, false, 7, temp_array);
    Game_Map_Graph[1].push_back(&s7);
    Game_Map_Graph[8].push_back(&s7);
    Game_Map_Graph[13].push_back(&s7);
    
    //space 8 
    s8.Set_Info(false, false, false, 8, temp_array);
    Game_Map_Graph[7].push_back(&s8);
    Game_Map_Graph[15].push_back(&s8);
    
    //space 9
    temp_array = {ZONE_COLORS::CYAN, ZONE_COLORS::BROWN, ZONE_COLORS::NON};
    s9.Set_Info(true, false, false, 9, temp_array);
    Game_Map_Graph[2].push_back(&s9);
    Game_Map_Graph[3].push_back(&s9);
    Game_Map_Graph[15].push_back(&s9);
    
    //space 10
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s10.Set_Info(false, false, false, 10, temp_array);
    Game_Map_Graph[3].push_back(&s10);
    Game_Map_Graph[4].push_back(&s10);
    Game_Map_Graph[11].push_back(&s10);
    
    //space 11
    temp_array = {ZONE_COLORS::BROWN, ZONE_COLORS::GREEN, ZONE_COLORS::YELLOW};
    s11.Set_Info(true, false, false, 11, temp_array);
    Game_Map_Graph[4].push_back(&s11);
    Game_Map_Graph[5].push_back(&s11);
    Game_Map_Graph[10].push_back(&s11);
    Game_Map_Graph[12].push_back(&s11);
    Game_Map_Graph[21].push_back(&s11);
    
    //space 12
    temp_array = {ZONE_COLORS::YELLOW, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s12.Set_Info(false, false, false, 12, temp_array);
    Game_Map_Graph[5].push_back(&s12);
    Game_Map_Graph[11].push_back(&s12);
    Game_Map_Graph[17].push_back(&s12);
    
    //space 13
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s13.Set_Info(false, false, false, 13, temp_array);
    Game_Map_Graph[7].push_back(&s13);
    Game_Map_Graph[14].push_back(&s13);
    Game_Map_Graph[18].push_back(&s13);
    
    //space 14
    s14.Set_Info(false, false, false, 14, temp_array);
    Game_Map_Graph[13].push_back(&s14);
    Game_Map_Graph[15].push_back(&s14);
    
    
    //space 15
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::CYAN, ZONE_COLORS::NON};
    s15.Set_Info(true, false, false, 15, temp_array);
    Game_Map_Graph[8].push_back(&s15);
    Game_Map_Graph[9].push_back(&s15);
    Game_Map_Graph[14].push_back(&s15);
    
    //space 16
    temp_array = {ZONE_COLORS::GREEN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s16.Set_Info(false, false, true, 16, temp_array);
    Game_Map_Graph[20].push_back(&s16);
    Game_Map_Graph[21].push_back(&s16);
    //via teleport
    Game_Map_Graph[1].push_back(&s16);
    Game_Map_Graph[6].push_back(&s16);
    Game_Map_Graph[24].push_back(&s16);
    
    
    //space 17
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s17.Set_Info(false, false, false, 17, temp_array);
    Game_Map_Graph[21].push_back(&s17);
    Game_Map_Graph[23].push_back(&s17);
    
    //space 18
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::PINK, ZONE_COLORS::NON};
    s18.Set_Info(true, false, false, 18, temp_array);
    Game_Map_Graph[13].push_back(&s18);
    Game_Map_Graph[19].push_back(&s18);
    Game_Map_Graph[24].push_back(&s18);
    
    //space 19
    temp_array = {ZONE_COLORS::BLUE, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    s19.Set_Info(true, false, false, 19, temp_array);
    Game_Map_Graph[18].push_back(&s19);
    Game_Map_Graph[20].push_back(&s19);
    
    //space 20
    temp_array = {ZONE_COLORS::GREEN, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s20.Set_Info(false, false, false, 20, temp_array);
    Game_Map_Graph[16].push_back(&s20);
    Game_Map_Graph[19].push_back(&s20);
    Game_Map_Graph[26].push_back(&s20);
    
    //space 21
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    s21.Set_Info(true, false, false, 21, temp_array);
    Game_Map_Graph[11].push_back(&s21);
    Game_Map_Graph[16].push_back(&s21);
    Game_Map_Graph[17].push_back(&s21);
    Game_Map_Graph[22].push_back(&s21);
    Game_Map_Graph[27].push_back(&s21);
    Game_Map_Graph[28].push_back(&s21);
    
    //space 22
    temp_array = {ZONE_COLORS::PURPLE, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s22.Set_Info(false, false, false, 22, temp_array);
    Game_Map_Graph[21].push_back(&s22);
    Game_Map_Graph[23].push_back(&s22);
    
    //space 23
    s23.Set_Info(false, false, false, 23, temp_array);
    Game_Map_Graph[17].push_back(&s23);
    Game_Map_Graph[22].push_back(&s23);
    Game_Map_Graph[29].push_back(&s23);
    
    //space 24
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s24.Set_Info(false, false, true, 24, temp_array);
    Game_Map_Graph[18].push_back(&s24);
    Game_Map_Graph[25].push_back(&s24);
    //via teleport
    Game_Map_Graph[1].push_back(&s24);
    Game_Map_Graph[6].push_back(&s24);
    Game_Map_Graph[16].push_back(&s24);
    
    //space 25
    s25.Set_Info(false, false, false, 25, temp_array);
    Game_Map_Graph[24].push_back(&s25);
    Game_Map_Graph[30].push_back(&s25);
    
    //space 26
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::GREEN, ZONE_COLORS::NON};
    s26.Set_Info(true, false, false, 26, temp_array);
    Game_Map_Graph[20].push_back(&s26);
    Game_Map_Graph[27].push_back(&s26);
    Game_Map_Graph[30].push_back(&s26);
    Game_Map_Graph[31].push_back(&s26);
    
    //space 27
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s27.Set_Info(false, false, false, 27, temp_array);
    Game_Map_Graph[21].push_back(&s27);
    Game_Map_Graph[26].push_back(&s27);
    Game_Map_Graph[28].push_back(&s27);
    Game_Map_Graph[31].push_back(&s27);
    
    //space 28
    s28.Set_Info(false, false, false, 28, temp_array);
    Game_Map_Graph[21].push_back(&s28);
    Game_Map_Graph[27].push_back(&s28);
    Game_Map_Graph[29].push_back(&s28);
    Game_Map_Graph[32].push_back(&s28);
    
    //space 29
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::PURPLE, ZONE_COLORS::NON};
    s29.Set_Info(true, false, false, 29, temp_array);
    Game_Map_Graph[23].push_back(&s29);
    Game_Map_Graph[28].push_back(&s29);
    Game_Map_Graph[32].push_back(&s29);
    

    //space 30
    temp_array = {ZONE_COLORS::PINK, ZONE_COLORS::NON, ZONE_COLORS::NON};
    s30.Set_Info(false, false, false, 30, temp_array);
    Game_Map_Graph[25].push_back(&s30);
    Game_Map_Graph[26].push_back(&s30);
    Game_Map_Graph[31].push_back(&s30);
    
    //space 31
    s31.Set_Info(false, false, false, 31, temp_array);
    Game_Map_Graph[26].push_back(&s31);
    Game_Map_Graph[27].push_back(&s31);
    Game_Map_Graph[30].push_back(&s31);
    
    //space 32
    s32.Set_Info(false, false, false, 32, temp_array);
    Game_Map_Graph[28].push_back(&s32);
    Game_Map_Graph[29].push_back(&s32);
    
}

Graph::~Graph()
{
    delete Object_Instance;
}
