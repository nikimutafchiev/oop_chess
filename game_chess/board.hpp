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
	BoardCell(const BoardCell& other);
	//BoardCell& operator=(const BoardCell& other);
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
	bool isFriendColor(Color c) const;
};
class Board {
	static constexpr int SIZE = 8;
	BoardCell arr[SIZE][SIZE];
	void initDefaultBoard();
	std::vector<Move> moves;
public:
	Board();
	Board(BoardCell arr[SIZE][SIZE]);
	Board(const Board& other);
	size_t getBoardSize()const;
	bool isValidPosition(const Position& p) const;
	BoardCell& operator[](const Position& p);
	const BoardCell& operator[](const Position& p) const;
	int move(Color playerColor, const Move&move);
	friend std::ostream& operator<<(std::ostream& os, Board& board);
	void getAllPossibleMoves(Color c, std::vector<Move>& res);
	//the end position to which a pawn from this color can be moved
	int pawnDirection(Color color) const;
	int pawnEnd(Color color) const;
	unsigned getFigureCount() const;
	unsigned getFigureCount(FigureType f) const;
	//recursively goes to this direction, adding the positions, that were visited until obstacle
	void goRoute(const Position& initPos, Position currPos, int directionX, int directionY, Color enemyColor, std::vector<Move>& res)const;
	void undoMove();
	//gets the position of c colored king/used for check logic
	Position getKingPosition(Color c);
	~Board();
};