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
	friend std::istream& operator>>(std::istream& is, Player& p);
};
//add time
class Game {
	Board* board;
	static Game* instance;
	GameStatus status;

	Player p[2];
	int turn;
	
	Position enterCoordinates();
	int processMove(Player& p);
	void play();
	bool isGameOver();
	bool isStalemate();
	bool isCheckmate();
	bool isDeadPosition();

	Game();
public:

	void startGame(std::string name1, std::string name2);
	
	Game(Game& other) = delete;
	Game& operator=(Game& other) = delete;
	static Game* getInstance();
};
