#include <iostream>
#include <fstream>
#include "game.hpp"
#include "player.hpp"


Game::Game() {
	status = GameStatus::NOT_STARTED;
	p[0].setColor(Color::WHITE);
	p[1].setColor(Color::BLACK);

	turn = 0;
}
Position Game::enterCoordinates() const{
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
Move Game::enterMove()const {
	std::cout << "Enter starting position:";
	Position p1 = enterCoordinates();
	std::cout << "Enter destination position:";
	Position p2 = enterCoordinates();
	return Move(p1, p2);
}
int Game::enterOption()const {
	std::cout << "Enter 1 to start new game, 2 to load game, 3 to exit\n";
	int option;
	std::cout << "* Start new game (1)" << std::endl;
	std::cout << "* Load game from file (2) " << std::endl;
	std::cout << "* Exit (3)" << std::endl;
	do {
		std::cin >> option;
		if (option < 1 || option > 3) {

			std::cout << "Invalid option, try again\n";
		}
		else {
			break;
		}
	} while (true);
	return option;
}
int Game::processMove(Player& p) {
	Move move = enterMove();
	int result = board.move(p, move);
	//checks are we in check after this move, if true, it undo it
	if (result != -1 && board.isCheck(p.getColor())) {
		board.undoLastMove();
		std::cout << "King is in check, if this move is made" << std::endl;
		return -1;
	}
	return result;
}
void Game::play() {
	status = GameStatus::IN_PLAY;

	while (!isGameOver()) {
		system("cls");
		std::cout << p[0] <<std::endl;
		std::cout << board<<std::endl;
		std::cout << p[1] << std::endl;
		std::cout << p[turn].getName() << "'s turn\n";
		std::cout << (p[turn].isChecked ? "CHECK" : "") << std::endl;
		
		int score = 0;
		
		while ((score = processMove(p[turn]))<0) {
			std::cout << "INVALID MOVE"<<std::endl;
		}
		p[turn].addScore(score);
		p[turn ^ 1].addScore(-score);
		turn ^= 1;
	}
	std::cout << std::endl << status << std::endl;
}

void Game::start() {
	std::cout << "CHESS" << std::endl;
	int option = enterOption();
	std::string filename;
	switch (option) {
		case 1:
			std::cout << "Enter name for white player:\n";
			std::cin >> p[0].getName();
			std::cout << "Enter name for black player:\n";
			std::cin >> p[1].getName();
			break;
		case 2:
			std::cout << "Enter filename: \n";
			std::cin >> filename;
			{
				std::ifstream file(filename);
				if (!file.is_open()) {
					std::cout << "Failed to open file\n";
					return;
				}
				this->deserialize(file);
			}
			break;
		case 3:
			board = nullptr;
			return;
	}
	play();
}

Game* Game::getInstance() {
	static Game instance;

	return &instance;
}

//first we get the all possible moves of our opponent and determine is our king at danger, after that we move the king to all its possible moves and check again
bool Game::isCheckmate() {
	//gets all the possible nexr moves for the other player, to determine are we in check
	//colors in variable /todo
	Color playerColor = p[turn].getColor();
	bool isChecked = board.isCheck(playerColor);
	if (isChecked) {
		std::vector<Move> moves;
		
		Board copy(board);
		copy.getAllPossibleMoves(playerColor, moves);
		for (Move move : moves) {
			copy.move(p[turn], move);
			
			if (!copy.isCheck(playerColor)) {
				p[turn].isChecked = true;
				return false;
			}
			
			copy.undoLastMove();
		}
		this->status = GameStatus::CHECKMATE;
		p[turn].isChecked = true;
		return true;
	}
	p[turn].isChecked = false;
	return false;
}
bool Game::isStalemate() {
	if (false) {
		this->status = GameStatus::STALEMATE;
	}
	return false;
}
bool Game::isDeadPosition(){

	if (board.getFigureCount() == 2 && board.getFigureCount(FigureType::KING) == 2) {
		this->status = GameStatus::DEAD_POSITION;
		return true;
	}
	return false;
}
bool Game::isGameOver() {
	return isCheckmate()||isStalemate() || isDeadPosition();
}
void Game::serialize(std::ostream& os) const {
	if (status != GameStatus::NOT_STARTED) {
		board.serialize(os);
		for (int i = 0; i < 2; i++) {
			os << "\n";
			p[i].serialize(os);
		}
		os << "\n" << turn;
	}
}
void Game::deserialize(std::istream& is) {
	board.deserialize(is);
	for (int i = 0; i < 2; i++) {
		p[i].deserialize(is);
	}
	is >> turn;
}