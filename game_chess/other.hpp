#pragma once
#include <cmath>
#include <iostream>
struct Position {
	unsigned x;
	unsigned y;
	int deltaX(const Position &other) {
		return x - other.x;
	}
	int deltaY(const Position& other) {
		return y - other.y;
	}
	unsigned absDeltaX(const Position& other) {
		return abs(deltaX(other));
	}
	unsigned absDeltaY(const Position& other) {
		return abs(deltaY(other));
	}
	static int deltaX(const Position& p1, const Position& p2) {
		return p1.x - p2.x;
	}
	static int deltaY(const Position& p1, const Position& p2) {
		return p1.y - p2.y;
	}
	static int absDeltaX(const Position& p1, const Position& p2) {
		return abs(deltaX(p1, p2));
	}
	static int absDeltaY(const Position& p1, const Position& p2) {
		return abs(deltaY(p1, p2));
	}
	friend std::ostream& operator<<(std::ostream& os, const Position& p) {
		return os << "(" << p.x << "," << p.y << ")";
	}
	friend std::istream& operator>>(std::istream& is, Position& p) {
		char c;
		is >> c;
		if (c != '(') {
			throw "Unexpected character, expected (";
		}
		is >> p.x;
		is >> c;
		if (c != ',') {
			throw "Unexpected character, expected ,";
		}
		is >> p.y;
		is >> c;
		if (c != ')') {
			throw "Unexpected character, expected )";
		}
		return is;
	}
	bool operator==(const Position& other) {
		return other.x == x && other.y == y;
	}
	bool operator!=(const Position& other) {
		return !this->operator==(other);
	}

};
enum class Color {
	BLACK, WHITE
};
enum class FigureType {
	PAWN, ROOK, KNIGHT, QUEEN, KING, BISHOP
};
enum class GameStatus {
	NOT_STARTED, IN_PLAY, STALEMATE, CHECKMATE, DEAD_POSITION
};
struct Move {
	Position src;
	Position dest;
	friend std::ostream& operator<<(std::ostream& os, const Move &move) {
		return os << move.src << "->" << move.dest;
	}
};