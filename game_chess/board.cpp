#include <iostream>
#include "board.hpp"

BoardCell::BoardCell(Figure* fig, Position pos, Color color) :fig(fig), pos(pos), color(color) {

}
//bug: when deleting will have problem if something is on the stack
void BoardCell::setFigure(Figure* f) {
	fig = f;
}
Figure* BoardCell::getFigure() {
	return fig;
}
const Figure* BoardCell::getFigure() const {
	return fig;
}
bool BoardCell::hasFigure() const {
	return fig != nullptr;
}
Color BoardCell::getColor() const {
	return color;
}
std::ostream& operator<<(std::ostream& os, const BoardCell& bc) {
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
void BoardCell::moveFromCell(BoardCell& other) {
	this->setFigure(other.fig);
	other.setFigure(nullptr);
}
void Board::initDefaultBoard() {
	for (unsigned i = 0; i < BOARD_SIZE; i++) {
		for (unsigned j = 0; j < BOARD_SIZE; j++) {
			arr[i][j] = { nullptr, {i,j},((i + j) % 2 == 0 ? Color::BLACK : Color::WHITE) };
		}
	}
	arr[0][0].setFigure(Figure::factory(FigureType::ROOK, Color::WHITE));
	arr[0][1].setFigure(Figure::factory(FigureType::KNIGHT, Color::WHITE));
	arr[0][2].setFigure(Figure::factory(FigureType::BISHOP, Color::WHITE));
	arr[0][3].setFigure(Figure::factory(FigureType::QUEEN, Color::WHITE));
	arr[0][4].setFigure(Figure::factory(FigureType::KING, Color::WHITE));
	arr[0][5].setFigure(Figure::factory(FigureType::BISHOP, Color::WHITE));
	arr[0][6].setFigure(Figure::factory(FigureType::KNIGHT, Color::WHITE));
	arr[0][7].setFigure(Figure::factory(FigureType::ROOK, Color::WHITE));
	for (int i = 0; i < BOARD_SIZE; i++) {
		arr[1][i].setFigure(Figure::factory(FigureType::PAWN, Color::WHITE));
		arr[6][i].setFigure(Figure::factory(FigureType::PAWN, Color::BLACK));
	}
	arr[7][0].setFigure(Figure::factory(FigureType::ROOK, Color::BLACK));
	arr[7][1].setFigure(Figure::factory(FigureType::KNIGHT, Color::BLACK));
	arr[7][2].setFigure(Figure::factory(FigureType::BISHOP, Color::BLACK));
	arr[7][3].setFigure(Figure::factory(FigureType::QUEEN, Color::BLACK));
	arr[7][4].setFigure(Figure::factory(FigureType::KING, Color::BLACK));
	arr[7][5].setFigure(Figure::factory(FigureType::BISHOP, Color::BLACK));
	arr[7][6].setFigure(Figure::factory(FigureType::KNIGHT, Color::BLACK));
	arr[7][7].setFigure(Figure::factory(FigureType::ROOK, Color::BLACK));
}
Board::Board() {
	initDefaultBoard();
}
Board::Board(BoardCell arr[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			this->arr[i][j] = arr[i][j];
		}
	}
}

BoardCell& Board::operator[](const Position& p) {
	return arr[p.x][p.y];
}
int Board::move(Color playerColor, const Position& p1, const Position& p2) {
	Figure* currentFigure = (*this)[p1].getFigure();
	if (!currentFigure)
		return -1;
	if (currentFigure->getColor() != playerColor)
		return -1;
	if (!currentFigure->canMove(*this, p1, p2))
		return -1;
	int score = 0;
	BoardCell& newPosCell = (*this)[p2];
	//it is guaranteed that if there is a figure on the new pos, it is an opponents figure
	if (newPosCell.hasFigure()) {
		score += newPosCell.getFigure()->getPoints();
	}
	newPosCell.moveFromCell((*this)[p1]);
	return score;
}
std::ostream& operator<<(std::ostream& os, Board& board) {
	os << "\n";
	for (int i = 0; i < BOARD_SIZE; i++) {
		os << 8 - i;
		for (int j = 0; j < BOARD_SIZE; j++) {
			os << board.arr[i][j];
		}
		os << "\n";
	}
	os << " ";
	for (int i = 0; i < BOARD_SIZE; i++) {
		os << (char)(i + 'A') << "     ";
	}
	os << "\n";
	return os;
}
Board::~Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (arr[i][j].hasFigure())
				delete arr[i][j].getFigure();
		}
	}
}
