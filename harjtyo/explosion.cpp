#include "explosion.h"

Explosion::Explosion(const sf::Texture& texture) {
	this->setTexture(texture);
	this->frameNumber = 0;
	this->done = false;
}
void Explosion::animate() {
	sf::IntRect nextFrame(frameNumber * 32, 0, 32, 32);
	this->setTextureRect(nextFrame);
	++frameNumber;
	if (frameNumber >= 7) {
		done = true;
	}
}
bool Explosion::isDone() {
	return done;
}