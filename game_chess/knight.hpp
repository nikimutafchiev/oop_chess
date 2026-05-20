#pragma once
#include "figure.hpp"
#include "board.hpp"

class Knight : public Figure {

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Knight(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	Figure* copy()const {
		return new Knight(*this);
	}
	void serialize(std::ostream& os)const override;
	void deserialize(std::istream& is)override;
};