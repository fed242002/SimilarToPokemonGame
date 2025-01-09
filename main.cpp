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

struct Skill {
    string name;
    int damage;
    string type;

    Skill(string n, int dmg, string t)
        : name(n), damage(dmg), type(t) {}
};

struct pokemon {
    string name;
    string type;
    int health;
    bool alive;
    vector<Skill> skills;

    pokemon(string n, int h,bool a, string t) : name(n), health(h), alive(a), type(t) {}
};

vector<pokemon> initializePokemons() {
    vector<pokemon> pokemons = {
        pokemon("Pikachu", 100, true, "Electric"),
        pokemon("Charmander", 100,true , "Fire"),
        pokemon("Bulbasaur", 100, true ,"Grass")
    };

    // Adding skills to each Pokémon
    pokemons[0].skills.push_back(Skill("Thunderbolt", 15, "Electric"));
    pokemons[0].skills.push_back(Skill("Quick Attack", 10, "Normal"));

    pokemons[1].skills.push_back(Skill("Flamethrower", 15, "Fire"));
    pokemons[1].skills.push_back(Skill("Scratch", 10, "Normal"));

    pokemons[2].skills.push_back(Skill("Vine Whip", 15, "Grass"));
    pokemons[2].skills.push_back(Skill("Tackle", 10, "Normal"));

    return pokemons;
}

vector<pokemon> initializeComputerPokemons() {
    vector<pokemon> computerPokemons = {
        pokemon("Squirtle", 100, true, "Water"),
        pokemon("Jigglypuff", 100, true, "Normal"),
        pokemon("Meowth", 100, true, "Normal")
    };

    // Adding skills to each Pokémon
    computerPokemons[0].skills.push_back(Skill("Water Gun", 15, "Water"));
    computerPokemons[0].skills.push_back(Skill("Tackle", 10, "Normal"));

    computerPokemons[1].skills.push_back(Skill("Sing", 15, "Normal"));
    computerPokemons[1].skills.push_back(Skill("Double Slap", 10, "Normal"));

    computerPokemons[2].skills.push_back(Skill("Scratch", 15, "Normal"));
    computerPokemons[2].skills.push_back(Skill("Bite", 10, "Dark"));

    return computerPokemons;
}

void displayPokemons(const vector<pokemon>& pokemons) {
    cout << "Available Pokemon:\n";
    for (int i = 0; i < pokemons.size(); i++) {
        cout << i + 1 << ". " << pokemons[i].name << endl
             << "Health: " << pokemons[i].health << endl
             << "Type: " << pokemons[i].type << endl
             << "Status: " <<(pokemons[i].alive ? "Alive" : "Dead") << endl << endl;
    }
}

pokemon selectPokemon(const vector<pokemon>& pokemons, int &choice) {
    cout << "Select your Pokemon by entering the corresponding number:\n";

    cin >> choice;

    if (choice < 1 || choice > pokemons.size()) {
        cout << "Invalid choice! Defaulting to Pikachu.\n";
        choice = 1;
        return pokemons[0]; // Default to first Pokémon
    }

    return pokemons[choice - 1];
}

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

    // Function to check if all Pokémon are fainted
bool allFainted(const vector<pokemon>& pokemons)
{
    for (int i = 0; i < pokemons.size(); i++) {
        if (pokemons[i].alive) return false;  // Access each pokemon by index
    }
    return true;
}

void playGame(PlayerScore &a, vector<pokemon> playerPokemons, vector<pokemon> computerPokemons) {
    bool gameOver = false, playerTurn = true;
    system("cls");
    srand(time(0));

    int playerPokemonCount = playerPokemons.size();
    int computerPokemonCount = computerPokemons.size();

    do {
        // Player selects their Pokémon
        int playerChoice;
        do {
            displayPokemons(playerPokemons);
            cout << "Choose an alive Pokemon: ";
            playerChoice = 0;
            cin >> playerChoice;
            if (playerChoice < 1 || playerChoice > playerPokemons.size() || !playerPokemons[playerChoice - 1].alive) {
                cout << "Invalid choice or Pokemon is fainted. Please choose again.\n";
            }
        } while (playerChoice < 1 || playerChoice > playerPokemons.size() || !playerPokemons[playerChoice - 1].alive);

        system("cls");
        pokemon& playerPokemon = playerPokemons[playerChoice - 1];

        // Computer selects its Pokémon
        int computerChoice;
        do {
            computerChoice = rand() % computerPokemons.size();
        } while (!computerPokemons[computerChoice].alive);

        pokemon& computerPokemon = computerPokemons[computerChoice];

        // Display selected Pokémon details
        cout << a.name << "'s Pokemon Details " << endl;
        cout << "Name: " << playerPokemon.name << endl
             << "Health: " << playerPokemon.health << endl
             << "Type: " << playerPokemon.type << endl << endl;

        cout << "Computer's Pokemon Details " << endl;
        cout << "Name: " << computerPokemon.name << endl
             << "Health: " << computerPokemon.health << endl
             << "Type: " << computerPokemon.type << endl << endl;

        while (!gameOver) {
            if (playerTurn) {
                // Player's turn
                cout << a.name << "'s turn" << endl;
                cout << "Skills: " << endl;
                for (size_t i = 0; i < playerPokemon.skills.size(); i++) {
                    cout << i + 1 << ". " << playerPokemon.skills[i].name
                         << " (Damage: " << playerPokemon.skills[i].damage << ")" << endl;
                }

                int skillChoice;
                do {
                    cout << "Choose skill: ";
                    cin >> skillChoice;
                    if (skillChoice < 1 || skillChoice > playerPokemon.skills.size()) {
                        cout << "Invalid choice, try again." << endl;
                    }
                } while (skillChoice < 1 || skillChoice > playerPokemon.skills.size());

                computerPokemon.health -= playerPokemon.skills[skillChoice - 1].damage;
                updatePokemonStatus(computerPokemon);
                cout << "You used " << playerPokemon.skills[skillChoice - 1].name << "!" << endl;
                cout << "Computer's Pokemon Health: " << computerPokemon.health << endl;

                if (!computerPokemon.alive) {
                    computerPokemonCount--;
                    a.score += 100;
                    cout << "Computer's Pokemon fainted!\n";

                    if (allFainted(computerPokemons)) {
                        cout << "You defeated all the Computer's Pokemon! You win!\n";
                        gameOver = true;
                        break;
                    }

                    do {
                        computerChoice = rand() % computerPokemons.size();
                    } while (!computerPokemons[computerChoice].alive);
                    computerPokemon = computerPokemons[computerChoice];
                    cout << "Computer switched to: " << computerPokemon.name << endl;
                }

                playerTurn = false;
            } else {
                // Computer's turn
                cout << "Computer's turn" << endl;
                int computerSkillChoice = rand() % computerPokemon.skills.size();
                cout << "Computer used " << computerPokemon.skills[computerSkillChoice].name << "!" << endl;

                playerPokemon.health -= computerPokemon.skills[computerSkillChoice].damage;
                updatePokemonStatus(playerPokemon);
                cout << "Your Pokemon Health: " << playerPokemon.health << endl;

                if (!playerPokemon.alive) {
                    playerPokemonCount--;
                    cout << "Your Pokemon fainted!\n";

                    if (allFainted(playerPokemons)) {
                        cout << "All your Pokemon have fainted! You lose!\n";
                        gameOver = true;
                        break;
                    }

                    do {
                        displayPokemons(playerPokemons);
                        cout << "Choose an alive Pokemon: ";
                        cin >> playerChoice;
                        if (playerChoice < 1 || playerChoice > playerPokemons.size() || !playerPokemons[playerChoice - 1].alive) {
                            cout << "Invalid choice or Pokemon is fainted. Please choose again.\n";
                        }
                    } while (playerChoice < 1 || playerChoice > playerPokemons.size() || !playerPokemons[playerChoice - 1].alive);

                    playerPokemon = playerPokemons[playerChoice - 1];
                    cout << "You switched to: " << playerPokemon.name << endl;
                }
                playerTurn = true;
            }
        }

    } while (!gameOver);

    ofstream outFile("leaderboard.txt", ios::app);
    if (outFile) {
        outFile << a.name << " " << a.score << endl;
        outFile.close();
    } else {
        cout << "Error saving to leaderboard!" << endl;
    }
}




void leaderBoard(PlayerScore a)
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
                scores.push_back(temp);  // Store each player and score
            }
            inFile.close();
            sort(scores.begin(), scores.end(), compareScores); // Sort scores

            cout << "\nLEADERBOARD\n" << endl;
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
    } while(!backToMenu);
}

void backPack(const vector<pokemon>& pokemons)
{
    bool backToMenu = false;
    vector <string> backpack;


    do
    {
        displayPokemons(pokemons);
        _getch();
        backToMenu = true;
    }while(!backToMenu);
}

//Ini buat declare elemen pokemon
const vector<string> tipe =
{
    "Normal", "Fire", "Water", "Electric", "Grass", "Ice",
    "Fighting", "Poison", "Ground", "Flying", "Psychic", "Bug",
    "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"
};

//Ini buat declare damage pokemon
const vector<vector<float>> tipeChart =
{
   //Nor  Fir  Wat  Ele  Gra  Ice  Fig  Poi  Gro  Fly  Psy  Bug  Roc  Gho  Dra  Dar  Ste  Fai
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0}, // Normal
    {1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0}, // Fire
    {1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0}, // Water
    {1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0}, // Electric
    {1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0}, // Grass
    {1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0}, // Ice
    {2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5}, // Fighting
    {1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0}, // Poison
    {1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0}, // Ground
    {1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0}, // Flying
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0}, // Psychic
    {1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5}, // Bug
    {1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0}, // Rock
    {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0}, // Ghost
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0}, // Dragon
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 2.0}, // Dark
    {1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0}, // Steel
    {1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0}  // Fairy
};

//Ini buat dapetin indeks tipenya
int getTypeIndex(const string& type)
{
    for(size_t i = 0; i < tipe.size(); i++)
    {
        if (tipe[i] == type)
        {
            return i;
        }
    }
    return -1;
}

//Ini buat declare efektivitasnya pokemon
void printEfektivitas(float efektivitas)
{
    if(efektivitas == 0.0)
        cout << "0" << endl;
    else if(efektivitas == 0.5)
        cout << "50" << endl;
    else if(efektivitas == 1.0)
        cout << "100" << endl;
    else if(efektivitas == 2.0)
        cout << "200" << endl;
}

int main() {
    int choice;
    vector<pokemon> pokemons = initializePokemons();
    vector<pokemon> comPokemons = initializeComputerPokemons();
    PlayerScore player;
    player.name;
    cout << "Player Name : "; cin >> player.name; //minta nama player
    player.score = 0; //initialize score awal jadi 0 biar tidak random
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
                playGame(player,pokemons,comPokemons);
                break;

            case 2: // leaderboard
                system("cls");
                cout << "Showing Leaderboard"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                system("cls");
                leaderBoard(player);
                break;

            case 3: // backpack
                system("cls");
                cout << "Opening Backpack"; Sleep(100);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                cout << "."; Sleep(500);
                system("cls");
                backPack(pokemons);
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
