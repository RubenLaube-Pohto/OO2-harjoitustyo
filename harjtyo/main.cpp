#include <vector>
#include <SFML/Graphics.hpp>
#include "playerCharacter.h"
#include "math.h"

const float MOVE_SPEED = 5.0f;
const int WIDTH = 600;
const int HEIGTH = WIDTH;
const float GROUND_WIDTH = 1000.0f;
const float GROUND_HEIGTH = GROUND_WIDTH;

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
	background.setSize(sf::Vector2f(GROUND_WIDTH, GROUND_HEIGTH));
	background.setFillColor(sf::Color::Blue);

	player = PlayerCharacter();
	player.setSize(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(50.0f/2, 50.0f/2);
	player.setPosition(GROUND_WIDTH/2, GROUND_HEIGTH/2);
	player.setFillColor(sf::Color::Yellow);

	crossHair = sf::CircleShape::CircleShape();
	crossHair.setRadius(5.0f);
	crossHair.setOrigin(5.0f, 5.0f);
	crossHair.setPosition(GROUND_WIDTH / 2, GROUND_HEIGTH / 2);

	view = sf::View(player.getPosition(), sf::Vector2f(WIDTH, HEIGTH));

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = -MOVE_SPEED * sin(Math::PI * 0.25f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = -MOVE_SPEED * sin(Math::PI * 0.25f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = MOVE_SPEED * sin(Math::PI * 0.25f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = MOVE_SPEED * sin(Math::PI * 0.25f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			ySpeed = -MOVE_SPEED;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			ySpeed = MOVE_SPEED;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
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

	bool crossLeft = (playerPos.x - playerSize.x * 0.5f + xSpeed) < 0.0f;
	bool crossRight = (playerPos.x + playerSize.x * 0.5f + xSpeed) > 1000.0f;
	bool crossTop = (playerPos.y - playerSize.y * 0.5f + ySpeed) < 0.0f;
	bool crossBottom = (playerPos.y + playerSize.y * 0.5f + ySpeed) > 1000.0f;
	if (crossTop && crossLeft)
		player.setPosition(playerSize.x * 0.5f, playerSize.y * 0.5f);
	else if (crossTop && crossRight)
		player.setPosition(1000.0f - playerSize.x * 0.5f, playerSize.y * 0.5f);
	else if (crossBottom && crossLeft)
		player.setPosition(playerSize.x * 0.5f, 1000.0f - playerSize.y * 0.5f);
	else if (crossBottom && crossRight)
		player.setPosition(1000.0f - playerSize.x * 0.5f, 1000.0f - playerSize.y * 0.5f);
	else if (crossLeft) {
		player.setPosition(playerSize.x * 0.5f, playerPos.y);
		player.move(0.0f, ySpeed);
	}
	else if (crossRight) {
		player.setPosition(1000.0f - playerSize.x * 0.5f, playerPos.y);
		player.move(0.0f, ySpeed);
	}
	else if (crossTop) {
		player.setPosition(playerPos.x, playerSize.y * 0.5f);
		player.move(xSpeed, 0.0f);
	}
	else if (crossBottom) {
		player.setPosition(playerPos.x, 1000.0f - playerSize.y * 0.5f);
		player.move(xSpeed, 0.0f);
	}
	else
		player.move(xSpeed, ySpeed);


	// TODO: make view stop moving on edges
	playerPos = player.getPosition();
	view.setCenter(playerPos);

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

	framerateText.setPosition(view.getCenter() + sf::Vector2f(-WIDTH * 0.5f + 20.0f, -HEIGTH * 0.5f + 20.0f));
	if (fpsTimer.getElapsedTime().asSeconds() <= 1.0f) {
		fps++;
	}
	else {
		framerateText.setString(std::to_string(fps));
		fpsTimer.restart();
		fps = 0;
	}
}