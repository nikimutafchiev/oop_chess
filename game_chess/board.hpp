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
	//returns if the color of our figure(if there is one) is the same as the fig color
	bool isFriendFigure(const Figure* fig) const;
};
constexpr int BOARD_SIZE = 8;
class Board {
	BoardCell arr[BOARD_SIZE][BOARD_SIZE];
	void initDefaultBoard();
public:
	Board();
	Board(BoardCell arr[BOARD_SIZE][BOARD_SIZE]);
	size_t getBoardSize()const;
	BoardCell& operator[](const Position& p);
	const BoardCell& operator[](const Position& p) const;
	int move(Color playerColor, const Position& p1, const Position& p2);
	friend std::ostream& operator<<(std::ostream& os, Board& board);
	//the end position to which a pawn from this color can be moved
	int pawnEnd(Color color) const;
	~Board();
};