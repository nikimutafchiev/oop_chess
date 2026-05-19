#include <iostream>
#include "board.hpp"

BoardCell::BoardCell(Figure* fig, Position pos, Color color) :fig(fig), pos(pos), color(color) {

}
BoardCell::BoardCell(const BoardCell& other) {
	fig = other.fig->copy();
	pos = other.pos;
	color = other.color;
}
void BoardCell::setFigure(Figure* f) {
	fig = f;
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
	if (this->fig)
		delete this->fig;
	this->setFigure(other.fig);
	fig->move(pos);
	other.setFigure(nullptr);
}
bool BoardCell::isFriendFigure(const Figure* other) const{
	if (fig) {
		if (other) 
			return fig->isColor(other);
	}
	return false;
}
bool BoardCell::isFriendColor(Color c)const {
	return this->fig->isColor(c);
}
int Board::pawnEnd(Color color)const {
	return color == Color::BLACK ? 0 : SIZE - 1;
}
bool Board::isValidPosition(const Position& p)const {
	return p.x < SIZE && p.y < SIZE;
}
void Board::initDefaultBoard() {
	for (unsigned i = 0; i < SIZE; i++) {
		for (unsigned j = 0; j < SIZE; j++) {
			arr[i][j] = { nullptr, {i,j},((i + j) % 2 == 0 ? Color::BLACK : Color::WHITE) };
		}
	}
	arr[0][0].setFigure(Figure::factory(FigureType::ROOK, Color::WHITE, { 0, 0 }));
	arr[0][1].setFigure(Figure::factory(FigureType::KNIGHT, Color::WHITE, {0,1}));
	arr[0][2].setFigure(Figure::factory(FigureType::BISHOP, Color::WHITE,{0,2}));
	arr[0][3].setFigure(Figure::factory(FigureType::QUEEN, Color::WHITE,{0,3}));
	arr[0][4].setFigure(Figure::factory(FigureType::KING, Color::WHITE, {0,4}));
	arr[0][5].setFigure(Figure::factory(FigureType::BISHOP, Color::WHITE, {0,5}));
	arr[0][6].setFigure(Figure::factory(FigureType::KNIGHT, Color::WHITE, { 0,6 }));
	arr[0][7].setFigure(Figure::factory(FigureType::ROOK, Color::WHITE, { 0,7 }));
	for (unsigned i = 0; i < SIZE; i++) {
		arr[1][i].setFigure(Figure::factory(FigureType::PAWN, Color::WHITE,{1,i}));
		arr[6][i].setFigure(Figure::factory(FigureType::PAWN, Color::BLACK,{6,i}));
	}
	arr[7][0].setFigure(Figure::factory(FigureType::ROOK, Color::BLACK, { 7,0}));
	arr[7][1].setFigure(Figure::factory(FigureType::KNIGHT, Color::BLACK, { 7,1 }));
	arr[7][2].setFigure(Figure::factory(FigureType::BISHOP, Color::BLACK, { 7,2 }));
	arr[7][3].setFigure(Figure::factory(FigureType::QUEEN, Color::BLACK, { 7,3}));
	arr[7][4].setFigure(Figure::factory(FigureType::KING, Color::BLACK, { 7,4 }));
	arr[7][5].setFigure(Figure::factory(FigureType::BISHOP, Color::BLACK, { 7,5 }));
	arr[7][6].setFigure(Figure::factory(FigureType::KNIGHT, Color::BLACK, { 7,6 }));
	arr[7][7].setFigure(Figure::factory(FigureType::ROOK, Color::BLACK, { 7,7}));
}
Board::Board() {
	initDefaultBoard();
}
Board::Board(BoardCell arr[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->arr[i][j] = arr[i][j];
		}
	}
}
Board::Board(const Board& other) {
	this->moves = other.moves;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->arr[i][j] = other.arr[i][j];
		}
	}
}
size_t Board::getBoardSize() const{
	return SIZE;
}
BoardCell& Board::operator[](const Position& p) {
	if (!isValidPosition(p))
		std::exit(-1);
	return arr[p.x][p.y];
}
const BoardCell& Board::operator[](const Position& p) const{
	if (!isValidPosition(p))
		std::exit(-1);
	return arr[p.x][p.y];
}
int Board::move(Color playerColor, const Move&move) {
	const Figure* currentFigure = (*this)[move.src].getFigure();
	if (!currentFigure)
		return -1;
	if (currentFigure->getColor() != playerColor)
		return -1;
	if (!currentFigure->canMove(*this, move.dest))
		return -1;
	int score = 0;
	BoardCell& newPosCell = (*this)[move.dest];
	//it is guaranteed that if there is a figure on the new pos, it is an opponents figure
	if (newPosCell.hasFigure()) {
		score += newPosCell.getFigure()->getPoints();
	}
	newPosCell.moveFromCell((*this)[move.src]);
	return score;
}
std::ostream& operator<<(std::ostream& os, Board& board) {
	os << "\n";
	for (int i = 0; i < board.SIZE; i++) {
		os << board.SIZE - i;
		for (int j = 0; j < board.SIZE; j++) {
			os << board.arr[i][j];
		}
		os << "\n";
	}
	os << " ";
	for (int i = 0; i < board.SIZE; i++) {
		os << (char)(i + 'A') << "     ";
	}
	os << "\n";
	return os;
}
int Board::pawnDirection(Color color)const {
	return color == Color::WHITE ? 1 : -1;
}
unsigned Board::getFigureCount()const {
	unsigned cnt = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j].hasFigure())
				cnt++;
		}
	}
	return cnt;
}
unsigned Board::getFigureCount(FigureType ft)const {
	unsigned cnt = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j].hasFigure())
				cnt += arr[i][j].getFigure()->getType() == ft;
		}
	}
	return cnt;
}
void Board::getAllPossibleMoves(Color c, std::vector<Move>& res) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j].hasFigure()) {
				const Figure* f = arr[i][j].getFigure();
				if (f->isColor(c))
					f->getAllPossibleMoves(*this, res);
			}
		}
	}
}
void Board::goRoute(const Position& initPos, Position currPos, int directionX, int directionY, Color color, std::vector<Move>& res)const{
	if (!isValidPosition(currPos))
		return;
	if ((*this)[currPos].hasFigure()) {
		if (!(*this)[currPos].isFriendColor(color)) {
			res.push_back(Move(initPos, currPos));
		}
		return;
	}
	res.push_back(Move(initPos, currPos));
	goRoute(initPos, { currPos.x + directionX,currPos.y + directionY }, directionX, directionY, color, res);
}
//this should always return valid position, because if not the game will be finished
Position Board::getKingPosition(Color c) {
	for (unsigned i = 0; i < SIZE; i++) {
		for (unsigned j = 0; j < SIZE; j++) {
			if (arr[i][j].hasFigure()) {
				const Figure* f = arr[i][j].getFigure();
				if (f->getColor() == c && f->getType() == FigureType::KING) {
					return { i,j };
				}
			}
		}
	}
	throw "There is no king of this color";
}
//need to make sure all figures are dynamically allocated
Board::~Board() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j].hasFigure())
				delete arr[i][j].getFigure();
		}
	}
}
