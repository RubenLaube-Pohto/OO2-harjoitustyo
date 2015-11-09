#include "playerCharacter.h"
#include "SFML\Graphics\Rect.hpp"

PlayerCharacter::PlayerCharacter() {
	this->size = sf::Vector2f(64.0f, 64.0f);
	this->texture.loadFromFile("mech.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	this->sprite.setOrigin(sf::Vector2f(size.x * 0.5f, size.y * 0.5f));
}

Bullet PlayerCharacter::shoot(sf::Vector2f direction) {
	Bullet b = Bullet();
	return b;
}

void PlayerCharacter::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void PlayerCharacter::setDirection(int d) {
	this->direction = d;
}

sf::Vector2f PlayerCharacter::getPosition() {
	return this->sprite.getPosition();
}

sf::Vector2f PlayerCharacter::getSize() {
	return this->size;
}

void PlayerCharacter::move(const float x, const float y) {
	this->sprite.move(x, y);
}

void PlayerCharacter::animate() {
	sf::IntRect nextFrame(frameNumber * (int)size.x, direction * (int)size.y, (int)size.x, (int)size.y);
	sprite.setTextureRect(nextFrame);
	
	++frameNumber;
	if (frameNumber > 15)
		frameNumber = 0;
}

void PlayerCharacter::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}