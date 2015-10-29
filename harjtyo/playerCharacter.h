#ifndef PLAYERCHARACTERH
#define PLAYERCHARACTERH

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\System\Vector2.hpp>
#include "bullet.h"

class PlayerCharacter : public sf::RectangleShape {
public:
	PlayerCharacter();
	Bullet shoot(sf::Vector2f);
private:
};

#endif