#include <iostream>
#include "figure.hpp"
#include "board.hpp"
#include "pawn.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "queen.hpp"
#include "rook.hpp"
Figure::Figure(Color figureColor, const Position& pos, unsigned points) :figureColor(figureColor), points(points), pos(pos) {

}
Figure* Figure::factory(FigureType ft) {
	switch (ft) {
	case FigureType::PAWN:
		return new Pawn(Color::WHITE, { 0,0 });
	case FigureType::ROOK:
		return new Rook(Color::WHITE, { 0,0 });
	case FigureType::KNIGHT:
		return new Knight(Color::WHITE, { 0,0 });
	case FigureType::BISHOP:
		return new Bishop(Color::WHITE, { 0,0 });
	case FigureType::QUEEN:
		return new Queen(Color::WHITE, { 0,0 });
	case FigureType::KING:
		return new King(Color::WHITE, { 0,0 });
	default:return nullptr;
	}
}
Figure* Figure::factory(FigureType ft, Color color, const Position&initial_position) {
	switch (ft) {
	case FigureType::PAWN:
		return new Pawn(color, initial_position);
	case FigureType::ROOK:
		return new Rook(color, initial_position);
	case FigureType::KNIGHT:
		return new Knight(color, initial_position);
	case FigureType::BISHOP:
		return new Bishop(color, initial_position);
	case FigureType::QUEEN:
		return new Queen(color, initial_position);
	case FigureType::KING:
		return new King(color, initial_position);
	default:return nullptr;
	}
}






