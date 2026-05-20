#pragma once
#include "other.hpp"
#include <iostream>

class Player {
	Color color;
	std::string name;
	int score;
public:
	Player();
	Player(Color color, std::string name);
	Color getColor()const;
	void setColor(Color c) {
		color = c;
	}
	const std::string& getName()const;
	std::string& getName();
	int getScore()const;
	void setScore(int newScore);
	void addScore(int points);
	friend std::ostream& operator<<(std::ostream& os, const Player& p);
	friend std::istream& operator>>(std::istream& is, Player& p);
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

};