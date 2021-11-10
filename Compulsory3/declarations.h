#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <tuple>
#include "Player.h"
#include "termcolor.hpp"


void mainMenu();
void middleMenu(Player*, Player*, bool);															// Lets player decide whether to go with default or custom names
void createPlayers(Player*, Player*, bool);															// Custom player creation
void connect4(bool, Player*&, Player*&, Player*&);													// Main game function
bool saveGamePrompt(std::vector<std::vector<int>>*, Player*, Player*, Player*, bool);				// Asks the player if they want to save and play again
void boardUpdate(std::vector<std::vector<int>>*, std::tuple<bool, int, int, int, std::string>);		// Updates the board vector at the win positions after the game is won
void printBoard(std::vector<std::vector<int>>*, bool, Player*&, Player*&, Player*&);				
void checkInput(std::vector<std::vector<int>>*, Player*&, Player*&, Player*&);
void insertMarker(std::vector<std::vector<int>>*, Player*&, Player*&, Player*&);					// Inserts a marker at the active player's position
std::tuple <bool, int, int, int, std::string> checkWin(std::vector<std::vector<int>>*);
bool checkForFullBoard(std::vector<std::vector<int>>* board);
void saveGame(std::vector<std::vector<int>>*, Player*&, Player*&);
void loadGame();
void aiMove(std::vector<std::vector<int>>* board, bool, Player*&, Player*&, Player*&);				// Main function for AI, simulates AI arrow movement
int getAiInfo(std::vector<std::vector<int>>* &board);												// Support function for aiMove, gets all potential and valid 2- and 3 in a rows and decides the AIs next move
std::pair <int, int> getBestInt(std::vector <std::pair<int, int>>);									// Support for multiblock, like hitting 2 birds with one stone
std::pair <bool, int> checkAvailablility(std::vector<std::vector<int>>*, int);						// Checks if the specified column has available spots and returns the y position


// Color defenitions, printRed, printGreen aso.
#define pR termcolor::bright_red
#define pG termcolor::bright_green
#define pB termcolor::bright_blue
#define pC termcolor::bright_cyan
#define pY termcolor::bright_yellow
#define oW termcolor::on_bright_white
#define reset termcolor::reset