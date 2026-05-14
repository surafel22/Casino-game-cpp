/*
Developed by 
1.Surafel Bahiru --2718/17
2.Marsela Samuel --1857/17
3.Mesay Gadisa.  --1952/17
4.Medhanit Tefera--1901/17
5.Nahom Azmach.  --2165/17

finished at 
December 25 2025 G.C

***Core features 
1.Ask username 
2.Ask balance 
3.Ask the user for difficulty of the game
4.Generate random number 
5.And ask the user for guess

*/



#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

enum Difficulty { EASY = 1, MEDIUM, HARD };

struct Player {
    string name;
    int balance;
};

void showHeader();
void displayHistory();
void saveResultToFile(const Player& p);
int getMaxRange(Difficulty level);
int getMultiplier(Difficulty level);
void playRound(Player* p, Difficulty level);


int main() {
    srand(static_cast<unsigned int>(time(0)));
    Player user;
    int diffChoice;
    char playAgain;

    showHeader();
    displayHistory();

    cout << "\nEnter your name: ";
    cin >> user.name;
    cout << "Enter starting balance: $";
    cin >> user.balance;

    cout << "\nSelect Difficulty (1: Easy, 2: Medium, 3: Hard): ";
    cin >> diffChoice;
    Difficulty level = static_cast<Difficulty>(diffChoice);

    do {
        playRound(&user, level); 

        if (user.balance <= 0) {
            cout << "\nGame Over! You've run out of money." << endl;
            break;
        }

        cout << "\nDo you want another round? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    saveResultToFile(user); 

    cout << "\nFinal balance of $" << user.balance << " saved. Goodbye!" << endl;
    return 0;
}


void showHeader() {
    cout << "========================================" << endl;
    cout << "       ULTIMATE C++ CASINO SYSTEM       " << endl;
    cout << "========================================" << endl;
}


int getMaxRange(Difficulty level) {
    switch (level) {
        case EASY:   return 5;
        case HARD:   return 20;
        case MEDIUM: 
        default:     return 10;
    }
}

int getMultiplier(Difficulty level) {
    switch (level) {
        case EASY:   return 2;
        case HARD:   return 10;
        case MEDIUM: 
        default:     return 5;
    }
}

void playRound(Player* p, Difficulty level) {
    int bet, guess, dice;
    int maxRange = getMaxRange(level);
    int multiplier = getMultiplier(level);

    cout << "\n--- Current Balance: $" << p->balance << " ---" << endl;

    
    do {
        cout << "Enter bet amount: $";
        cin >> bet;
    } while (bet <= 0 || bet > p->balance);

    do {
        cout << "Guess a number (1-" << maxRange << "): ";
        cin >> guess;
    } while (guess < 1|| guess>maxRange);

    dice = rand() % maxRange + 1;
    cout << "The secret number was: " << dice<< endl;

    if (guess == dice) {
        int winnings = bet * multiplier;
        cout << "CONGRATS! You won $" << winnings << "!" <<endl;
        p->balance += winnings; 
    } else {
        cout << "Sorry, you lost $" << bet <<endl;
        p->balance -= bet;
    }
}

void saveResultToFile(const Player& p) {
    ofstream outFile("history.txt", ios::app); 
    if (outFile.is_open()) {
        outFile << "Player: " << p.name << " | Final Balance: $" << p.balance << endl;
        outFile.close();
    }
}

void displayHistory() {
    ifstream inFile("history.txt");
    string line;
    
    cout << "\n[ GAME HISTORY ]" << endl;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "No previous history found" << endl;
    }
    cout << "----------------------------------------" << endl;
}