#ifndef EXPLOSIONH
#define EXPLOSIONH

#include <SFML\Graphics.hpp>

class Explosion : public sf::Sprite {
public:
	Explosion(const sf::Texture&);
	void animate();
	bool isDone();
private:
	bool done;
	int frameNumber;
};

#endif