#pragma once
#include "diagonally_moving_figure.hpp"
#include "straight_moving_figure.hpp"

class Queen : public DiagonallyMovingFigure, public StraightMovingFigure {

public:
	bool canMove(const Board& board, const Position& dest) const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Queen(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os) override;
	FigureType getType() const override;
	Figure* copy()const {
		return new Queen(*this);
	}
	void serialize(std::ostream& os)const override;
	void deserialize(std::istream& is)override;
};