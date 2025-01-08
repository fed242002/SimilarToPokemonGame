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


//map buat pokemon pake variabel global

struct xy {
    int x, y;
};

struct player {
    int x, y, dx, dy;
    char shape;
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

 char mainMaps[15][15] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, //0
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
        {'2', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '2'}  //14
    };

    //1 buat pembatas, 2 juga pembatas,3 rumah , 4 medical center, 5, pokeshops


char houseMaps[5][5] = {
    {'1', '1', '1', '1', '1'}, //0
    {'1', '0', '0', '0', '1'}, //1
    {'1', '0', '2', '0', '1'}, //2
    {'1', '0', '0', '0', '1'}, //3
    {'1', '1', '1', '1', '1'}  //4
};

char MedicalCentreMaps[5][5] = {
    {'1', '1', '1', '1', '1'}, //0
    {'1', '0', '0', '0', '1'}, //1
    {'1', '0', '3', '0', '1'}, //2
    {'1', '0', '0', '0', '1'}, //3
    {'1', '1', '1', '1', '1'}  //4
};

char shopMaps[5][5] = {
    {'1', '1', '1', '1', '1'}, //0
    {'1', '0', '0', '0', '1'}, //1
    {'1', '0', '4', '0', '1'}, //2
    {'1', '0', '0', '0', '1'}, //3
    {'1', '1', '1', '1', '1'}  //4
};

void printMaps()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if(mainMaps[i][j] == '1') {
                cout << (char)186; //print horizontal
            }
            else if(mainMaps[i][j] == '0') {
                cout << ' '; // print kosong
            }
            else if(mainMaps[i][j] == '2') {
                cout << (char)205; //print vertical
            }
            else if(mainMaps[i][j] == '3') {
                cout << "H"; //print
            }
            else if(mainMaps[i][j] == '4') {
                cout << "M" ; //print medical centre
            }
            else if(mainMaps[i][j] == '5') {
                cout << "S"; //print shops
            }
        }
        cout << endl;
    }
}

int menu() {
    xy menu[4];
    menu[1] = { 50, 10 };
    menu[2] = { 50, 12 };
    menu[3] = { 50, 14 };

    int cursor = 1;
    bool end = false;

    while (!end) {
        system("cls");
        const int FRAME_HEIGHT = 30;
        const int FRAME_WIDTH = 120;

        char v = 186; // vertical
        char h = 205; // horizontal
        char lt = 201; // left top
        char lb = 200; // left bot
        char rt = 187; // right top
        char rb = 188; // right bot

        // Draw border
        for (int i = 0; i < FRAME_HEIGHT; i++) {
            for (int j = 0; j < FRAME_WIDTH; j++) {
                if (i == 0 && j == 0)
                    cout << lt;
                else if (i == 0 && j == FRAME_WIDTH - 1)
                    cout << rb;
                else if (i == FRAME_HEIGHT - 1 && j == 0)
                    cout << lb;
                else if (i == FRAME_HEIGHT - 1 && j == FRAME_WIDTH - 1)
                    cout << rt;
                else if (i == 0 || i == FRAME_HEIGHT - 1)
                    cout << h;
                else if (j == 0 || j == FRAME_WIDTH - 1)
                    cout << v;
                else
                    cout << " ";
            }
            cout << endl;
        }

        // Welcome sign
        gotoxy(48, 5);
        setColor(9); // blue text
        cout << " Welcome to";
        setColor(14); // Yellow text
        cout << " POKEMON ";
        setColor(9);

        // Menu
        for (int i = 1; i <= 3; i++) {
            gotoxy(menu[i].x - (cursor == i ? 2 : 0), menu[i].y);
            cout << (cursor == i ? "> " : "  ") << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" : "EXIT");
        }

        // Input
        char input = _getch();

        if (input == 'W' || input == 'w') {
            if (cursor > 1) cursor--;
        } else if (input == 'S' || input == 's') {
            if (cursor < 3) cursor++;
        } else if (input == '\r') { // Enter
            switch (cursor) {
                case 1:
                    return 1;  // play game
                case 2:
                    return 2;  // leaderboard
                case 3:
                    return 3;  // exit
            }
        }
    }

    return 0; // Default return value (not used)
}

int main() {
    int choice;
    do {
        int scores = 0;
        choice = menu();
        switch (choice) {
            case 1: // play game
                system("cls");
                cout << "Starting Game"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                printMaps();
                break;

            case 2: // leaderboard
                system("cls");
                cout << "Showing Leaderboard"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                break;
        }
    } while (choice != 3);

    system("cls");
    cout << "Thank You For Playing Pokemon"; Sleep(100);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    return 0;
}
