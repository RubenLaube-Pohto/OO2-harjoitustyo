#ifndef ENEMYH
#define ENEMYH

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>

class Enemy {
public:
	Enemy();
	void draw(sf::RenderWindow&);
	void setPosition(const float, const float);
	bool isReadyToFire();
	void setReadyToFire(bool);
	void update();
	sf::Vector2f getPosition();
	void move(const sf::Vector2f&);
	void checkHit(const sf::Vector2f&);
	bool isAlive();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
	sf::Clock cooldownTimer;
	float cooldown = 1.5f;
	int direction = 0;
	int frameNumber = 0;
	bool readyToFire = false;
	int healthPoints = 3;
	bool alive = true;
	sf::FloatRect hitbox;
};

#endif