#ifndef UI_GAMELOOP_RELATED_FUNCTION_HPP
#define UI_GAMELOOP_RELATED_FUNCTION_HPP
#include <iostream>
#include <string>

#include <thread>
#include <chrono> 



std::string Return_Map_To_Be_Rendered(int Array_Element_Count, Fighters_Print_Info* Info_Array)
{
    
    char mymap[11][71];
    std::string To_Be_printed = "";

    for(int j = 0 ; j < 11 ; j++)
    {
        for(int i = 0 ; i < 71 ; i++)
        {
            mymap[j][i] = ' ';
            if(i == 70)
            {
                mymap[j][i] = '\n';
            }
            
        }
    }
    mymap[10][70] = '\0';
    
    //initializing first row
    for(int i = 18 ; i < 57 ; i++)
    {
        if(i % 6 == 0 || i % 6 == 2)
        {
            if(i % 6 == 0)
            {
                mymap[0][i] = '(';
            }
            if(i % 6 == 2)
            {
                mymap[0][i] = ')';
            }
        }
        else
        {
            mymap[0][i] = '-';
        }
    }
    
    mymap[0][19] = '2';
    mymap[0][25] = '9';
    mymap[0][31] = '3';
    mymap[0][37] = '4';

    mymap[0][41] = '(';
    mymap[0][42] = '1';
    mymap[0][43] = '1';
    mymap[0][44] = ')';
    
    mymap[0][49] = '5';
    mymap[0][55] = '6';

    mymap[1][15] = '/';
    mymap[1][24] = '|';
    mymap[1][33] = '\\';
    mymap[1][36] = '|';
    mymap[1][39] = '/';
    mymap[1][42] = '|';
    mymap[1][45] = '\\';
    mymap[1][48] = '|';

    mymap[2][11] = '(';
    mymap[2][12] = '1';
    mymap[2][13] = ')';

    mymap[2][35] = '(';
    mymap[2][36] = '1';
    mymap[2][37] = '0';
    mymap[2][38] = ')';

    mymap[2][47] = '(';
    mymap[2][48] = '1';
    mymap[2][49] = '2';
    mymap[2][50] = ')';

    mymap[2][51] = '-';
    mymap[2][52] = '-';
    mymap[2][53] = '-';
    mymap[2][54] = '-';
    mymap[2][55] = '-';
    mymap[2][24] = '|';
    mymap[2][42] = '|';

    mymap[3][9] = '/';
    mymap[3][24] = '|';
    mymap[3][42] = '|';
    mymap[3][57] = '\\';

    for(int i = 5 ; i <= 25 ;i++)
    {
        if((i % 6 == 5 || i % 6 == 1) && (i != 11 && i != 13))
        {
            if(i % 6 == 5)
            {
                mymap[4][i] = '(';
            }            
            if(i % 6 == 1)
            {
                mymap[4][i] = ')';
            }            
        }
        else 
        {
            mymap[4][i] = '-';
        }
    }    


    mymap[4][6] = '7';
    mymap[4][18] = '8';
    
    mymap[4][24] = '1';
    mymap[4][25] = '5';
    mymap[4][26] = ')';

    mymap[4][42] = '|';
    mymap[4][62] = '\\';


    mymap[5][3] = '/';
    mymap[5][21] = '/';
    mymap[5][42] = '|';
    mymap[5][67] = '\\';
    

    mymap[6][0] = '(';
    mymap[6][1] = '1';
    mymap[6][2] = '3';
    mymap[6][3] = ')';

    for(int i = 4 ; i < 17 ; i++)
    {
        mymap[6][i] = '-';
    }
    mymap[6][17] = '(';
    mymap[6][18] = '1';
    mymap[6][19] = '4';
    mymap[6][20] = ')';
    
    mymap[6][29] = '(';
    mymap[6][30] = '1';
    mymap[6][31] = '6';
    mymap[6][32] = ')';

    for(int i = 33 ; i < 70 ; i++)
    {
        mymap[6][i] = '-';
    }
    mymap[6][41] = '(';
    mymap[6][42] = '2';
    mymap[6][43] = '1';
    mymap[6][44] = ')';

    mymap[6][66] = '(';
    mymap[6][67] = '1';
    mymap[6][68] = '7';
    mymap[6][69] = ')';
    mymap[6][70] = '\n';

    mymap[7][3] = '\\';
    mymap[7][27] = '/';
    mymap[7][42] = '|';
    mymap[7][45] = '\\';
    mymap[7][65] = '/';
    
    for(int i = 9 ; i < 37 ; i++)
    {
        mymap[8][i] = '-';
    }
    
    for(int i = 50 ; i < 61 ; i++)
    {
        mymap[8][i] = '-';
    }

    mymap[8][6] = '(';
    mymap[8][7] = '1';
    mymap[8][8] = '8';
    mymap[8][8] = ')';

    mymap[8][17] = '(';
    mymap[8][18] = '1';
    mymap[8][19] = '9';
    mymap[8][20] = ')';

    mymap[8][23] = '(';
    mymap[8][24] = '2';
    mymap[8][25] = '0';
    mymap[8][26] = ')';

    mymap[8][35] = '(';
    mymap[8][36] = '2';
    mymap[8][37] = '6';
    mymap[8][38] = ')';

    mymap[8][47] = '(';
    mymap[8][48] = '2';
    mymap[8][49] = '2';
    mymap[8][50] = ')';

    mymap[8][61] = '(';
    mymap[8][62] = '2';
    mymap[8][63] = '3';
    mymap[8][64] = ')';

    mymap[8][42] = '|';


    mymap[9][9] = '\\';
    mymap[9][33] = '/';
    mymap[9][36] = '|';
    mymap[9][39] = '\\';
    mymap[9][42] = '|';
    mymap[9][43] = '\\';
    mymap[9][61] = '/';

    for(int i = 52 ; i < 57 ; i++)
    {
        mymap[9][i] = '-';
    }


    for(int i = 11 ; i < 60 ; i++)
    {
        mymap[10][i] = '-';
        if((i % 6 == 5  && i != 23) &&  i < 58)
        {
            mymap[10][i] = '(';
            mymap[10][i + 1] = '-';
            mymap[10][i + 2] = ')';
            i += 2;
        }
    }
    mymap[10][45] = '-';
    mymap[10][46] = '\\';
    mymap[10][51] = '/';
    mymap[10][57] = '\\';

    mymap[10][12] = '2';
    mymap[10][13] = '4';
    mymap[10][14] = ')';
    
    mymap[10][18] = '2';
    mymap[10][19] = '5';
    mymap[10][20] = ')';
    
    
    mymap[10][42] = '2';
    mymap[10][43] = '7';
    mymap[10][44] = ')';
    
    mymap[10][48] = '2';
    mymap[10][49] = '8';
    mymap[10][50] = ')';
    
    
    mymap[10][59] = '(';
    mymap[10][60] = '2';
    mymap[10][61] = '9';
    mymap[10][62] = ')';
    
    mymap[10][30] = '3';
    mymap[10][31] = '0';
    mymap[10][32] = ')';

    mymap[10][36] = '3';
    mymap[10][37] = '1';
    mymap[10][38] = ')';

    mymap[10][54] = '3';
    mymap[10][55] = '2';
    mymap[10][56] = ')';

    for(int i = 0 ; i < Array_Element_Count ; i++)
    {
        if(!Info_Array[i].Is_Placed_On_Map)
        {
            continue;
        }

        if(Info_Array[i].Fighter_Name != 's')
        {
            
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index] = Info_Array[i].Fighter_Name;
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index + 1] = ')';
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index + 2] = '-';
            
        }
        else
        {   
            
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index] = Info_Array[i].Fighter_Name;
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index + 1] = Info_Array[i].Sis_Number;
            mymap[Info_Array[i].Row_Index][Info_Array[i].Column_Index + 2] = ')';
        }
    }

    

    for(int i = 0 ; i < 11 ; i++)
    {
        for(int j = 0 ; j < 71 ; j++)
        {
            To_Be_printed.push_back(mymap[i][j]);
        }
    }
    return To_Be_printed;


}

#endif