#include <iostream>
#include <cmath>
struct Position {
	int x;
	int y;
};
enum class Color {
	BLACK, WHITE
};
enum class FigureType {
	PAWN, ROOK, KNIGHT,QUEEN, KING, BISHOP
};
class Board;
class Figure {
	const unsigned points;
protected:
	Color figureColor;
	Figure(Color figureColor,unsigned points):figureColor(figureColor),points(points) {

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
	//board?
public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos)override;
	Pawn(Color figureColor):Figure(figureColor,1),hasMoved(false) {

	}
	std::ostream& print (std::ostream& os)override{
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
	Knight(Color figureColor) :Figure(figureColor,3) {

	}
	std::ostream& print(std::ostream& os) override{
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Knight";
		return os << "\033[0m";
	}
	
};
class King : public Figure {
	
	
public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override {
		return true;
	}
	King(Color figureColor) :Figure(figureColor,0) {

	}
	std::ostream& print (std::ostream& os) override{
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "King  ";
		return os << "\033[0m";
	}
};
class Bishop : public Figure {
	
	
public:
	bool canMove(Board& board, const Position& oldPos, const Position& newPos) override {
		return true;
	}
	Bishop(Color figureColor) :Figure(figureColor,3) {

	}
	std::ostream& print(std::ostream& os) override{
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
	Queen(Color figureColor) :Figure(figureColor,9) {

	}
	std::ostream& print(std::ostream& os) override {
		os << (figureColor == Color::WHITE ? "\033[33m" : "\033[34m");
		os << "Queen ";
		return os << "\033[0m";
	}
};
class Rook : public Figure {
	
public:
	bool canMove(Board& board, const Position& oldPos,const Position& newPos)override {
		return true;
	}
	Rook(Color figureColor) :Figure(figureColor,5) {

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


class BoardCell {

	Figure* fig;
	Position pos;
	Color color;
public:
	BoardCell() = default;
	BoardCell(Figure* fig, Position pos, Color color) :fig(fig), pos(pos), color(color) {

	}
	void setFigure(Figure* f) {
		fig = f;
	}
	Figure* getFigure() {
		return fig;
	}
	const Figure* getFigure() const {
		return fig;
	}
	Color getColor() const {
		return color;
	}
	friend std::ostream& operator<<(std::ostream& os, const BoardCell& bc) {
		os << (bc.color == Color::WHITE ? "\033[47m" : "");
		if (bc.fig == nullptr) {
			os << "      ";
		}
		else {
			bc.fig->print(os);
		}
		os << "\033[0m";
		return os;
	}
};
constexpr int BOARD_SIZE = 8;
class Board {
	BoardCell arr[BOARD_SIZE][BOARD_SIZE];
	void initDefaultBoard() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				arr[i][j] = { nullptr, {i,j},((i + j) % 2 == 0 ? Color::BLACK : Color::WHITE) };
			}
		}
		arr[0][0].setFigure(Figure::factory(FigureType::ROOK,Color::WHITE));
		arr[0][1].setFigure(Figure::factory(FigureType::KNIGHT,Color::WHITE));
		arr[0][2].setFigure(Figure::factory(FigureType::BISHOP,Color::WHITE));
		arr[0][3].setFigure(Figure::factory(FigureType::QUEEN,Color::WHITE));
		arr[0][4].setFigure(Figure::factory(FigureType::KING,Color::WHITE));
		arr[0][5].setFigure(Figure::factory(FigureType::BISHOP,Color::WHITE));
		arr[0][6].setFigure(Figure::factory(FigureType::KNIGHT,Color::WHITE));
		arr[0][7].setFigure(Figure::factory(FigureType::ROOK,Color::WHITE));
		for (int i = 0; i < BOARD_SIZE; i++) {
			arr[1][i].setFigure(Figure::factory(FigureType::PAWN,Color::WHITE));
			arr[6][i].setFigure(Figure::factory(FigureType::PAWN,Color::BLACK));
		}
		arr[7][0].setFigure(Figure::factory(FigureType::ROOK,Color::BLACK));
		arr[7][1].setFigure(Figure::factory(FigureType::KNIGHT,Color::BLACK));
		arr[7][2].setFigure(Figure::factory(FigureType::BISHOP,Color::BLACK));
		arr[7][3].setFigure(Figure::factory(FigureType::QUEEN,Color::BLACK));
		arr[7][4].setFigure(Figure::factory(FigureType::KING,Color::BLACK));
		arr[7][5].setFigure(Figure::factory(FigureType::BISHOP,Color::BLACK));
		arr[7][6].setFigure(Figure::factory(FigureType::KNIGHT,Color::BLACK));
		arr[7][7].setFigure(Figure::factory(FigureType::ROOK,Color::BLACK));
	}
public:
	Board() {
		initDefaultBoard();
	}
	Board(BoardCell arr[BOARD_SIZE][BOARD_SIZE]) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				this->arr[i][j] = arr[i][j];
			}
		}
	}
	
	BoardCell& operator[](const Position& p) {
		return arr[p.x][p.y];
	}
	int move(const Position& p1, const Position& p2) {
		Figure* currentFigure = (*this)[p1].getFigure();
		if (!currentFigure)
			return -1;
		if (!currentFigure->canMove(*this, p1, p2))
			return -1;
		return 1;
	}
	friend std::ostream& operator<<(std::ostream& os, Board& board) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			os << 8-i;
			for (int j = 0; j < BOARD_SIZE; j++) {
				os << board.arr[i][j];
			}
			os << "\n";
		}
		os << " ";
		for (int i = 0; i < BOARD_SIZE; i++) {
			os << (char)(i+'A') << "     ";
		}
		os << "\n";
		return os;
	}
	~Board() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				delete arr[i][j].getFigure();
			}
		}
	}
};

bool Pawn::canMove(Board& board, const Position& oldPos, const Position& newPos) {
	{
		int direction = (this->figureColor == Color::WHITE ? 1 : -1);
		if (oldPos.y == newPos.y) {
			if (oldPos.x == newPos.x - direction) {
				board[newPos].setFigure(board[oldPos].getFigure());
				return true;
			}
			else if (!hasMoved && oldPos.x == newPos.x - direction*2) {
				hasMoved = true;
				return true;
			}

		}
		else if(abs(newPos.y-oldPos.y)==1&& oldPos.x == newPos.x - direction){
			if (board[newPos].getFigure()->getColor() == this->figureColor) {
				return false;
			}
			else {
				board[newPos].setFigure(board[oldPos].getFigure());
			}
		}
		return false;
	}
}

class Player {
	Color color;
	std::string name;
	int score;
};

class Game {
	Board* board;
	static Game* instance;
	enum class GameStatus {
		NOT_STARTED, STARTED, IN_PLAY,STALEMATE
	}status;
	Player *p1, *p2;
	int turn;
	Game() {
		board = nullptr;
		status = GameStatus::NOT_STARTED;
		p1 = p2 = nullptr;
	}
	Position enterCoordinates() {
		std::string coord;
		do {
			coord.clear();
			std::cin >> coord;
		} while (coord[0] < 'A' || coord[0]>'H' || coord[1] < '1' || coord[1]>'8');
		return Position( '8'-coord[1], coord[0]-'A');
	}
	void processMove(Player& p) {
		std::cout << "Enter move:" << std::endl;
		Position p1 = enterCoordinates();
		Position p2 = enterCoordinates();
		board->move(p1, p2);	
	}
	void play() {
		while (status == GameStatus::IN_PLAY) {
			std::cout << *board;
			processMove(*p1);
			turn ^= 1;
			

		}
	}
public:
	
	void startGame() {
		board = new Board();
		status = GameStatus::IN_PLAY;
		p1 = new Player();
		p2 = new Player();
		turn = 0;
		play();
		
	}
	
	Game(Game& other) = delete;
	Game& operator=(Game& other) = delete;
	static Game* getInstance();
};
Game* Game::instance = nullptr;
Game* Game::getInstance() {
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}
int main() {
	Game *g = Game::getInstance();
	g->startGame();
	//Position p1(1, 1),n1(2,1),p2(6,1),n2(5,1);
	//(*board)[p1].getFigure()->canMove(*board, p1, n1);
	//(*board)[p2].getFigure()->canMove(*board, p2, n2);
	//std::cout << *board;
}