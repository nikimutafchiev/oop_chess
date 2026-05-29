#pragma once
#include "board.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <map>
//add time
class Game {
	Board board;
	Player p[2];
	//the commands return if there were successful
	std::map<std::string, std::function<bool()>> commands;
	int turn;
	GameStatus status;
	
	Position enterCoordinates() const;
	Move enterMove() const;
	std::string enterStartOption() const;
	std::string enterCommand() const;
	int processMove(Player& p);
	void handleCommand(const std::string& command);
	void play();
	bool isGameOver();
	bool isStalemate();
	bool isCheckmate();
	bool isDeadPosition();

	

	Game();
public:

	void start();
	
	Game(Game& other) = delete;
	Game& operator=(Game& other) = delete;
	static Game* getInstance();
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);
	friend std::ostream& operator<<(std::ostream& os, const Game& g);
};
