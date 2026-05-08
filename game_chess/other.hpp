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
	static int deltaX(const Position& p1, const Position& p2) {
		return p1.x - p2.x;
	}
	static int deltaY(const Position& p1, const Position& p2) {
		return p1.y - p2.y;
	}
};
enum class Color {
	BLACK, WHITE
};
enum class FigureType {
	PAWN, ROOK, KNIGHT, QUEEN, KING, BISHOP
};
enum class GameStatus {
	NOT_STARTED, STARTED, IN_PLAY, STALEMATE
};