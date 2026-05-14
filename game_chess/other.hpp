#pragma once
#include <cmath>
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
};