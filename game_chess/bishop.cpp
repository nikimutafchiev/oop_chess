#include "bishop.hpp"


void Bishop::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	DiagonallyMovingFigure::getAllPossibleMoves(board, res);
}
bool Bishop::canMove(const Board& board, const Position& pos) const {
	return DiagonallyMovingFigure::canMove(board, pos);
}
FigureType Bishop::getType()const {
	return FigureType::BISHOP;
}
Bishop::Bishop(Color figureColor, const Position& pos) :Figure(figureColor, pos, 3), DiagonallyMovingFigure(figureColor, pos, 3) {

}
std::ostream& Bishop::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Bishop";
	return os << "\033[0m";
}
