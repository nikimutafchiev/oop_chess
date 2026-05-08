#pragma once
#include <iostream>

#include "other.hpp"
class Board;
class Figure {
	const unsigned points;
protected:
	Color figureColor;
	Figure(Color figureColor, unsigned points);

public:
	//static method that returns the desired figure
	static Figure* factory(FigureType ft, Color color);
	Color getColor();
	unsigned getPoints()const;
	virtual std::ostream& print(std::ostream& os) = 0;
	//method that returns whether a figure can go to specific position, using her rules of movement
	virtual bool canMove(Board& board, const Position& oldPos, const Position& newPos) = 0;
};
class Pawn : public Figure {
	bool hasMoved;
public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override;
	Pawn(Color figureColor);
	std::ostream& print(std::ostream& os)override;

};
class Knight : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override;
	Knight(Color figureColor);
	std::ostream& print(std::ostream& os) override;

};
class King : public Figure {
	bool hasMoved;

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override;
	King(Color figureColor);
	std::ostream& print(std::ostream& os) override;
};
class Bishop : public Figure {
	bool hasMoved;

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override;
	Bishop(Color figureColor);
	std::ostream& print(std::ostream& os) override;
};
class Queen : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override;
	Queen(Color figureColor);
	std::ostream& print(std::ostream& os) override;
};
class Rook : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override;
	Rook(Color figureColor);
	std::ostream& print(std::ostream& os);
};
