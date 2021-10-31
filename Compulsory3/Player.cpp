#include "Player.h"
#include <iostream>

Player::Player() // Constructor
{
	pos = 0;
	color = 1;
	name = "";
}

Player::~Player() // Deconstructor
{
	std::cout << this << "was decontructed.";
}

void Player::printSelf() 
{
	switch (color)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}