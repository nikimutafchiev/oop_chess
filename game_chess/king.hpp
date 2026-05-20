#pragma once
#include "figure.hpp"
#include "board.hpp"


class King : public Figure {
	bool hasMoved;

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	King(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	void move(const Position& pos) override {
		this->pos = pos;
		hasMoved = true;
	}
	void serialize(std::ostream& os)const override;
	void deserialize(std::istream& is)override;
	Figure* copy()const {
		return new King(*this);
	}
};