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
Color Figure::getColor() {
	return figureColor;
}
unsigned Figure::getPoints()const {
	return points;
}
bool Pawn::canMove(Board& board, const Position& oldPos, const Position& newPos) {
	//determines the direction to where the pieces will be headed, depending on the figure color
	int step = (this->figureColor == Color::WHITE ? 1 : -1);
	bool isValidMove = false;
	if (oldPos.y == newPos.y && !board[newPos].hasFigure()) {
		if (Position::deltaX(newPos, oldPos) ==  step) {
			isValidMove = true;
		}
		else if (!hasMoved && Position::deltaX(newPos, oldPos) == step * 2) {
			isValidMove = true;
		}
	}
	//checks the NW NE move if there is a figure or not
	else if (std::abs(Position::deltaY(newPos, oldPos)) == 1 && Position::deltaX(newPos, oldPos) == step)
	{
		if (board[newPos].hasFigure())
			isValidMove = board[newPos].getFigure()->getColor() != this->figureColor;
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


bool Knight::canMove(Board& board, const Position& oldPos, const Position& newPos) {
	if (true);
	return false;
}
Knight::Knight(Color figureColor) :Figure(figureColor, 3) {

}
std::ostream& Knight::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Knight";
	return os << "\033[0m";
}

bool King::canMove(Board & board, const Position & oldPos, const Position & newPos)  {
	bool isValidMove = false;
	if (std::abs(Position::deltaX(newPos,oldPos))<=1 && std::abs(Position::deltaY(newPos,oldPos))<=1) {
		if (board[newPos].hasFigure()) {
			isValidMove = board[newPos].getFigure()->getColor() != this->figureColor;
		}
		else
			isValidMove = true;
	}
	if (isValidMove)
		hasMoved = true;
	return isValidMove;
}
King::King(Color figureColor) :Figure(figureColor,0) {

}
std::ostream& King::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "King  ";
	return os << "\033[0m";
}

bool Bishop::canMove(Board& board, const Position& oldPos, const Position& newPos)  {
	return true;
}
Bishop::Bishop(Color figureColor) :Figure(figureColor, 3) {

}
std::ostream& Bishop::print(std::ostream& os)  {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Bishop";
	return os << "\033[0m";
}

bool Queen::canMove(Board& board, const Position& oldPos, const Position& newPos) {
	return true;
}
Queen::Queen(Color figureColor) :Figure(figureColor, 9) {

}
std::ostream& Queen::print(std::ostream & os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Queen ";
	return os << "\033[0m";
}

bool Rook::canMove(Board & board, const Position & oldPos, const Position & newPos) {
	return true;
}
Rook::Rook(Color figureColor) :Figure(figureColor, 5) {

}
std::ostream& Rook::print(std::ostream& os) {
	os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
	os << "Rook  ";
	return os << "\033[0m";
}



