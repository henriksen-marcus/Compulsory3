#pragma once
#include <string>

class Player
{
public:
	Player();
	~Player();

	bool isCurrent;
	int pos, color, marker, score;
	std::string name;

	void printSelf();

};

