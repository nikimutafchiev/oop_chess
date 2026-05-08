#include <iostream>
#include "game.hpp"

int main() {
	Game* g = Game::getInstance();
	g->startGame("Ivan", "Petkan");
	//Position p1(1, 1),n1(2,1),p2(6,1),n2(5,1);
	//(*board)[p1].getFigure()->canMove(*board, p1, n1);
	//(*board)[p2].getFigure()->canMove(*board, p2, n2);
	//std::cout << *board;
}