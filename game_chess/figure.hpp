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
	virtual Figure* copy()const = 0;
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
	virtual void move(const Position&pos) {
		this->pos = pos;
	};
	//virtual void serialize(std::ostream& os) = 0;
	//virtual void deserialize(std::istream& is) = 0;
	virtual ~Figure() {};
};






