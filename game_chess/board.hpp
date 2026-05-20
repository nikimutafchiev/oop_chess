#pragma once
#include <iostream>
#include "figure.hpp"
#include "other.hpp"
#include "board_cell.hpp"
class Board {
	static constexpr int SIZE = 8;
	BoardCell arr[SIZE][SIZE];
	void initDefaultBoard();
	std::vector<std::pair<Color,Move>> moves;
public:
	Board();
	Board(BoardCell arr[SIZE][SIZE]);
	Board(const Board& other);
	//maybe unnessesary
	Board& operator=(const Board& other);
	size_t getBoardSize()const;
	bool isValidPosition(const Position& p) const;
	BoardCell& operator[](const Position& p);
	const BoardCell& operator[](const Position& p) const;
	bool canMove(Color playerColor, const Move& move,const Figure* figure);
	int move(Color playerColor, const Move&move);
	friend std::ostream& operator<<(std::ostream& os, Board& board);
	void getAllPossibleMoves(Color c, std::vector<Move>& res);
	//gets the direction of the colored pawn on the board
	int pawnDirection(Color color) const;
	//the end rank to which a pawn from this color can be moved
	int promotionRank(Color color) const;
	unsigned getFigureCount() const;
	unsigned getFigureCount(FigureType f) const;
	//recursively goes to this direction, adding the positions, that were visited until obstacle
	void goRoute(const Position& initPos, Position currPos, int directionX, int directionY, Color enemyColor, std::vector<Move>& res)const;
	void undoMove();
	//gets the position of c colored king/used for check logic
	Position getKingPosition(Color c);
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);
	~Board();
};