#include "king.hpp"
void King::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	Position positions[] = {
		{pos.x + 1,pos.y},
		{pos.x + 1,pos.y - 1},
		{pos.x + 1,pos.y + 1},
		{ pos.x ,pos.y + 1 },
	{ pos.x ,pos.y - 1},
	{ pos.x - 1,pos.y - 1 },
	{ pos.x - 1,pos.y },
	{ pos.x - 1,pos.y + 1 }
	};
	for (int i = 0; i < 8; i++) {
		if (this->canMove(board, positions[i]))
			res.push_back(Move(pos, positions[i]));
	}
}
bool King::canMove(const Board& board, const Position& dest) const {
	if (!board.isValidPosition(dest))return false;
	bool isValidMove = false;
	if (Position::absDeltaX(dest, pos) <= 1 && Position::absDeltaY(dest, pos) <= 1) {
		if (board[dest].hasFigure()) {
			isValidMove = board[dest].isFriendFigure(this);
		}
		else
			isValidMove = true;
	}
	return isValidMove;
}
FigureType King::getType()const {
	return FigureType::KING;
}
King::King(Color figureColor, const Position& pos) :Figure(figureColor, pos, 0), hasMoved(false) {

}
std::ostream& King::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "King  ";
	return os << "\033[0m";
}
void King::serialize(std::ostream& os)const {
	os << "[King] " << (figureColor == Color::WHITE ? "w" : "b") << " " << pos << " " << hasMoved;
}
void King::deserialize(std::istream& is) {
	char c;
	is >> c;
	if (c == 'w') {
		figureColor = Color::WHITE;
	}
	else if (c == 'b') {
		figureColor = Color::BLACK;
	}
	is >> pos;
	is >> hasMoved;
}