#ifndef ENEMYH
#define ENEMYH

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

class Enemy {
public:
	Enemy();
	void draw(sf::RenderWindow&);
	void setPosition(const float, const float);
	bool isReadyToFire();
	void setReadyToFire(bool);
	void updateTimer();
	sf::Vector2f getPosition();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
	sf::Clock cooldownTimer;
	float cooldown = 1.5f;
	int direction = 0;
	int frameNumber = 0;
	bool readyToFire = false;
};

#endif