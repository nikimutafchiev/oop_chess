#include <iostream>
#include "figure.hpp"
#include "board.hpp"
Figure::Figure(Color figureColor, const Position& pos, unsigned points) :figureColor(figureColor), points(points), pos(pos) {

}

Figure* Figure::factory(FigureType ft, Color color, const Position&initial_position) {
	switch (ft) {
	case FigureType::PAWN:
		return new Pawn(color,initial_position);
	case FigureType::ROOK:
		return new Rook(color,initial_position);
	case FigureType::KNIGHT:
		return new Knight(color,initial_position);
	case FigureType::BISHOP:
		return new Bishop(color,initial_position);
	case FigureType::QUEEN:
		return new Queen(color,initial_position);
	case FigureType::KING:
		return new King(color,initial_position);
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
bool Pawn::canMove(const Board& board, const Position& dest)const {
	if (!board.isValidPosition(dest))return false;
	//determines the direction to where the pieces will be headed, depending on the figure color
	int step = board.pawnDirection(this->figureColor);
	bool isValidMove = false;
	int deltaX = Position::deltaX(dest, pos),absDeltaY = Position::absDeltaY(dest, pos);

	if (pos.y == dest.y && !board[dest].hasFigure()) {
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
Pawn::Pawn(Color figureColor, const Position& pos) :Figure(figureColor, pos,1), hasMoved(false) {

}
FigureType Pawn::getType()const {
	return FigureType::PAWN;
}
std::ostream& Pawn::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Pawn  ";
	return os << "\033[0m";
}
void Pawn::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const{
	//check all moves that can be made by pawn
	int step = board.pawnDirection(this->figureColor);
	Position positions[4] = { {pos.x + step, pos.y }, { pos.x + step * 2,pos.y }, { pos.x + step, pos.y + 1 }, { pos.x + step,pos.y - 1 } };
	for (unsigned i = 0; i < 4;i++) {
		if (this->canMove(board, positions[i]))
			res.push_back(Move(pos, positions[i]));
	}
}
StraightMovingFigure::StraightMovingFigure(Color figureColor, const Position& pos, unsigned points) :Figure(figureColor, pos,points) {

}
void StraightMovingFigure::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	//BFS
}
DiagonallyMovingFigure::DiagonallyMovingFigure(Color figureColor, const Position& pos, unsigned points) :Figure(figureColor, pos,points) {

}
void DiagonallyMovingFigure::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	//BFS
}
bool StraightMovingFigure::canMove(const Board& board, const Position& dest)const{
	if (!board.isValidPosition(dest))return false;
	int deltaX = Position::deltaX(dest, pos), deltaY = Position::deltaY(dest,pos);
	if (!deltaX && deltaY) {
		int direction = deltaY > 0 ? 1 : -1;
		for (int i = pos.y + direction; i != dest.y; i += direction) {
			if (board[Position(dest.x,i)].hasFigure())
				return false;
		}
	}
	else if (deltaX && !deltaY) {
		int direction = deltaX > 0 ? 1 : -1;
		for (int i = pos.x + direction; i != dest.x; i += direction) {
			if (board[Position(i,dest.y)].hasFigure())
				return false;
		}
	}
	if (board[dest].hasFigure())
		return !board[dest].isFriendFigure(this);
	return true;

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

bool Knight::canMove(const Board& board, const Position& dest) const {
	if (!board.isValidPosition(dest))return false;

	int absDeltaX = Position::absDeltaX(pos, dest),absDeltaY = Position::absDeltaY(pos,dest);
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
Knight::Knight(Color figureColor, const Position& pos) :Figure(figureColor, pos,3) {
	
}
std::ostream& Knight::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Knight";
	return os << "\033[0m";
}
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
bool King::canMove(const Board & board, const Position&dest) const {
	if (!board.isValidPosition(dest))return false;
	bool isValidMove = false;
	if (Position::absDeltaX(dest,pos)<=1 && Position::absDeltaY(dest,pos)<=1) {
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
King::King(Color figureColor, const Position& pos) :Figure(figureColor,pos,0),hasMoved(false) {

}
std::ostream& King::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "King  ";
	return os << "\033[0m";
}
void Bishop::getAllPossibleMoves(const Board& board,  std::vector<Move>& res) const {
	DiagonallyMovingFigure::getAllPossibleMoves(board, res);
}
bool Bishop::canMove(const Board& board, const Position&pos) const {
	return DiagonallyMovingFigure::canMove(board, pos);
}
FigureType Bishop::getType()const {
	return FigureType::BISHOP;
}
Bishop::Bishop(Color figureColor, const Position& pos) :Figure(figureColor, pos,3),DiagonallyMovingFigure(figureColor,pos,3) {
	
}
std::ostream& Bishop::print(std::ostream& os)  {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Bishop";
	return os << "\033[0m";
}

bool Queen::canMove(const Board& board, const Position&pos)const {
	return DiagonallyMovingFigure::canMove(board, pos) || StraightMovingFigure::canMove(board, pos);
}
void Queen::getAllPossibleMoves(const Board& board,  std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, res);
	DiagonallyMovingFigure::getAllPossibleMoves(board, res);
}
FigureType Queen::getType()const {
	return FigureType::QUEEN;
}
Queen::Queen(Color figureColor, const Position& pos) :DiagonallyMovingFigure(figureColor,pos, 9) , StraightMovingFigure(figureColor,pos,9), Figure(figureColor, pos,9){
	
}
std::ostream& Queen::print(std::ostream & os) {
	os << (this->figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Queen ";
	return os << "\033[0m";
}

bool Rook::canMove(const Board & board, const Position &dest)const {
	return StraightMovingFigure::canMove(board,dest);

	//add logic for rokada
}
void Rook::getAllPossibleMoves(const Board& board, std::vector<Move>& res) const {
	StraightMovingFigure::getAllPossibleMoves(board, res);
}
FigureType Rook::getType()const {
	return FigureType::ROOK;
}
Rook::Rook(Color figureColor, const Position& pos) :StraightMovingFigure(figureColor,pos, 5), Figure(figureColor,pos, 5),hasMoved(false) {

}
std::ostream& Rook::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Rook  ";
	return os << "\033[0m";
}



