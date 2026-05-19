#include "knight.hpp"


bool Knight::canMove(const Board& board, const Position& dest) const {
	if (!board.isValidPosition(dest))return false;

	int absDeltaX = Position::absDeltaX(pos, dest), absDeltaY = Position::absDeltaY(pos, dest);
	if (absDeltaX == 2 && absDeltaY == 1 || absDeltaX == 1 && absDeltaY == 2) {
		if (board[dest].hasFigure())
			return !board[dest].isFriendFigure(this);
		else
			return true;
	}
	return false;
}
void Knight::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	Position positions[8] = {
		{pos.x + 1,pos.y + 2},
		{pos.x + 1, pos.y - 2},
		{pos.x + 2, pos.y + 1},
		{pos.x + 2, pos.y - 1},
		{pos.x - 1, pos.y + 2},
		{pos.x - 1, pos.y - 2},
		{pos.x - 2, pos.y + 1},
		{pos.x - 2, pos.y - 1}
	};
	for (unsigned i = 0; i < 8; i++) {
		if (this->canMove(board, positions[i]))
			res.push_back(Move(pos, positions[i]));
	}
}
FigureType Knight::getType()const {
	return FigureType::KNIGHT;
}
Knight::Knight(Color figureColor, const Position& pos) :Figure(figureColor, pos, 3) {

}
std::ostream& Knight::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Knight";
	return os << "\033[0m";
}