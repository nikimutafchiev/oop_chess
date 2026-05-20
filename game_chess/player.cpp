#include "player.hpp"
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
void Player::serialize(std::ostream& os) const {
	os << name << " " << score << " " << (color == Color::WHITE ? "w" : "b");
}
void Player::deserialize(std::istream& is) {
	is >> name;
	is >> score;
	char c;
	is >> c;
	if (c == 'w') {
		color = Color::WHITE;
	}
	else if (c == 'b') {
		color = Color::BLACK;
	}
}