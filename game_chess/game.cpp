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
Move Game::enterMove() {
	std::cout << "Enter starting position:";
	Position p1 = enterCoordinates();
	std::cout << "Enter destination position:";
	Position p2 = enterCoordinates();
	return Move(p1, p2);
}
int Game::processMove(Player& p) {
	return board->move(p.getColor(), enterMove());
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
bool Game::isCheck(const std::vector<Move>& moves) {
	Position kingPosition = board->getKingPosition(p[turn].getColor());
	for (Move move : moves) {
		if ((*board)[move.dest].hasFigure() && move.dest == kingPosition) {
			return true;
		}
	}
	//for allPossibleMoves, if dest == King return true;
	return false;
}
//first we get the all possible moves of our opponent and determine is our king at danger, after that we move the king to all its possible moves and check again
bool Game::isCheckmate() {
	std::vector<Move> possibleMoves;
	//gets all the possible nexr moves for the other player, to determine are we in check
	//colors in variable /todo
	board->getAllPossibleMoves(p[turn^1].getColor(), possibleMoves);
	Position kingPosition = board->getKingPosition(p[turn].getColor());
	if (isCheck(possibleMoves)) {
		std::vector<Move> kingMoves;
		(*board)[kingPosition].getFigure()->getAllPossibleMoves(*board, kingMoves);
		Board copy(*board);
		for (Move move : kingMoves) {
			possibleMoves.clear();
			copy.move(p[turn].getColor(), move);
			copy.getAllPossibleMoves(p[turn ^ 1].getColor(), possibleMoves);
			copy.undoMove();
			if (!isCheck(possibleMoves))
				return false;
		}
		return true;
	}
	return false;
	return false;
}
bool Game::isStalemate() {
	if (true) {
		this->status = GameStatus::STALEMATE;
	}
	return false;
}
bool Game::isDeadPosition(){

	if (board->getFigureCount() == 2 && board->getFigureCount(FigureType::KING) == 2) {
		this->status = GameStatus::DEAD_POSITION;
		return true;
	}
	return false;
}
bool Game::isGameOver() {
	return isStalemate() || isDeadPosition();
}