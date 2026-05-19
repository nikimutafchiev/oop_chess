#pragma once
#include "straight_moving_figure.hpp"


class Rook : public StraightMovingFigure {
	bool hasMoved;
public:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
	Rook(Color figureColor, const Position& pos);
	std::ostream& print(std::ostream& os);
	FigureType getType() const override;
	void move(const Position& pos) override {
		this->pos = pos;
		hasMoved = true;
	}
	Figure* copy()const {
		return new Rook(*this);
	}
};
