#pragma once
#include "other.hpp"
#include "board.hpp"
#include <iostream>
#include <vector>
#include "player.hpp"
//add time
class Game {
	Board* board;
	static Game* instance;
	GameStatus status;

	Player p[2];
	int turn;
	
	Position enterCoordinates() const;
	Move enterMove() const;
	int enterOption() const;
	int processMove(Player& p);
	void play();
	bool isGameOver();
	bool isStalemate();
	bool isCheckmate();
	bool isDeadPosition();
	bool isCheck(const std::vector<Move>&);
	

	Game();
public:

	void start();
	
	Game(Game& other) = delete;
	Game& operator=(Game& other) = delete;
	static Game* getInstance();
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);
};
