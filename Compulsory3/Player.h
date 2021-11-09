#pragma once

class Player
{
public:
	Player();
	~Player();

	bool winner;
	int pos, color, marker, score;
	std::string name;

	void printSelf();
	void printSelf(bool);
	void clear();

};

