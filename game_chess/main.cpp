#include <iostream>
#include "game.hpp"

int main() {
	Board b;
	std::vector<Move>res;
	b.move(Color::WHITE, Move({ 1,3 }, { 3,3 }));
	b.move(Color::BLACK, Move({ 6,6 }, { 5,6 }));
	b[{0,2}].getFigure()->getAllPossibleMoves(b, res);
	//b[{7, 5}].getFigure()->getAllPossibleMoves(b, res);
	for (auto move : res) {
		std::cout << move << std::endl;
	}
	//Game* g = Game::getInstance();
	//g->startGame("Ivan", "Petkan");
	//
	//Position p1(1, 1),n1(2,1),p2(6,1),n2(5,1);
	//(*board)[p1].getFigure()->canMove(*board, p1, n1);
	//(*board)[p2].getFigure()->canMove(*board, p2, n2);
	//std::cout << *board;
}