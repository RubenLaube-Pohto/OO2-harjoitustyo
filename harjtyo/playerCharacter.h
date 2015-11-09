#ifndef PLAYERCHARACTERH
#define PLAYERCHARACTERH

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include "bullet.h"

class PlayerCharacter {
public:
	PlayerCharacter();
	Bullet shoot(sf::Vector2f);
	void move(const float, const float);
	void draw(sf::RenderWindow&);
	void setPosition(const float, const float);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
};

#endif