#include "healthmeter.h"

HealthMeter::HealthMeter() {
	this->meterBackground.setFillColor(sf::Color(128, 0, 0, 255));
	this->meterFill.setFillColor(sf::Color::Red);
}
void HealthMeter::setPosition(float x, float y) {
	this->meterBackground.setPosition(x, y);
	this->meterFill.setPosition(x + 0.5f * X_OFFSET, y + 0.5f * Y_OFFSET);
}
void HealthMeter::setPosition(const sf::Vector2f& v) {
	this->meterBackground.setPosition(v);
	this->meterFill.setPosition(v + sf::Vector2f(0.5f * X_OFFSET, 0.5f * Y_OFFSET));
}
void HealthMeter::setSize(const sf::Vector2f& v) {
	this->meterBackground.setSize(v);
	this->meterFill.setSize(v - sf::Vector2f(X_OFFSET, Y_OFFSET));
}
void HealthMeter::move(const sf::Vector2f& v) {
	this->meterBackground.move(v);
	this->meterFill.move(v);
}
void HealthMeter::move(float x, float y) {
	this->meterBackground.move(x, y);
	this->meterFill.move(x, y);
}
void HealthMeter::draw(sf::RenderWindow& window) {
	window.draw(this->meterBackground);
	window.draw(this->meterFill);
}
void HealthMeter::setFillWidth(float scale) {
	this->meterFill.setScale(scale, 1.0f);
}