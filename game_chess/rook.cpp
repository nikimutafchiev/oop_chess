#include "rook.hpp"
bool Rook::canMove(const Board& board, const Position& dest)const {
	return StraightMovingFigure::canMove(board, dest);

	//add logic for rokada
}
void Rook::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, res);
}
FigureType Rook::getType()const {
	return FigureType::ROOK;
}
Rook::Rook(Color figureColor, const Position& pos) :StraightMovingFigure(figureColor, pos, 5), Figure(figureColor, pos, 5), hasMoved(false) {

}
std::ostream& Rook::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Rook  ";
	return os << "\033[0m";
}