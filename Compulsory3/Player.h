#pragma once
#include <string>

class Player
{
public:
	Player();
	~Player();

	bool isCurrent;
	int pos, color, marker;
	std::string name;

	void printSelf();

};

