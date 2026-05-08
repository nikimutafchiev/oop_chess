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
bool Pawn::canMove(const Board& board, const Position& oldPos, const Position& newPos) {
	//determines the direction to where the pieces will be headed, depending on the figure color
	int step = this->figureColor == Color::WHITE ? 1 : -1;
	bool isValidMove = false;
	int deltaX = Position::deltaX(newPos, oldPos),deltaY = Position::deltaY(newPos, oldPos);
	if (oldPos.y == newPos.y && !board[newPos].hasFigure()) {
		if (deltaX ==  step) {
			isValidMove = true;
		}
		else if (!hasMoved && deltaX == step * 2) {
			isValidMove = true;
		}
	}
	//checks the NW NE move if there is a figure or not
	else if (std::abs(deltaY) == 1 && deltaX == step)
	{
		if (board[newPos].hasFigure())
			isValidMove = !board[newPos].isFriendFigure(this);
	}
	if (isValidMove)
		hasMoved = true;
	return isValidMove;
}
Pawn::Pawn(Color figureColor) :Figure(figureColor, 1), hasMoved(false) {

}
std::ostream& Pawn::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Pawn  ";
	return os << "\033[0m";
}
StraightMovingFigure::StraightMovingFigure(Color figureColor, unsigned points) :Figure(figureColor, points) {

}
DiagonallyMovingFigure::DiagonallyMovingFigure(Color figureColor, unsigned points) :Figure(figureColor, points) {

}
bool StraightMovingFigure::canMoveStraight(const Board& board, const Position& oldPos, const Position& newPos) {
	int deltaX = Position::deltaX(newPos, oldPos), deltaY = Position::deltaY(newPos,oldPos);
	if (!deltaX && deltaY) {
		int direction = deltaY > 0 ? 1 : -1;
		for (int i = oldPos.y + direction; i != newPos.y; i += direction) {
			if (board[Position(newPos.x,i)].hasFigure())
				return false;
		}
	}
	else if (deltaX && !deltaY) {
		int direction = deltaX > 0 ? 1 : -1;
		for (int i = oldPos.x + direction; i != newPos.x; i += direction) {
			if (board[Position(i,newPos.y)].hasFigure())
				return false;
		}
	}
	if (board[newPos].hasFigure())
		return !board[newPos].isFriendFigure(this);
	return true;

}
bool DiagonallyMovingFigure::canMoveDiagonally(const Board& board, const Position& oldPos, const Position& newPos) {
	int deltaX = Position::deltaX(newPos, oldPos), deltaY = Position::deltaY(newPos, oldPos);

	int northSouthDirection = deltaX > 0 ? 1 : -1;
	int eastWestDirection = deltaY > 0 ? 1 : -1;
	if (!deltaX || !deltaY)
		return false;
	if (deltaY < 0) {
		//checks if it is on the right to left diagonal
		if (oldPos.x + oldPos.y != newPos.x + newPos.y) {
			return false;
		}
	}//checks if it is on the left to right diagonal
	else if (deltaX != deltaY) {
		return false;
	}
	for (int i = oldPos.x + northSouthDirection, j = oldPos.y + eastWestDirection; i != newPos.x; i += northSouthDirection, j += eastWestDirection) {
		if (board[Position(i, j)].hasFigure())
			return false;
	}
	if (board[newPos].hasFigure())
		return !board[newPos].isFriendFigure(this);
	return true;
}

bool Knight::canMove(const Board& board, const Position& oldPos, const Position& newPos) {
	int deltaX = Position::deltaX(oldPos, newPos),deltaY = Position::deltaY(oldPos, newPos);
	if (std::abs(deltaX) == 2 && std::abs(deltaY) == 1 || std::abs(deltaX) == 1 && std::abs(deltaY) == 2) {
		if (board[newPos].hasFigure()) 
			return !board[newPos].isFriendFigure(this);
		else
			return true;
	}
	return false;
}
Knight::Knight(Color figureColor) :Figure(figureColor, 3) {
	
}
std::ostream& Knight::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Knight";
	return os << "\033[0m";
}

bool King::canMove(const Board & board, const Position & oldPos, const Position & newPos)  {
	bool isValidMove = false;
	if (std::abs(Position::deltaX(newPos,oldPos))<=1 && std::abs(Position::deltaY(newPos,oldPos))<=1) {
		if (board[newPos].hasFigure()) {
			isValidMove = board[newPos].isFriendFigure(this);
		}
		else
			isValidMove = true;
	}
	if (isValidMove)
		hasMoved = true;
	return isValidMove;
}
King::King(Color figureColor) :Figure(figureColor,0),hasMoved(false) {

}
std::ostream& King::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "King  ";
	return os << "\033[0m";
}

bool Bishop::canMove(const Board& board, const Position& oldPos, const Position& newPos)  {
	return canMoveDiagonally(board, oldPos, newPos);
}
Bishop::Bishop(Color figureColor) :Figure(figureColor, 3),DiagonallyMovingFigure(figureColor,3) {
	
}
std::ostream& Bishop::print(std::ostream& os)  {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Bishop";
	return os << "\033[0m";
}

bool Queen::canMove(const Board& board, const Position& oldPos, const Position& newPos) {
	return canMoveDiagonally(board,oldPos,newPos)||canMoveStraight(board,oldPos,newPos);
}
Queen::Queen(Color figureColor) :DiagonallyMovingFigure(figureColor, 9) , StraightMovingFigure(figureColor,9), Figure(figureColor, 9){

}
std::ostream& Queen::print(std::ostream & os) {
	os << (this->figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Queen ";
	return os << "\033[0m";
}

bool Rook::canMove(const Board & board, const Position & oldPos, const Position & newPos) {
	return canMoveStraight(board,oldPos,newPos);

	//add logic for rokada
}
Rook::Rook(Color figureColor) :StraightMovingFigure(figureColor, 5), Figure(figureColor, 5),hasMoved(false) {

}
std::ostream& Rook::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Rook  ";
	return os << "\033[0m";
}



