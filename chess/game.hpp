#pragma once
#include "other.hpp"
#include "board.hpp"
#include <iostream>
class Player {
	Color color;
	std::string name;
	int score;
public:
	Player();
	Player(Color color, std::string name);
	Color getColor()const;
	const std::string& getName()const;
	std::string& getName();
	int getScore()const;
	void setScore(int newScore);
	void addScore(int points);
	friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

class Game {
	Board* board;
	static Game* instance;
	GameStatus status;
	Player p[2];
	int turn;
	Game();
	Position enterCoordinates();
	int processMove(Player& p);
	void play();
	bool isGameOver();
public:

	void startGame(std::string name1, std::string name2);
	Game(Game& other) = delete;
	Game& operator=(Game& other) = delete;
	static Game* getInstance();
};
