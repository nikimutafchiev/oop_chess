#include <iostream>
#include "game.hpp"

Player::Player() :color(Color::WHITE), name("Default"), score(0) {

	}
Player::Player(Color color, std::string name) :color(color), name(name), score(0) {

}
Color Player::getColor()const {
	return color;
}
const std::string& Player::getName()const {
	return name;
}
std::string& Player::getName() {
	return name;
}
int Player::getScore()const {
	return score;
}
void Player::setScore(int newScore) {
	score = newScore;
}
void Player::addScore(int points) {
	score += points;
}
std::ostream& operator<<(std::ostream& os, const Player& p) {
	return os << p.name << ", score:" << p.score;
}

Game::Game() {
	board = nullptr;
	status = GameStatus::NOT_STARTED;
	turn = 0;
}
Position Game::enterCoordinates() {
	std::string coord;
	do {
		coord.clear();
		std::cin >> coord;
		if (coord[0] < 'A' || coord[0]>'H' || coord[1] < '1' || coord[1]>'8') {
			std::cout << "Invalid coordinates, must be (A-H)(1-8)" << std::endl;
		}
		else {
			break;
		}
	} while (true);
	return Position('8' - coord[1], coord[0] - 'A');
}
int Game::processMove(Player& p) {
	std::cout << "Enter move:" << std::endl;
	Position p1 = enterCoordinates();
	Position p2 = enterCoordinates();
	return board->move(p.getColor(), Move(p1,p2));
}
void Game::play() {
	while (!isGameOver()) {
		system("cls");
		std::cout << p[0] <<std::endl;
		std::cout << *board<<std::endl;
		std::cout << p[1] << std::endl;
		std::cout << p[turn].getName() << "'s turn\n";
		
		int score = 0;
		
		while ((score = processMove(p[turn]))<0) {
			std::cout << "INVALID MOVE"<<std::endl;
		}
		p[turn].addScore(score);
		p[turn ^ 1].addScore(-score);
		turn ^= 1;
	}
}

void Game::startGame(std::string name1, std::string name2) {
	board = new Board();
	status = GameStatus::IN_PLAY;
	p[0] = Player(Color::WHITE,name1);
	p[1] = Player(Color::BLACK,name2);
	play();

}

Game* Game::instance = nullptr;
Game* Game::getInstance() {
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}
bool Game::isCheck() {
	//for allPossibleMoves, if dest == King return true;
	return false;
}
bool Game::isCheckmate() {
	if (true) {
		this->status = GameStatus::CHECKMATE;
	}
	return false;
}
bool Game::isStalemate() {
	if (true) {
		this->status = GameStatus::STALEMATE;
	}
	return false;
}
bool Game::isDeadPosition(){
	if (true) {
		//if(figureCount == 2 && kingsCount == 2)
		this->status = GameStatus::DEAD_POSITION;
	}
	return false;
}
bool Game::isGameOver() {
	return isCheckmate() || isStalemate() || isDeadPosition();
}