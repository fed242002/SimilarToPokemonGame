#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <cstdlib>


using namespace std;

struct PlayerScore {
    string name;
    int score;
};

bool compareScores(const PlayerScore& a, const PlayerScore& b) {
    return a.score > b.score;
}

struct xy {
    int x, y;
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


int menu() {
    xy menu[5];
    menu[1] = { 50, 10 };
    menu[2] = { 50, 12 };
    menu[3] = { 50, 14 };
    menu[4] = { 50, 16 };


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
                    cout << rt;
                else if (i == FRAME_HEIGHT - 1 && j == 0)
                    cout << lb;
                else if (i == FRAME_HEIGHT - 1 && j == FRAME_WIDTH - 1)
                    cout << rb;
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
        for (int i = 1; i <= 4; i++) {
            gotoxy(menu[i].x - (cursor == i ? 2 : 0), menu[i].y);
            cout << (cursor == i ? "> " : "  ") << (i == 1 ? "PLAY GAME" : i == 2 ? "LEADERBOARD" :i == 3 ? "BACKPACK" : "EXIT");
        }

        // Input
        char input = _getch();

        if (input == 'W' || input == 'w') {
            if (cursor > 1) cursor--;
        } else if (input == 'S' || input == 's') {
            if (cursor < 4) cursor++;
        } else if (input == '\r') { // Enter
            switch (cursor) {
                case 1:
                    return 1;  // play game
                case 2:
                    return 2;  // leaderboard
                case 3:
                    return 3;  // backpack
               case 4:
                    return 4;  // exit

            }
        }
    }

    return 0; // Default return value (not used)
}

void playGame()
{
    bool gameOver = false;
    PlayerScore player;
    player.name;
    cout << "Player Name : "; cin >> player.name;
    player.score;
    system("cls");

    do
    {
        cout << player.name << "'s Pokemon Details " << endl; //detail pokemon player

        cout << "Computer's Pokemon Details " << endl; //detail pokemon musuh

        cout << "Damage Logs" << endl;

    }while(!gameOver);

}

void leaderBoard()
{
    bool backToMenu = false;
    setColor(7);

    do
    {
        vector<PlayerScore> scores;
        string fileName = "leaderboard.txt";

        ifstream inFile(fileName);
        if (!inFile)
        {
            cout << "No leaderboard data found.\n";
        }
        else
        {
            PlayerScore temp;
            while (inFile >> temp.name >> temp.score)
            {
                scores.push_back(temp);
            }
            inFile.close();
            sort(scores.begin(), scores.end(), compareScores);

            cout << "\nLEADERBOARD\n";
            cout << left << setw(20) << "Player" << setw(10) << "Score" << endl;
            cout << string(30, '-') << endl;

            for (int i = 0; i < scores.size(); i++)
            {
                cout << setw(20) << left << scores[i].name << setw(10) << scores[i].score << endl;
            }
        }

        cout << "\nPress any key to return to the menu...\n";
        _getch();
        backToMenu = true;
    }while(!backToMenu);
}

void backPack()
{
    bool backToMenu = false;

    do
    {

    }while(!backToMenu);
}

int main() {
    int choice;
    do {
        choice = menu();
        switch (choice) {
            case 1: // play game
                system("cls");
                cout << "Starting Game"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                system("cls");
                playGame();
                break;

            case 2: // leaderboard
                system("cls");
                cout << "Showing Leaderboard"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                system("cls");
                leaderBoard();
                break;

            case 3: // backpack
                system("cls");
                cout << "Opening Backpack"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                system("cls");
                backPack();
                break;
        }
    } while (choice != 4);

    system("cls");
    cout << "Thank You For Playing Pokemon"; Sleep(100);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    cout << "."; Sleep(500);
    return 0;
}
