#ifndef BULLETH
#define BULLETH

#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Vector2.hpp>

class Bullet : public sf::CircleShape {
public:
	Bullet();
	Bullet(const sf::Vector2f&, const sf::Vector2f&, float);
	void travel();
	bool isAlive();
	void setSpeed(float);
private:
	sf::Vector2f direction;
	float speed;
	float distanceToTravel;
	float distanceTravelled;
	bool alive;
};

#endif