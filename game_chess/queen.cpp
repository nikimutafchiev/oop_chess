#include "queen.hpp"


bool Queen::canMove(const Board& board, const Position& pos)const {
	return DiagonallyMovingFigure::canMove(board, pos) || StraightMovingFigure::canMove(board, pos);
}
void Queen::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, res);
	DiagonallyMovingFigure::getAllPossibleMoves(board, res);
}
FigureType Queen::getType()const {
	return FigureType::QUEEN;
}
Queen::Queen(Color figureColor, const Position& pos) :DiagonallyMovingFigure(figureColor, pos, 9), StraightMovingFigure(figureColor, pos, 9), Figure(figureColor, pos, 9) {

}
std::ostream& Queen::print(std::ostream& os) {
	os << (this->figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Queen ";
	return os << "\033[0m";
}
