#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <algorithm>
#include <cstdlib>

using namespace std;

 char mainMaps[15][15] = {
        {'9', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '6'}, //0
        {'2', '0', '3', '0', '4', '0', '5', '0', '0', '0', '0', '0', '0', '0', '2'}, //1
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //2
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //3
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //4
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //5
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //6
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //7
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //8
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //9
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //10
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //11
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //12
        {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2'}, //13
        {'8', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '7'}  //14
    };

    //1 buat pembatas, 2 juga pembatas,3 rumah , 4 medical center, 5, pokeshops



   void printMaps()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if(mainMaps[i][j] == '1') {
                cout << (char)205 << " " ; //print horizontal
            }
            else if(mainMaps[i][j] == '0') {
                cout << "  "; // print kosong
            }
            else if(mainMaps[i][j] == '2') {
                cout << (char)186 << " "; //print vertical
            }
            else if(mainMaps[i][j] == '3') {
                cout << "H "; //print
            }
            else if(mainMaps[i][j] == '4') {
                cout << "M " ; //print medical centre
            }
            else if(mainMaps[i][j] == '5') {
                cout << "S "; //print shops
            }
            else if(mainMaps[i][j] == '6') {
                cout << (char)187 << " ";
            }
            else if(mainMaps[i][j] == '7') {
                cout << (char)188 << " ";
            }
            else if(mainMaps[i][j] == '8') {
                cout << (char)200 << " ";
            }
            else if(mainMaps[i][j] == '9') {
                cout << (char)201 << " ";
        }

    }
    cout << endl;
}
}


int main ()
{

    printMaps();
    return 0;
}
