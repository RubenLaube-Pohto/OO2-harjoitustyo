#include <vector>
#include <SFML/Graphics.hpp>
#include "playerCharacter.h"
#include "math.h"

const float MOVE_SPEED = 5.0f;
const int WIDTH = 600;
const int HEIGTH = WIDTH;

PlayerCharacter player;
sf::View view;
sf::CircleShape crossHair;
float xSpeed, ySpeed;
std::vector<Bullet> bullets;
sf::Text framerateText;
sf::Clock fpsTimer;
int fps = 0;

void update(sf::RenderWindow&);

int main() {
	srand(time(NULL));
	sf::Clock cooldownTimer;
	float cooldown = 0.01f;

	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");
	framerateText = sf::Text();
	framerateText.setFont(fontArial);
	framerateText.setColor(sf::Color::Red);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Harkkarainen");
	window.setFramerateLimit(60);

	sf::RectangleShape background = sf::RectangleShape::RectangleShape();
	background.setSize(sf::Vector2f(1000.0f, 1000.0f));
	background.setFillColor(sf::Color::Blue);

	player = PlayerCharacter();
	player.setSize(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(50.0f/2, 50.0f/2);
	player.setPosition(1000.0f/2, 1000.0f/2);
	player.setFillColor(sf::Color::Yellow);

	crossHair = sf::CircleShape::CircleShape();
	crossHair.setRadius(5.0f);
	crossHair.setOrigin(5.0f, 5.0f);
	crossHair.setPosition(1000.0f / 2, 1000.0f / 2);

	view = sf::View(sf::Vector2f(500.0f, 500.0f), sf::Vector2f(WIDTH, HEIGTH));

	xSpeed = 0.0f;
	ySpeed = 0.0f;

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
			if (cooldown <= cooldownTimer.getElapsedTime().asSeconds()) {
				cooldownTimer.restart();
				sf::Vector2f bv = crossHair.getPosition() - player.getPosition();
				bullets.push_back(Bullet(Math::vector2fUnit(bv), player.getPosition(), Math::vector2fLength(bv)));
			}
		}

		update(window);

		window.clear();
		window.setView(view);
		window.draw(background);
		window.draw(player);
		window.draw(crossHair);
		window.draw(framerateText);
		for (unsigned int i = 0; i < bullets.size(); i++) {
			window.draw(bullets.at(i));
		}
		window.display();
	}

	return 0;
}

void update(sf::RenderWindow& window) {
	const float OFFSET = 50.0f;
	
	sf::Vector2f playerPos = player.getPosition();
	sf::Vector2f playerSize = player.getSize();

	if ((playerPos.x - playerSize.x / 2 + xSpeed) >= 0.0f && 
		(playerPos.x + playerSize.x / 2 + xSpeed) <= 1000.0f) {
		player.move(xSpeed, 0);
	}
	if ((playerPos.y - playerSize.y / 2 + ySpeed) >= 0.0f && 
		(playerPos.y + playerSize.y / 2 + ySpeed) <= 1000.0f) {
		player.move(0, ySpeed);
	}

	view.setCenter(player.getPosition());

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(window);
	crossHair.setPosition(player.getPosition() + sf::Vector2f(mousePosition) - sf::Vector2f(WIDTH / 2.0f, HEIGTH / 2.0f));
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets.at(i).travel();
		if (!bullets.at(i).isAlive()) {
			bullets.erase(bullets.begin() + i);
		}
	}

	framerateText.setPosition(player.getPosition() + sf::Vector2f(-WIDTH * 0.5f + 20.0f, -HEIGTH * 0.5f + 20.0f));
	if (fpsTimer.getElapsedTime().asSeconds() <= 1.0f) {
		fps++;
	}
	else {
		framerateText.setString(std::to_string(fps));
		fpsTimer.restart();
		fps = 0;
	}
}