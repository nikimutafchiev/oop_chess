#include "straight_moving_figure.hpp"
#include "board.hpp"
StraightMovingFigure::StraightMovingFigure(Color figureColor, const Position& pos, unsigned points) :Figure(figureColor, pos, points) {

}
//goint n, w, s, e, looking for possible moves
void StraightMovingFigure::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	board.goRoute(pos, { pos.x + 1,pos.y }, 1, 0, figureColor, res);
	board.goRoute(pos, { pos.x - 1,pos.y }, -1, 0, figureColor, res);
	board.goRoute(pos, { pos.x ,pos.y + 1 }, 0, 1, figureColor, res);
	board.goRoute(pos, { pos.x ,pos.y - 1 }, 0, -1, figureColor, res);
}

bool StraightMovingFigure::canMove(const Board& board, const Position& dest)const {
	if (!board.isValidPosition(dest))return false;
	int deltaX = Position::deltaX(dest, pos), deltaY = Position::deltaY(dest, pos);
	if (!deltaX && deltaY) {
		int direction = deltaY > 0 ? 1 : -1;
		for (int i = pos.y + direction; i != dest.y; i += direction) {
			if (board[Position(dest.x, i)].hasFigure())
				return false;
		}
	}
	else if (deltaX && !deltaY) {
		int direction = deltaX > 0 ? 1 : -1;
		for (int i = pos.x + direction; i != dest.x; i += direction) {
			if (board[Position(i, dest.y)].hasFigure())
				return false;
		}
	}
	if (board[dest].hasFigure())
		return !board[dest].isFriendFigure(this);
	return true;

}