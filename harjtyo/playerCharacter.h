#ifndef PLAYERCHARACTERH
#define PLAYERCHARACTERH

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include "bullet.h"

enum Direction {
	SOUTH, SOUTHEAST, EAST, NORTHEAST,
	NORTH, NORTHWEST, WEST, SOUTHWEST
};

class PlayerCharacter {
public:
	PlayerCharacter();
	void move(const float, const float);
	void updateTimer();
	void animate();
	void draw(sf::RenderWindow&);
	void setPosition(const float, const float);
	void setDirection(int);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	bool isReadyToFire();
	void setReadyToFire(bool);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
	sf::Clock cooldownTimer;
	float cooldown = 0.3f;
	bool readyToFire = false;
	int direction = 0;
	int frameNumber = 0;
};

#endif