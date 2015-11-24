#ifndef ENEMYH
#define ENEMYH

#include <SFML\Graphics.hpp>

class Enemy : public sf::Sprite {
public:
	Enemy(const sf::Texture&);
	bool isReadyToFire();
	void setReadyToFire(bool);
	void setHitbox(sf::FloatRect);
	void update();
	bool checkHit(const sf::Vector2f&);
	bool isAlive();
private:
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