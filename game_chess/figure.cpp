#include <iostream>
#include "figure.hpp"
#include "board.hpp"
Figure::Figure(Color figureColor, unsigned points) :figureColor(figureColor), points(points) {

}

Figure* Figure::factory(FigureType ft, Color color) {
	switch (ft) {
	case FigureType::PAWN:
		return new Pawn(color);
	case FigureType::ROOK:
		return new Rook(color);
	case FigureType::KNIGHT:
		return new Knight(color);
	case FigureType::BISHOP:
		return new Bishop(color);
	case FigureType::QUEEN:
		return new Queen(color);
	case FigureType::KING:
		return new King(color);
	default:return nullptr;
	}
	return nullptr;
}
Color Figure::getColor() const{
	return figureColor;
}
unsigned Figure::getPoints()const {
	return points;
}

bool Pawn::canTransform(const Board&board, const Position&p) {
	return board.pawnEnd(figureColor) == p.x;
}
bool Pawn::canMove(const Board& board, const Move& move)const {
	if (!board.isValidPosition(move.dest))return false;
	//determines the direction to where the pieces will be headed, depending on the figure color
	int step = board.pawnDirection(this->figureColor);
	bool isValidMove = false;
	Position dest = move.dest, src = move.src;
	int deltaX = Position::deltaX(dest, src),absDeltaY = Position::absDeltaY(dest, src);

	if (src.y == dest.y && !board[dest].hasFigure()) {
		if (deltaX ==  step) {
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
Pawn::Pawn(Color figureColor) :Figure(figureColor, 1), hasMoved(false) {

}
FigureType Pawn::getType()const {
	return FigureType::PAWN;
}
std::ostream& Pawn::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Pawn  ";
	return os << "\033[0m";
}
void Pawn::getAllPossibleMoves(const Board& board,const Position& pos, std::vector<Move>& res) const{
	//check all moves that can be made by pawn
	int step = board.pawnDirection(this->figureColor);
	Position positions[4] = { {pos.x + step, pos.y }, { pos.x + step * 2,pos.y }, { pos.x + step, pos.y + 1 }, { pos.x + step,pos.y - 1 } };
	for (unsigned i = 0; i < 4;i++) {
		Move move(pos, positions[i]);
		if (this->canMove(board, move))
			res.push_back(move);
	}
}
StraightMovingFigure::StraightMovingFigure(Color figureColor, unsigned points) :Figure(figureColor, points) {

}
void StraightMovingFigure::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {
	//BFS
}
DiagonallyMovingFigure::DiagonallyMovingFigure(Color figureColor, unsigned points) :Figure(figureColor, points) {

}
void DiagonallyMovingFigure::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {
	//BFS
}
bool StraightMovingFigure::canMove(const Board& board, const Move& move)const{
	if (!board.isValidPosition(move.dest))return false;
	Position src = move.src, dest = move.dest;
	int deltaX = Position::deltaX(dest, src), deltaY = Position::deltaY(dest,src);
	if (!deltaX && deltaY) {
		int direction = deltaY > 0 ? 1 : -1;
		for (int i = src.y + direction; i != dest.y; i += direction) {
			if (board[Position(dest.x,i)].hasFigure())
				return false;
		}
	}
	else if (deltaX && !deltaY) {
		int direction = deltaX > 0 ? 1 : -1;
		for (int i = src.x + direction; i != dest.x; i += direction) {
			if (board[Position(i,dest.y)].hasFigure())
				return false;
		}
	}
	if (board[dest].hasFigure())
		return !board[dest].isFriendFigure(this);
	return true;

}
bool DiagonallyMovingFigure::canMove(const Board& board, const Move&move)const {
	if (!board.isValidPosition(move.dest))return false;
	Position src = move.src, dest = move.dest;
	int deltaX = Position::deltaX(dest, src), deltaY = Position::deltaY(dest, src);

	int northSouthDirection = deltaX > 0 ? 1 : -1;
	int eastWestDirection = deltaY > 0 ? 1 : -1;
	if (!deltaX || !deltaY)
		return false;
	//TODO: bug
	if (deltaX != deltaY) {
		//checks if it is on the right to left diagonal
		if (src.x + src.y != dest.x + dest.y) {
			return false;
		}
	}//checks if it is on the left to right diagonal
	else if (src.x - dest.x != src.y - dest.y) {
		return false;
	}
	for (int i = src.x + northSouthDirection, j = src.y + eastWestDirection; i != dest.x; i += northSouthDirection, j += eastWestDirection) {
		if (board[Position(i, j)].hasFigure())
			return false;
	}
	if (board[dest].hasFigure())
		return !board[dest].isFriendFigure(this);
	return true;
}

bool Knight::canMove(const Board& board, const Move& move) const {
	if (!board.isValidPosition(move.dest))return false;
	Position src = move.src, dest = move.dest;
	int absDeltaX = Position::absDeltaX(src, dest),absDeltaY = Position::absDeltaY(src,dest);
	if (absDeltaX == 2 && absDeltaY == 1 || absDeltaX == 1 && absDeltaY == 2) {
		if (board[dest].hasFigure()) 
			return !board[dest].isFriendFigure(this);
		else
			return true;
	}
	return false;
}
void Knight::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {

}
FigureType Knight::getType()const {
	return FigureType::KNIGHT;
}
Knight::Knight(Color figureColor) :Figure(figureColor, 3) {
	
}
std::ostream& Knight::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Knight";
	return os << "\033[0m";
}
void King::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {

}
bool King::canMove(const Board & board, const Move& move) const {
	if (!board.isValidPosition(move.dest))return false;
	Position src = move.src, dest = move.dest;
	bool isValidMove = false;
	if (Position::absDeltaX(dest,src)<=1 && Position::absDeltaY(dest,src)<=1) {
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
King::King(Color figureColor) :Figure(figureColor,0),hasMoved(false) {

}
std::ostream& King::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "King  ";
	return os << "\033[0m";
}
void Bishop::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {
	DiagonallyMovingFigure::getAllPossibleMoves(board, pos, res);
}
bool Bishop::canMove(const Board& board, const Move& move) const {
	return DiagonallyMovingFigure::canMove(board, move);
}
FigureType Bishop::getType()const {
	return FigureType::BISHOP;
}
Bishop::Bishop(Color figureColor) :Figure(figureColor, 3),DiagonallyMovingFigure(figureColor,3) {
	
}
std::ostream& Bishop::print(std::ostream& os)  {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Bishop";
	return os << "\033[0m";
}

bool Queen::canMove(const Board& board, const Move &move)const {
	return DiagonallyMovingFigure::canMove(board, move) || StraightMovingFigure::canMove(board, move);
}
void Queen::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, pos, res);
	DiagonallyMovingFigure::getAllPossibleMoves(board, pos, res);
}
FigureType Queen::getType()const {
	return FigureType::QUEEN;
}
Queen::Queen(Color figureColor) :DiagonallyMovingFigure(figureColor, 9) , StraightMovingFigure(figureColor,9), Figure(figureColor, 9){
	
}
std::ostream& Queen::print(std::ostream & os) {
	os << (this->figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Queen ";
	return os << "\033[0m";
}

bool Rook::canMove(const Board & board, const Move&move)const {
	return StraightMovingFigure::canMove(board, move);

	//add logic for rokada
}
void Rook::getAllPossibleMoves(const Board& board, const Position& pos, std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, pos, res);
}
FigureType Rook::getType()const {
	return FigureType::ROOK;
}
Rook::Rook(Color figureColor) :StraightMovingFigure(figureColor, 5), Figure(figureColor, 5),hasMoved(false) {

}
std::ostream& Rook::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Rook  ";
	return os << "\033[0m";
}



