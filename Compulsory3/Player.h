#pragma once
#include <string>

class Player
{
public:
	Player();
	~Player();

	int pos, color, marker;
	std::string name;

	void printSelf();

};

