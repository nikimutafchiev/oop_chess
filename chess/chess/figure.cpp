#include <iostream>
#include "figure.hpp"

Figure::Figure(Color figureColor, unsigned points) :figureColor(figureColor), points(points) {
}

public:
	static Figure* factory(FigureType ft, Color color);
	Color getColor() {
		return figureColor;
	}
	unsigned getPoints()const {
		return points;
	}
	virtual std::ostream& print(std::ostream& os) = 0;
	virtual bool canMove(Board& board, const Position& oldPos, const Position& newPos) = 0;
};
class Pawn : public Figure {
	bool hasMoved;
public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override;
	Pawn(Color figureColor) :Figure(figureColor, 1), hasMoved(false) {

	}
	std::ostream& print(std::ostream& os)override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Pawn  ";
		return os << "\033[0m";
	}

};
class Knight : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override {
		return true;
	}
	Knight(Color figureColor) :Figure(figureColor, 3) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Knight";
		return os << "\033[0m";
	}

};
class King : public Figure {
	bool hasMoved;

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override {
		return true;
	}
	King(Color figureColor) :Figure(figureColor, 0) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "King  ";
		return os << "\033[0m";
	}
};
class Bishop : public Figure {
	bool hasMoved;

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override {
		return true;
	}
	Bishop(Color figureColor) :Figure(figureColor, 3) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Bishop";
		return os << "\033[0m";
	}
};
class Queen : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override {
		return true;
	}
	Queen(Color figureColor) :Figure(figureColor, 9) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Queen ";
		return os << "\033[0m";
	}
};
class Rook : public Figure {

public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override {
		return true;
	}
	Rook(Color figureColor) :Figure(figureColor, 5) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Rook  ";
		return os << "\033[0m";
	}
};

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

