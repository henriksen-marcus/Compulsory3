#include <iostream>
#include "Player.h"
#include "termcolor.hpp"


Player::Player() // Constructor
{
	pos = 0;
	color = 0;
	name = "";
	winner = false;
}


Player::~Player() // Deconstructor
{
}


void Player::printSelf() // Prints out a marker with the player's own color
{
	switch (color)
	{
	case 1:
		std::cout << termcolor::bright_red << " O " << termcolor::reset;
		break;
	case 2:
		std::cout << termcolor::bright_blue << " O " << termcolor::reset;
		break;
	case 3:
		std::cout << termcolor::bright_green << " O " << termcolor::reset;
		break;
	case 4:
		std::cout << termcolor::bright_yellow << " O " << termcolor::reset;
		break;
	}
}


void Player::printSelf(bool) // Prints out a marker with the player's own color with a white background (only used after game is won)
{
	switch (color)
	{
	case 1:
		std::cout << termcolor::on_bright_white << termcolor::bright_red << " O " << termcolor::reset;
		break;
	case 2:
		std::cout << termcolor::on_bright_white << termcolor::bright_blue << " O " << termcolor::reset;
		break;
	case 3:
		std::cout << termcolor::on_bright_white << termcolor::bright_green << " O " << termcolor::reset;
		break;
	case 4:
		std::cout << termcolor::on_bright_white << termcolor::bright_yellow << " O " << termcolor::reset;
		break;
	}
}


void Player::clear() // Resets player variables
{
	pos = 0;
	color = 0;
	name = "";
	winner = false;
}
