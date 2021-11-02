#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <utility>
#include <fstream>
#include "termcolor.hpp"

#include "Player.h"


void mainMenu();
void middleMenu(Player*, Player*);
void createPlayers(Player*, Player*);
void connect4(bool*, Player*, Player*);
void printBoard(std::vector<std::vector<int>>*, bool*, Player*);
void checkInput(std::vector<std::vector<int>>*, Player*);
void insertMarker(std::vector<std::vector<int>>*, Player*);
std::pair <bool, int> checkWin(std::vector<std::vector<int>>*);

void saveGame();


// Color defenitions, printRed, printGreen aso.
#define pR termcolor::bright_red
#define pG termcolor::bright_green
#define pB termcolor::bright_blue
#define pC termcolor::bright_cyan
#define pY termcolor::bright_yellow
#define pW termcolor::bright_white
#define reset termcolor::reset

#define ROW_HEIGHT 6
#define ROW_WIDTH 7