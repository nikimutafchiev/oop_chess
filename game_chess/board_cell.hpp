#pragma once
#include "other.hpp"
#include "figure.hpp"
#include <memory>

using std::unique_ptr;
class BoardCell {
	//unique pointer?
	
	Figure* fig;
	Color color;
public:
	BoardCell() = default;
	BoardCell(Figure* fig, Color color);
	BoardCell(const BoardCell& other);
	BoardCell& operator =(const BoardCell& other);
	void setFigure(Figure* f);
	const Figure* getFigure() const;
	bool hasFigure() const;
	Color getColor() const;
	friend std::ostream& operator<<(std::ostream& os, const BoardCell& bc);
	//gets the value from the cell and leaves the source with nothing and returns the figure that was on the cell
	Figure* moveFromCell(BoardCell& other, const Position& myPos);
	//returns if the color of our figure(if there is one) is the same as the fig color
	bool isFriendFigure(const Figure* fig) const;
	bool isFriendColor(Color c) const;
	void serialize(std::ostream&) const;
	void deserialize(std::istream&);
};