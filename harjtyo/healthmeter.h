#ifndef HEALTHMETERH
#define HEALTHMETERH

#include <SFML\Graphics.hpp>

class HealthMeter {
public:
	HealthMeter();
	void setPosition(float, float);
	void setPosition(const sf::Vector2f&);
	void setSize(const sf::Vector2f&);
	void move(float, float);
	void move(const sf::Vector2f&);
	void draw(sf::RenderWindow&);
	void setFillWidth(float);
private:
	const float X_OFFSET = 8.0f;
	const float Y_OFFSET = 8.0f;
	sf::RectangleShape meterBackground;
	sf::RectangleShape meterFill;
};

#endif