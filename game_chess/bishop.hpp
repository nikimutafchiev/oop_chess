#pragma once
#include "diagonally_moving_figure.hpp"

class Bishop : public DiagonallyMovingFigure {

public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Bishop(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	Figure* copy()const {
		return new Bishop(*this);
	}
	void serialize(std::ostream& os)const override;
	void deserialize(std::istream& is)override;
};