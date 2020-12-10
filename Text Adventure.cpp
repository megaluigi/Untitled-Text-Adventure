// Text Adventure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "classes.h"

using namespace std;

World* world;
Character* pc;

// Initializes all relevant objects before the game starts
// Instantiate the world, then the locations, then bind the locations,
// then add items, then instantiate npcs
void initWorld(string name) {
    World* world = new World();
    world->linkLoc("Library", "Basement", true);
    world->linkLoc("Tunnel", "Basement", true);
}

// Receives a string of words,
// returns a vector of word strings
vector<string> parseArgs(string& argString) {
    vector<string> argArray;
    return argArray;
}

// Interprets dialogue from the user and responds accordingly
void parseDialogue(string& quote) {
    vector<string> words = parseArgs(quote);
}

void parseCommand(string& cmd) {
    if (cmd == "help") {
        cout << "Available Commands:\n"
             << "help: List all commands\n"
             << "exit: Exit without saving\n"
             << "where: List your current location\n";
    }
    else if (cmd == "exit") {
        exit(EXIT_SUCCESS);
    }
    else if (cmd == "say") {
        getline(cin, cmd);
        parseDialogue(cmd);
    }
    else if (cmd == "where") {
        cout << pc->getLoc() << endl;
    }
    else {
        cout << "Command not recognized\nEnter \"help\" to list available commands\n";
    }
}

int main()
{
    cout << "Welcome to \"A Fright to Remember\", an experimental text adventure from Wrought Studios\n"
         << "This game is very early in development and full of bugs, but I hope you still enjoy it!\n";

    string command;
    World* world = new World();
    Character* pc = new Character("Donny", 100, world->getLoc("Library"));
    initWorld("Donny");

    while (true) {
        
        cout << ">> ";
        cin >> command;

        if (command == "exit") {
            break;
        }

        parseCommand(command);
    }
}
