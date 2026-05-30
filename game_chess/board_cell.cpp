#include "board_cell.hpp"

BoardCell::BoardCell(Figure* fig, Color color) :fig(fig), color(color) {

}
BoardCell::BoardCell(const BoardCell& other) {
	if (other.fig)
		fig = other.fig->copy();
	else
		fig = nullptr;
	color = other.color;
}
BoardCell& BoardCell::operator=(const BoardCell& other) {
	if (this != &other) {
		if (other.fig)
			fig = other.fig->copy();
		else
			fig = nullptr;
		color = other.color;
	}
	return *this;
}
//there is RAII problem
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
Figure* BoardCell::moveFromCell(BoardCell& other, const Position& myPos) {
	if(!other.fig)
		throw "There is no figure to move";
	Figure* figToTake = fig;
	this->setFigure(other.fig);
	fig->move(myPos);
	other.setFigure(nullptr);
	return figToTake;
}
bool BoardCell::isFriendFigure(const Figure* other) const {
	if (fig) {
		if (other)
			return fig->isColor(other);
	}
	return false;
}
bool BoardCell::isFriendColor(Color c)const {
	return this->fig->isColor(c);
}
void BoardCell::serialize(std::ostream& os)const {
	os << (color == Color::WHITE ? "w" : "b") << " ";
	if (fig) {
		fig->serialize(os);
	}
	else {
		os << "[Empty]";
	}
}
void BoardCell::deserialize(std::istream& is) {
	if (fig) {
		delete fig;
		fig = nullptr;
	}
	char c;
	is >> c;
	if (c == 'w') {
		color = Color::WHITE;
	}
	else if (c == 'b') {
		color = Color::BLACK;
	}
	std::string figureType;
	is >> figureType;
	if (figureType == "[Empty]") 
	{
		return;
	}
	else if(figureType == "[Pawn]") {
		fig = Figure::factory(FigureType::PAWN, Color::WHITE, { 0, 0 });
	}
	else if(figureType == "[Rook]") {
		fig = Figure::factory(FigureType::ROOK, Color::WHITE, { 0, 0 });
	}
	else if(figureType == "[Bishop]") {
		fig = Figure::factory(FigureType::BISHOP, Color::WHITE, { 0, 0 });
	}
	else if(figureType == "[Knight]") {
		fig = Figure::factory(FigureType::KNIGHT, Color::WHITE, { 0, 0 });
	}
	else if(figureType == "[Queen]") {
		fig = Figure::factory(FigureType::QUEEN, Color::WHITE, { 0, 0 });
	}
	else if(figureType == "[King]") {
		fig = Figure::factory(FigureType::KING, Color::WHITE, { 0, 0 });
	}
	else {
		throw "Unexpected figure type";
	}
	fig->deserialize(is);
}