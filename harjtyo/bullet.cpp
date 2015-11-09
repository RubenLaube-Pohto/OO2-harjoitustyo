#include "bullet.h"
#include <time.h>
#include "math.h"

Bullet::Bullet() : CircleShape () {

}

Bullet::Bullet(const sf::Vector2f& direction, const sf::Vector2f& origin, float distance) : CircleShape() {
	this->speed = 20.0f;
	this->setRadius(3.0f);
	this->setOrigin(2.0f, 2.0f);
	this->setPosition(origin);
	this->direction = Math::vector2fRotate(direction, (Math::PI * 0.01f) * (rand() % 11 - 5));
	this->distanceToTravel = distance * (rand() % 21 + 90) * 0.01f;
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