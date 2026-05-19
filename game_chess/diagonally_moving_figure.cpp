#include "diagonally_moving_figure.hpp"


DiagonallyMovingFigure::DiagonallyMovingFigure(Color figureColor, const Position& pos, unsigned points) :Figure(figureColor, pos, points) {

}
void DiagonallyMovingFigure::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	board.goRoute(pos, { pos.x + 1,pos.y + 1 }, 1, 1, figureColor, res);
	board.goRoute(pos, { pos.x + 1,pos.y - 1 }, 1, -1, figureColor, res);
	board.goRoute(pos, { pos.x - 1,pos.y - 1 }, -1, -1, figureColor, res);
	board.goRoute(pos, { pos.x - 1,pos.y + 1 }, -1, 1, figureColor, res);
}

bool DiagonallyMovingFigure::canMove(const Board& board, const Position& dest)const {
	if (!board.isValidPosition(dest))return false;
	int deltaX = Position::deltaX(dest, pos), deltaY = Position::deltaY(dest, pos);

	int northSouthDirection = deltaX > 0 ? 1 : -1;
	int eastWestDirection = deltaY > 0 ? 1 : -1;
	if (!deltaX || !deltaY)
		return false;
	if (deltaX != deltaY) {
		//checks if it is on the right to left diagonal
		if (pos.x + pos.y != dest.x + dest.y) {
			return false;
		}
	}//checks if it is on the left to right diagonal
	else if (pos.x - dest.x != pos.y - dest.y) {
		return false;
	}
	for (int i = pos.x + northSouthDirection, j = pos.y + eastWestDirection; i != dest.x; i += northSouthDirection, j += eastWestDirection) {
		if (board[Position(i, j)].hasFigure())
			return false;
	}
	if (board[dest].hasFigure())
		return !board[dest].isFriendFigure(this);
	return true;
}