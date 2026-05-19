#pragma once
#include "figure.hpp"
#include "board.hpp"

class DiagonallyMovingFigure : virtual public Figure {
protected:
	bool canMove(const Board& board, const Position& dest)const override;
	void getAllPossibleMoves(const Board& board, std::vector<Move>& res) const override;
public:
	DiagonallyMovingFigure(Color figureColor, const Position& pos, unsigned points);


};