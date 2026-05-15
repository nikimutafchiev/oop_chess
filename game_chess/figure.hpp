#pragma once
#include <iostream>
#include <vector>
#include "other.hpp"

class Board;
class Figure {
	const unsigned points;
protected:
	Color figureColor;
	Figure(Color figureColor,  const Position&pos, unsigned points);
	Position pos;
public:
	//static method that returns the desired figure
	static Figure* factory(FigureType ft, Color color, const Position& initial_position);
	Color getColor() const{
		return figureColor;
	};
	unsigned getPoints() const{
		return points;
	}
	bool isColor(Color c)const {
		return figureColor == c;
	}
	bool isColor(const Figure *other)const {
		return figureColor == other->figureColor;
	}
	virtual std::ostream& print(std::ostream& os) = 0;
	//method that returns whether a figure can go to specific position, using her rules of movement
	virtual bool canMove(const Board& board, const Position& dest)const = 0;
	virtual void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const = 0;
	virtual FigureType getType() const = 0;
	//virtual std::string serialize() const = 0; //TODO
	virtual void move(const Position&pos) {
		this->pos = pos;
	};

	virtual ~Figure() {};
};
class Pawn : public Figure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Position& dest)const override;
	Pawn(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os)override;
	//this function checks if the pawn is at the end of the board, so that i t can be transformed to every other figure
	bool canTransform(const Board& board,const Position& pos);
	FigureType getType() const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	void move(const Position &pos) override {
		this->pos = pos;
		hasMoved = true;
	}
};

class StraightMovingFigure :virtual public Figure {
protected:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
public:
	StraightMovingFigure(Color figureColor, const Position& pos,unsigned points);
	
};
class DiagonallyMovingFigure : virtual public Figure {
protected:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
public:
	DiagonallyMovingFigure(Color figureColor, const Position& pos, unsigned points);

	
};
class Knight : public Figure {

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Knight(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class King : public Figure {
	bool hasMoved;

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	King(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	void move(const Position&pos) override {
		this->pos = pos;
		hasMoved = true;
	}
};
class Bishop : public DiagonallyMovingFigure {

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Bishop(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Queen :  public DiagonallyMovingFigure,public StraightMovingFigure {

public:
	bool canMove(const Board& board, const Position& dest) const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Queen(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Rook : public StraightMovingFigure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Rook(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os);
	FigureType getType() const override;
	void move(const Position&pos) override{
		this->pos = pos;
		hasMoved = true;
	}
};
