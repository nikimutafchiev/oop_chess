#pragma once
#include <iostream>
#include "figure.hpp"
#include "other.hpp"

class BoardCell {
	//unique pointer?
	Figure* fig;
	Position pos;
	Color color;
public:
	BoardCell() = default;
	BoardCell(Figure* fig, Position pos, Color color);
	void setFigure(Figure* f);
//	Figure* getFigure();
	const Figure* getFigure() const;
	bool hasFigure() const;
	Color getColor() const;
	friend std::ostream& operator<<(std::ostream& os, const BoardCell& bc);
	//gets the value from the cell and leaves the source with nothing
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
	bool isValidPosition(const Position& p) const;
	BoardCell& operator[](const Position& p);
	const BoardCell& operator[](const Position& p) const;
	int move(Color playerColor, const Move&move);
	friend std::ostream& operator<<(std::ostream& os, Board& board);
	//the end position to which a pawn from this color can be moved
	int pawnDirection(Color color) const;
	int pawnEnd(Color color) const;
	unsigned getFigureCount() const;
	unsigned getFigureCount(FigureType f) const;
	~Board();
};