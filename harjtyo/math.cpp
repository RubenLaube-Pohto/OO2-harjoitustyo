#include "math.h"
#include <cmath>

namespace Math {
	float vector2fLength(sf::Vector2f& v) {
		return std::sqrtf(v.x * v.x + v.y * v.y);
	}
	sf::Vector2f vector2fUnit(sf::Vector2f& v) {
		float l = vector2fLength(v);
		return sf::Vector2f(v.x / l, v.y / l);
	}
	sf::Vector2f vector2fRotate(const sf::Vector2f& v, float angle) {
		float x = v.x * cos(angle) - v.y * sin(angle);
		float y = v.x * sin(angle) + v.y * cos(angle);
		return sf::Vector2f(x, y);
	}
	sf::Vector2f vector2fMultiply(sf::Vector2f& v, float f) {
		return sf::Vector2f(v.x * f, v.y * f);
	}
}