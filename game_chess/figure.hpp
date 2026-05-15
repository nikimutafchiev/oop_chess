#pragma once
#include <iostream>
#include <vector>
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
	virtual bool canMove(const Board& board, const Move& move)const = 0;
	virtual void getAllPossibleMoves(const Board& board,const Position&pos, std::vector<Move>& res) const = 0;
	virtual FigureType getType() const = 0;
	//virtual std::string serialize() const = 0; //TODO
	virtual void move() {
	};
	virtual ~Figure() {};
};
class Pawn : public Figure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Move& move)const override;
	Pawn(Color figureColor);
	std::ostream& print(std::ostream& os)override;
	//this function checks if the pawn is at the end of the board, so that i t can be transformed to every other figure
	bool canTransform(const Board& board,const Position& pos);
	FigureType getType() const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	void move() override {
		hasMoved = true;
	}
};

class StraightMovingFigure :virtual public Figure {
protected:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
public:
	StraightMovingFigure(Color figureColor, unsigned points);
	
};
class DiagonallyMovingFigure : virtual public Figure {
protected:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
public:
	DiagonallyMovingFigure(Color figureColor, unsigned points);

	
};
class Knight : public Figure {

public:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	Knight(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class King : public Figure {
	bool hasMoved;

public:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	King(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	void move() override {
		hasMoved = true;
	}
};
class Bishop : public DiagonallyMovingFigure {

public:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	Bishop(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Queen :  public DiagonallyMovingFigure,public StraightMovingFigure {

public:
	bool canMove(const Board& board, const Move& move) const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	Queen(Color figureColor);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
};
class Rook : public StraightMovingFigure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Move& move)const override;
	void getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const override;
	Rook(Color figureColor);
	std::ostream& print(std::ostream& os);
	FigureType getType() const override;
	void move() override{
		hasMoved = true;
	}
};
