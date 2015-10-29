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
}