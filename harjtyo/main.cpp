#include <vector>
#include <SFML/Graphics.hpp>
#include "playerCharacter.h"
#include "math.h"

const float MOVE_SPEED = 0.5f;
const int WIDTH = 600;
const int HEIGTH = WIDTH;

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Harkkarainen");
	sf::RectangleShape bg = sf::RectangleShape::RectangleShape();
	bg.setSize(sf::Vector2f(1000.0f, 1000.0f));
	bg.setFillColor(sf::Color::Blue);

	PlayerCharacter player = PlayerCharacter();
	player.setSize(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(50.0f/2, 50.0f/2);
	player.setPosition(1000.0f/2, 1000.0f/2);
	player.setFillColor(sf::Color::Yellow);

	sf::CircleShape crossHair = sf::CircleShape::CircleShape();
	crossHair.setRadius(5.0f);
	crossHair.setOrigin(5.0f, 5.0f);
	crossHair.setPosition(1000.0f / 2, 1000.0f / 2);

	sf::View view(sf::Vector2f(500.0f, 500.0f), sf::Vector2f(WIDTH, HEIGTH));

	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	sf::Vector2i mousePosition;

	std::vector<Bullet> bullets;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
					window.close();
				}
			}
		}

		// TODO: Add realistic diagonal movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			ySpeed = -MOVE_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			ySpeed = MOVE_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f bv = crossHair.getPosition() - player.getPosition();
			bullets.push_back(Bullet(Math::vector2fUnit(bv), player.getPosition(), Math::vector2fLength(bv)));
		}

		player.move(xSpeed, ySpeed);
		view.move(xSpeed, ySpeed);
		mousePosition = sf::Mouse::getPosition(window);
		crossHair.setPosition(player.getPosition() + sf::Vector2f(mousePosition) - sf::Vector2f(WIDTH / 2.0f, HEIGTH / 2.0f));
		xSpeed = 0;
		ySpeed = 0;

		window.clear();
		window.setView(view);
		window.draw(bg);
		window.draw(player);
		window.draw(crossHair);
		for (int i = 0; i < bullets.size(); i++) {
			bullets.at(i).travel();
			if (bullets.at(i).isAlive()) {
				window.draw(bullets.at(i));
			}
			else {
				bullets.erase(bullets.begin() + i);
			}
		}
		window.display();
	}

	return 0;
}