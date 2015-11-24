#include "playerCharacter.h"

PlayerCharacter::PlayerCharacter(const sf::Texture& texture) : Sprite() {
	this->size = sf::Vector2f(64.0f, 64.0f);
	this->setTexture(texture);
	this->setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	this->setOrigin(sf::Vector2f(size.x * 0.5f, size.y * 0.5f));
	this->cooldownTimer.restart();
	this->alive = true;
	this->hitbox = this->getGlobalBounds();
}

void PlayerCharacter::setDirection(int d) {
	this->direction = d;
}

sf::Vector2f PlayerCharacter::getSize() {
	return this->size;
}

void PlayerCharacter::animate() {
	sf::IntRect nextFrame(frameNumber * (int)size.x, direction * (int)size.y, (int)size.x, (int)size.y);
	this->setTextureRect(nextFrame);
	
	++frameNumber;
	if (frameNumber > 15)
		frameNumber = 0;
}

void PlayerCharacter::updateTimer() {
	if (cooldown <= cooldownTimer.getElapsedTime().asSeconds()) {
		cooldownTimer.restart();
		readyToFire = true;
	}
}

bool PlayerCharacter::isReadyToFire() {
	return readyToFire;
}

void PlayerCharacter::setReadyToFire(bool b) {
	readyToFire = b;
}

bool PlayerCharacter::checkHit(const sf::Vector2f& point) {
	if (hitbox.contains(point)) {
		--healthPoints;
		if (healthPoints <= 0) {
			this->alive = false;
		}
		return true;
	}
	return false;
}

void PlayerCharacter::setHitbox(sf::FloatRect hitbox) {
	this->hitbox = hitbox;
}

bool PlayerCharacter::isAlive() {
	return alive;
}