#include "pawn.hpp"
#include "board.hpp"

bool Pawn::canTransform(const Board& board, const Position& p) {
	return board.promotionRank(figureColor) == p.x;
}
bool Pawn::canMove(const Board& board, const Position& dest)const {
	if (!board.isValidPosition(dest))
		return false;
	//determines the direction to where the pieces will be headed, depending on the figure color
	int step = board.pawnDirection(this->figureColor);
	bool isValidMove = false;
	int deltaX = Position::deltaX(dest, pos), absDeltaY = Position::absDeltaY(dest, pos);

	if (pos.y == dest.y && !board[dest].hasFigure()) {
		if (deltaX == step) {
			isValidMove = true;
		}
		else if (!hasMoved && deltaX == step * 2) {
			isValidMove = true;
		}
	}
	//checks the NW NE move if there is a figure or not
	else if (absDeltaY == 1 && deltaX == step)
	{
		if (board[dest].hasFigure())
			isValidMove = !board[dest].isFriendFigure(this);
	}
	return isValidMove;
}
Pawn::Pawn(Color figureColor, const Position& pos) :Figure(figureColor, pos, 1), hasMoved(false) {

}
FigureType Pawn::getType()const {
	return FigureType::PAWN;
}
std::ostream& Pawn::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Pawn  ";
	return os << "\033[0m";
}
void Pawn::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	//check all moves that can be made by pawn
	int step = board.pawnDirection(this->figureColor);
	Position positions[4] = { {pos.x + step, pos.y }, { pos.x + step * 2,pos.y }, { pos.x + step, pos.y + 1 }, { pos.x + step,pos.y - 1 } };
	for (unsigned i = 0; i < 4; i++) {
		if (this->canMove(board, positions[i]))
			res.push_back(Move(pos, positions[i]));
	}
}
void Pawn::serialize(std::ostream& os)const {
	os << "[Pawn] " << (figureColor == Color::WHITE ? "w" : "b") << " " << pos << " " << hasMoved;
}
void Pawn::deserialize(std::istream& is) {
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
//Figure* Pawn::promote() const {
//	std::string choice;
//	std::cout << "Your pawn can be promoted (rook, knight, bishop, queen)" << std::endl;
//	std::cin >> choice;
//	if (choice == "rook") {
//		return Figure::factory(FigureType::ROOK,figureColor, pos);
//	}
//	else if (choice == "knight") {
//		return Figure::factory(FigureType::KNIGHT,figureColor, pos);
//	}
//	else if (choice == "bishop") {
//		return Figure::factory(FigureType::BISHOP,figureColor, pos);
//	}
//	else if (choice == "queen") {
//		return Figure::factory(FigureType::QUEEN,figureColor, pos);
//	}
//	return nullptr;
//}