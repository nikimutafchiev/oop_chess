#include <iostream>
#include "board.hpp"
#include "pawn.hpp"
#include "board_cell.hpp"
#include "player.hpp"

int Board::promotionRank(Color color)const {
	return color == Color::BLACK ? 0 : SIZE - 1;
}
bool Board::isValidPosition(const Position& p)const {
	return p.x < SIZE && p.y < SIZE;
}
void Board::initDefaultBoard() {
	for (unsigned i = 0; i < SIZE; i++) {
		for (unsigned j = 0; j < SIZE; j++) {
			arr[i][j] = { nullptr,((i + j) % 2 == 0 ? Color::BLACK : Color::WHITE) };
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
bool Board::canMove(Color playerColor, const Move& move, const Figure* figure) {
	if (!figure)
		return false;
	if (figure->getColor() != playerColor)
		return false;
	if (!figure->canMove(*this, move.dest))
		return false;
	return true;
}
int Board::move(const Player &player, const Move&move) {
	const Figure* currentFigure = (*this)[move.src].getFigure();
	Color playerColor = player.getColor();
	if (!canMove(player.getColor(), move, currentFigure))
		return -1;
	int score = 0;
	BoardCell& newPosCell = (*this)[move.dest];
	//it is guaranteed that if there is a figure on the new pos, it is an opponents figure
	if (newPosCell.hasFigure()) {
		score += newPosCell.getFigure()->getPoints();
	}
	
	newPosCell.moveFromCell((*this)[move.src], move.dest);
	moves.push_back(std::pair(player, move));
	if (player.isChecked) {
		if (isCheck(playerColor)) {
			undoLastMove();
			std::cout << "King is still in check" << std::endl;
			return -1;
		}
	}
	//not so important for now
	//if (currentFigure->getType() == FigureType::PAWN && ((Pawn*)currentFigure)->canTransform(boae)) {
	//}
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
bool Board::isCheck(Color c) {
	std::vector<Move> possibleOpponentMoves;
	getAllPossibleMoves(!c, possibleOpponentMoves);
	Position kingPosition = getKingPosition(c);

	for (Move move : possibleOpponentMoves) {
		if ((*this)[move.dest].hasFigure() && move.dest == kingPosition) {
			return true;
		}
	}
	return false;
}
void Board::undoLastMove() {
	if (!moves.empty()) {
		std::pair<Player,Move> last = moves.back();
		moves.pop_back();
		Move lastMove = last.second;
		(*this)[lastMove.src].moveFromCell((*this)[lastMove.dest], lastMove.src);
	}
}
void Board::serialize(std::ostream& os) const {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			arr[i][j].serialize(os);
			os << "\n";
		}
	}
}
void Board::deserialize(std::istream& is) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			arr[i][j].deserialize(is);
		}
	}
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
