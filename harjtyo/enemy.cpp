#include "enemy.h"

Enemy::Enemy(const sf::Texture& texture) {
	this->size = sf::Vector2f(32.0f, 32.0f);
	this->setTexture(texture);
	this->setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	this->setOrigin(sf::Vector2f(size.x * 0.5f, size.y * 0.5f));
	this->cooldownTimer.restart();
	this->hitbox = this->getGlobalBounds();
}

bool Enemy::isReadyToFire() {
	return readyToFire;
}

void Enemy::setReadyToFire(bool b) {
	readyToFire = b;
}

void Enemy::update() {
	if (cooldown <= cooldownTimer.getElapsedTime().asSeconds()) {
		cooldownTimer.restart();
		readyToFire = true;
	}
	if (healthPoints <= 0) {
		alive = false;
	}
}

bool Enemy::checkHit(const sf::Vector2f& point) {
	if (hitbox.contains(point)) {
		--healthPoints;
		return true;
	}
	return false;
}

void Enemy::setHitbox(sf::FloatRect hitbox) {
	this->hitbox = hitbox;
}

bool Enemy::isAlive() {
	return alive;
}