#ifndef MATHH
#define MATHH

#include <SFML\System\Vector2.hpp>

namespace Math {
	float vector2fLength(sf::Vector2f&);
	sf::Vector2f vector2fUnit(sf::Vector2f&);
	sf::Vector2f vector2fRotate(const sf::Vector2f&, float);
	const float PI = 3.14159f;
}

#endif