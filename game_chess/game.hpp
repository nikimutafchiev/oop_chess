#pragma once
#include "board.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <map>
//add time
class Game {
	Board board;
	GameStatus status;

	Player p[2];
	int turn;
	std::map<std::string, std::function<void()>> commands;
	
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
};
