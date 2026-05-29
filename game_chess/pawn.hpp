#pragma once
#include "figure.hpp"
#include "board.hpp"

class Pawn : public Figure {
	bool hasMoved;
public:
	bool moved()const {
		return hasMoved;
	}
	bool canMove(const Board& board, const Position& dest)const override;
	Pawn(Color figureColor, const Position& pos);
	Pawn(const Pawn& other):Figure(other.figureColor,other.pos,1) {
		hasMoved = false;
	}
	std::ostream& print(std::ostream& os)override;
	//this function checks if the pawn is at the end of the board, so that i t can be transformed to every other figure
	bool canTransform(const Board& board);
	FigureType getType() const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	void move(const Position& pos) override {
		this->pos = pos;
		hasMoved = true;
	}
	void serialize(std::ostream& os)const override;
	void deserialize(std::istream& is)override;
	Figure* copy()const {
		return new Pawn(*this);
	}
};