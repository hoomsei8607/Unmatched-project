#include "../headers/graph.hpp"
#include "../headers/space.hpp"

Graph* Graph::Object_Instance = nullptr;
bool Graph::Is_Graph_Initiated = false;



void Graph::Recursive_Path_Finder(std::set<int>& paths, int current_space, int times_to_call_recursive_function, USER user_turn, int current_step)
{
    for(auto space : Game_Map_Graph[current_space])
    {
        if((space->Get_Occupied_Status()))
        {
            continue;
        }
        if(space->Get_Which_User_Is_Occupying_The_Space() != user_turn && space->Get_Which_User_Is_Occupying_The_Space() != USER::NONE)
        {
            continue;
        }
        paths.insert(space->Get_Space_Number());
    }
    current_step++;

    if(current_step < times_to_call_recursive_function)
    {
        for(auto space : Game_Map_Graph[current_space])
        {
            Recursive_Path_Finder(paths, space->Get_Space_Number(), times_to_call_recursive_function,user_turn, current_step);
        }
    }
    else
    {
        return;
    }

}
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
    Object_Instance = nullptr;
}


std::set<int> Graph::Available_Spaces_For_Moving(int move_value, int current_space, USER user_turn)
{
    std::set<int> To_Be_Returned_Set;

}

void Graph::Change_Space_Occiupied_Status(int space_number)
{
    switch (space_number)
    {
    case 1:
        s1.Change_Occupied_Status();
        break;
    case 2:
        s2.Change_Occupied_Status();
        break;
    case 3:
        s3.Change_Occupied_Status();
        break;
    case 4:
        s4.Change_Occupied_Status();
        break;
    case 5:
        s5.Change_Occupied_Status();
        break;
    case 6:
        s6.Change_Occupied_Status();
        break;
    case 7:
        s7.Change_Occupied_Status();
        break;
    case 8:
        s8.Change_Occupied_Status();
        break;
    case 9:
        s9.Change_Occupied_Status();
        break;
    case 10:
        s10.Change_Occupied_Status();
        break;
    case 11:
        s11.Change_Occupied_Status();
        break;
    case 12:
        s12.Change_Occupied_Status();
        break;
    case 13:
        s13.Change_Occupied_Status();
        break;
    case 14:
        s14.Change_Occupied_Status();
        break;
    case 15:
        s15.Change_Occupied_Status();
        break;
    case 16:
        s16.Change_Occupied_Status();
        break;
    case 17:
        s17.Change_Occupied_Status();
        break;
    case 18:
        s18.Change_Occupied_Status();
        break;
    case 19:
        s19.Change_Occupied_Status();
        break;
    case 20:
        s20.Change_Occupied_Status();
        break;
    case 21:
        s21.Change_Occupied_Status();
        break;
    case 22:
        s22.Change_Occupied_Status();
        break;
    case 23:
        s23.Change_Occupied_Status();
        break;
    case 24:
        s24.Change_Occupied_Status();
        break;
    case 25:
        s25.Change_Occupied_Status();
        break;
    case 26:
        s26.Change_Occupied_Status();
        break;
    case 27:
        s27.Change_Occupied_Status();
        break;
    case 28:
        s28.Change_Occupied_Status();
        break;
    case 29:
        s29.Change_Occupied_Status();
        break;
    case 30:
        s30.Change_Occupied_Status();
        break;
    case 31:
        s31.Change_Occupied_Status();
        break;
    case 32:
        s32.Change_Occupied_Status();
        break;
        
    }
}
std::array<ZONE_COLORS,3> Graph::return_zone(int space_number)
{
    Space * space_object;
    Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(space_object, space_number);
    return space_object->return_zone_color(space_number);
}
void Graph::Set_User_Occupying_Space(USER user_occupying_space, int space_number)
{
    Space* space_object_ptr;
    Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(space_object_ptr, space_number);
    space_object_ptr->Set_Which_User_Is_Occupying_The_Space(user_occupying_space);   
    
}

void Graph::Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(Space* & ptr, int space_number)
{
    switch (space_number)
    {
    case 1:
        ptr = &s1;
        break;
    case 2:
        ptr = &s2;
        break;
    case 3:
        ptr = &s3;
        break;
    case 4:
        ptr = &s4;
        break;
    case 5:
        ptr = &s5;
        break;
    case 6:
        ptr = &s6;
        break;
    case 7:
        ptr = &s7;
        break;
    case 8:
        ptr = &s8;
        break;
    case 9:
        ptr = &s9;
        break;
    case 10:
        ptr = &s10;
        break;
    case 11:
        ptr = &s11;
        break;
    case 12:
        ptr = &s12;
        break;
    case 13:
        ptr = &s13;
        break;
    case 14:
        ptr = &s14;
        break;
    case 15:
        ptr = &s15;
        break;
    case 16:
        ptr = &s16;
        break;
    case 17:
        ptr = &s17;
        break;
    case 18:
        ptr = &s18;
        break;
    case 19:
        ptr = &s19;
        break;
    case 20:
        ptr = &s20;
        break;
    case 21:
        ptr = &s21;
        break;
    case 22:
        ptr = &s22;
        break;
    case 23:
        ptr = &s23;
        break;
    case 24:
        ptr = &s24;
        break;
    case 25:
        ptr = &s25;
        break;
    case 26:
        ptr = &s26;
        break;
    case 27:
        ptr = &s27;
        break;
    case 28:
        ptr = &s28;
        break;
    case 29:
        ptr = &s29;
        break;
    case 30:
        ptr = &s30;
        break;
    case 31:
        ptr = &s31;
        break;
    case 32:
        ptr = &s32;
        break; 

    default:
        ptr = nullptr;
        break;
    }

}


USER Graph::Get_User_Occupying_Space(int space_number)
{
    Space* space_ptr;
    Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(space_ptr, space_number);
    return space_ptr->Get_Which_User_Is_Occupying_The_Space();
}


bool Graph::Can_Fighter_Use_Attacking_Cards(USER user_turn, ATTACKING_RANGE fighter_range, int fighter_space_number)
{
    if(fighter_range == ATTACKING_RANGE::MELEE)
    {
        for(auto space : Game_Map_Graph[fighter_space_number])
        {
            if(space->Get_Which_User_Is_Occupying_The_Space() != user_turn && space->Get_Which_User_Is_Occupying_The_Space() != USER::NONE)
            {
                return true;
            }
        }
    }
    else if(fighter_range == ATTACKING_RANGE::RANGED)
    {
        std::array <ZONE_COLORS, 3> fighter_space_zones = return_zone(fighter_space_number);
        std::array <ZONE_COLORS, 3> potential_enemy_space_zones;
        for(int i = 1 ; i < 33 ; i++)
        {
            if(i == fighter_space_number)
            {
                continue;
            }
            if(Get_User_Occupying_Space(i) == user_turn || Get_User_Occupying_Space(i) == USER::NONE)
            {
                continue;
            }
            

            potential_enemy_space_zones = return_zone(i);
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int k=0 ; k < 3 ; k++)
                {
                    if(fighter_space_zones[j] == potential_enemy_space_zones[k])
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::vector<int> Graph::return_enemies_in_melee_range(USER user_turn, int sapce_number)
{
    std::vector<int> temp_vec;
    for(auto space : Game_Map_Graph[sapce_number])
    {
        if(space->Get_Which_User_Is_Occupying_The_Space() == user_turn || space->Get_Which_User_Is_Occupying_The_Space() == USER::NONE )
        {
            continue;
        }
        temp_vec.push_back(space->Get_Space_Number());

    }
    return temp_vec;
}
std::vector<int> Graph::return_adjacent_allies(USER user_turn, int sapce_number)
{
    std::vector<int> temp_vec;
    for(auto space : Game_Map_Graph[sapce_number])
    {
        if(space->Get_Which_User_Is_Occupying_The_Space() != user_turn || space->Get_Which_User_Is_Occupying_The_Space() == USER::NONE )
        {
            continue;
        }
        temp_vec.push_back(space->Get_Space_Number());

    }
    return temp_vec;
}

std::set <int> Graph::return_adjacent_enemies_space_numbers_for_melee_attack(USER user_turn, int current_user_fighter_space_number)
{
    std::set<int> to_be_returned;
    for(auto space : Game_Map_Graph[current_user_fighter_space_number])
    {
        if(space->Get_Which_User_Is_Occupying_The_Space() != user_turn && space->Get_Which_User_Is_Occupying_The_Space() != USER::NONE )
        {
            to_be_returned.insert(space->Get_Space_Number());
        }
    }
    return to_be_returned;
}

bool Graph::Is_Space_Multi_Zone(int space_number)
{
   Space* space = nullptr;
   Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(space, space_number);
   return space->Get_Multi_Zone_status(); 
}

std::set <int> Graph::return_available_enemies_space_for_range_attack(USER user_turn, int current_user_fighter_space_number)
{
    std::set<int> to_be_returned;
    ZONE_COLORS color_for_comparison;
    std::array<ZONE_COLORS,3> space_color_array_to_be_compaired_with;
    std::array<ZONE_COLORS,3> current_space_color_array = return_zone(current_user_fighter_space_number);
    Space* space = nullptr;
    
    color_for_comparison = return_zone(current_user_fighter_space_number)[0];
    for(int a = 0 ; a < 3 ; a++)
    {
        color_for_comparison = current_space_color_array[a];
        if(color_for_comparison == ZONE_COLORS::NON)
        {
            break;
        }


        for(int i = 1 ; i < 33 ; i++)
        {
            if(i == current_user_fighter_space_number)
            {
                continue;
            }
            
            Set_The_Passed_Pointer_To_The_Corresponding_Space_Object(space, i);
            space_color_array_to_be_compaired_with = return_zone(i);
            for(int j = 0 ; j < 3 ; j++)
            {
                if(space_color_array_to_be_compaired_with[j] == color_for_comparison)
                {
                    to_be_returned.insert(i);
                    break;
                }
            }
        }
    }
    return to_be_returned;
}