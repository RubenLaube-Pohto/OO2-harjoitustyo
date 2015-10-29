#include "bullet.h"

Bullet::Bullet() : CircleShape () {

}

Bullet::Bullet(const sf::Vector2f& direction, const sf::Vector2f& origin, float distance) : CircleShape() {
	this->speed = 5.0f;
	this->setRadius(2.0f);
	this->setOrigin(2.0f, 2.0f);
	this->setPosition(origin);
	this->direction = direction;
	this->distanceToTravel = distance;
	this->distanceTravelled = 0.0f;
	this->setFillColor(sf::Color::Yellow);
	this->alive = true;
}

void Bullet::travel() {
	this->move(this->direction * speed);
	distanceTravelled += speed;
	if (distanceTravelled > distanceToTravel) {
		this->alive = false;
	}
}

bool Bullet::isAlive() {
	return alive;
}