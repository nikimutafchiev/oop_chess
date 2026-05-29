#pragma once
#include "other.hpp"
#include <iostream>

class Player {
	Color color;
	std::string name;
	int score;
	PlayerType type;
	//field only for type::COMPUTER
	int diffuculty;
	
public:

	bool isChecked;
	Player();
	Player(Color color, std::string name,PlayerType type);
	Color getColor()const;
	void setColor(Color c) {
		color = c;
	}
	const std::string& getName()const;
	std::string& getName();
	int getScore()const;
	void setScore(int newScore);
	void addScore(int points);
	//void makeMove(const Board& board);
	friend std::ostream& operator<<(std::ostream& os, const Player& p);
	friend std::istream& operator>>(std::istream& is, Player& p);
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

};