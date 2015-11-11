#include "enemy.h"

Enemy::Enemy() {
	this->size = sf::Vector2f(32.0f, 32.0f);
	this->texture.loadFromFile("enemy.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	this->sprite.setOrigin(sf::Vector2f(size.x * 0.5f, size.y * 0.5f));
	this->cooldownTimer.restart();
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

void Enemy::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

bool Enemy::isReadyToFire() {
	return readyToFire;
}

void Enemy::setReadyToFire(bool b) {
	readyToFire = b;
}

void Enemy::updateTimer() {
	if (cooldown <= cooldownTimer.getElapsedTime().asSeconds()) {
		cooldownTimer.restart();
		readyToFire = true;
	}
}

sf::Vector2f Enemy::getPosition() {
	return this->sprite.getPosition();
}