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
	Color getColor() const;
	unsigned getPoints()const;
	virtual std::ostream& print(std::ostream& os) = 0;
	//method that returns whether a figure can go to specific position, using her rules of movement
	virtual bool canMove(const Board& board, const Position& oldPos, const Position& newPos) = 0;
	virtual FigureType getType() const = 0;
	virtual ~Figure() {};
};
class Pawn : public Figure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos)override;
	Pawn(Color figureColor);
	std::ostream& print(std::ostream& os)override;
	//this function checks if the pawn is at the end of the board, so that i t can be transformed to every other figure
	bool canTransform(const Board& board,const Position& pos);
	FigureType getType() const override;
};
class StraightMovingFigure :virtual public Figure {
public:
	StraightMovingFigure(Color figureColor, unsigned points);
	bool canMoveStraight(const Board& board, const Position& oldPos, const Position& newPos) ;
};
class DiagonallyMovingFigure : virtual public Figure {
public:
	DiagonallyMovingFigure(Color figureColor, unsigned points);
	bool canMoveDiagonally(const Board& board, const Position& oldPos, const Position& newPos);
};
class Knight : public Figure {

public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos) override;
	Knight(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class King : public Figure {
	bool hasMoved;

public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos) override;
	King(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Bishop : public DiagonallyMovingFigure {

public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos) override;
	Bishop(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Queen :  public DiagonallyMovingFigure,public StraightMovingFigure {

public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos)override;
	Queen(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Rook : public StraightMovingFigure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Position& oldPos, const Position& newPos)override;
	Rook(Color figureColor);
	std::ostream& print(std::ostream& os);
	FigureType getType() const override;
};
