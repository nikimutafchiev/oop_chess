#pragma once
#include <iostream>
#include "figure.hpp"
#include "other.hpp"

class BoardCell {

	Figure* fig;
	Position pos;
	Color color;
public:
	BoardCell() = default;
	BoardCell(Figure* fig, Position pos, Color color);
	//bug: when deleting will have problem if something is on the stack
	void setFigure(Figure* f);
	Figure* getFigure();
	const Figure* getFigure() const;
	bool hasFigure() const;
	Color getColor() const;
	friend std::ostream& operator<<(std::ostream& os, const BoardCell& bc);
	void moveFromCell(BoardCell& other);
};
constexpr int BOARD_SIZE = 8;
class Board {
	BoardCell arr[BOARD_SIZE][BOARD_SIZE];
	void initDefaultBoard();
public:
	Board();
	Board(BoardCell arr[BOARD_SIZE][BOARD_SIZE]);

	BoardCell& operator[](const Position& p);
	int move(Color playerColor, const Position& p1, const Position& p2);
	friend std::ostream& operator<<(std::ostream& os, Board& board);
	~Board();
};