#include <vector>
#include <SFML/Graphics.hpp>
#include "playerCharacter.h"
#include "math.h"

const float MOVE_SPEED = 5.0f;
const int WIDTH = 700;
const int HEIGTH = WIDTH;
const float GROUND_WIDTH = 256.0f * 4;
const float GROUND_HEIGTH = 256.0f * 4;

PlayerCharacter* player = NULL;
sf::View view;
sf::CircleShape crosshair;
float xSpeed, ySpeed;
std::vector<Bullet> bullets;
sf::Text framerateText;
sf::Clock fpsTimer;
int fps = 0;

void update(sf::RenderWindow&);

int main() {
	srand((unsigned int)time(NULL));
	sf::Clock cooldownTimer;
	float cooldown = 0.01f;

	sf::Font fontArial;
	fontArial.loadFromFile("arial.ttf");
	framerateText = sf::Text();
	framerateText.setFont(fontArial);
	framerateText.setColor(sf::Color::Red);

	// Load window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Harkkarainen");
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);

	// Load background
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");
	backgroundTexture.setRepeated(true);
	sf::RectangleShape background = sf::RectangleShape::RectangleShape();
	background.setTexture(&backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, (int)GROUND_WIDTH, (int)GROUND_HEIGTH));
	background.setSize(sf::Vector2f(GROUND_WIDTH, GROUND_HEIGTH));

	// Load player
	player = new PlayerCharacter();
	player->setPosition(GROUND_WIDTH / 2, GROUND_HEIGTH / 2);

	// Load crosshair cursor
	crosshair = sf::CircleShape::CircleShape();
	crosshair.setRadius(5.0f);
	crosshair.setOrigin(5.0f, 5.0f);
	crosshair.setPosition(GROUND_WIDTH / 2, GROUND_HEIGTH / 2);

	view = sf::View(player->getPosition(), sf::Vector2f((float)WIDTH, (float)HEIGTH));

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
			player->setDirection(Direction::NORTHWEST);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = -MOVE_SPEED * sin(Math::PI * 0.25f);
			player->setDirection(Direction::NORTHEAST);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = MOVE_SPEED * sin(Math::PI * 0.25f);
			player->setDirection(Direction::SOUTHWEST);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
			     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED * cos(Math::PI * 0.25f);
			ySpeed = MOVE_SPEED * sin(Math::PI * 0.25f);
			player->setDirection(Direction::SOUTHEAST);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			ySpeed = -MOVE_SPEED;
			player->setDirection(Direction::NORTH);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			xSpeed = -MOVE_SPEED;
			player->setDirection(Direction::WEST);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			ySpeed = MOVE_SPEED;
			player->setDirection(Direction::SOUTH);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			xSpeed = MOVE_SPEED;
			player->setDirection(Direction::EAST);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (cooldown <= cooldownTimer.getElapsedTime().asSeconds()) {
				cooldownTimer.restart();
				sf::Vector2f bv = crosshair.getPosition() - player->getPosition();
				bullets.push_back(Bullet(Math::vector2fUnit(bv), player->getPosition(), Math::vector2fLength(bv)));
			}
		}

		update(window);

		window.clear();
		window.setView(view);
		window.draw(background);
		player->draw(window);
		window.draw(crosshair);
		window.draw(framerateText);
		for (unsigned int i = 0; i < bullets.size(); i++) {
			window.draw(bullets.at(i));
		}
		window.display();
	}

	delete player;
	player = NULL;

	return 0;
}

void update(sf::RenderWindow& window) {
	const float OFFSET = 50.0f;

	if (xSpeed != 0.0f || ySpeed != 0.0f) {
		// Update player position
		sf::Vector2f playerPos = player->getPosition();
		sf::Vector2f playerSize = player->getSize();

		player->animate();

		bool crossLeft = (playerPos.x - playerSize.x * 0.5f + xSpeed) < 0.0f;
		bool crossRight = (playerPos.x + playerSize.x * 0.5f + xSpeed) > GROUND_WIDTH;
		bool crossTop = (playerPos.y - playerSize.y * 0.5f + ySpeed) < 0.0f;
		bool crossBottom = (playerPos.y + playerSize.y * 0.5f + ySpeed) > GROUND_HEIGTH;

		if (crossTop && crossLeft)
			player->setPosition(playerSize.x * 0.5f, playerSize.y * 0.5f);
		else if (crossTop && crossRight)
			player->setPosition(GROUND_WIDTH - playerSize.x * 0.5f, playerSize.y * 0.5f);
		else if (crossBottom && crossLeft)
			player->setPosition(playerSize.x * 0.5f, GROUND_HEIGTH - playerSize.y * 0.5f);
		else if (crossBottom && crossRight)
			player->setPosition(GROUND_WIDTH - playerSize.x * 0.5f, GROUND_HEIGTH - playerSize.y * 0.5f);
		else if (crossLeft) {
			player->setPosition(playerSize.x * 0.5f, playerPos.y);
			player->move(0.0f, ySpeed);
		}
		else if (crossRight) {
			player->setPosition(GROUND_WIDTH - playerSize.x * 0.5f, playerPos.y);
			player->move(0.0f, ySpeed);
		}
		else if (crossTop) {
			player->setPosition(playerPos.x, playerSize.y * 0.5f);
			player->move(xSpeed, 0.0f);
		}
		else if (crossBottom) {
			player->setPosition(playerPos.x, GROUND_HEIGTH - playerSize.y * 0.5f);
			player->move(xSpeed, 0.0f);
		}
		else
			player->move(xSpeed, ySpeed);


		// Update view position
		playerPos = player->getPosition();

		crossLeft = playerPos.x < WIDTH * 0.5f - OFFSET;
		crossRight = playerPos.x > GROUND_WIDTH - WIDTH * 0.5f + OFFSET;
		crossTop = playerPos.y < HEIGTH * 0.5f - OFFSET;
		crossBottom = playerPos.y > GROUND_HEIGTH - HEIGTH * 0.5f + OFFSET;

		if (crossTop && crossLeft)
			view.setCenter(WIDTH * 0.5f - OFFSET, HEIGTH * 0.5f - OFFSET);
		else if (crossTop && crossRight)
			view.setCenter(GROUND_WIDTH - WIDTH * 0.5f + OFFSET, HEIGTH * 0.5f - OFFSET);
		else if (crossBottom && crossLeft)
			view.setCenter(WIDTH * 0.5f - OFFSET, GROUND_HEIGTH - HEIGTH * 0.5f + OFFSET);
		else if (crossBottom && crossRight)
			view.setCenter(GROUND_WIDTH - WIDTH * 0.5f + OFFSET, GROUND_HEIGTH - HEIGTH * 0.5f + OFFSET);
		else if (crossLeft) {
			view.setCenter(WIDTH * 0.5f - OFFSET, playerPos.y);
			view.move(0.0f, ySpeed);
		}
		else if (crossRight) {
			view.setCenter(GROUND_WIDTH - WIDTH * 0.5f + OFFSET, playerPos.y);
			view.move(0.0f, ySpeed);
		}
		else if (crossTop) {
			view.setCenter(playerPos.x, HEIGTH * 0.5f - OFFSET);
			view.move(xSpeed, 0.0f);
		}
		else if (crossBottom) {
			view.setCenter(playerPos.x, GROUND_HEIGTH - HEIGTH * 0.5f + OFFSET);
			view.move(xSpeed, 0.0f);
		}
		else
			view.setCenter(playerPos);

		// Reset speeds
		xSpeed = 0.0f;
		ySpeed = 0.0f;
	}

	// Update cursor position
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(window);
	crosshair.setPosition(view.getCenter() + sf::Vector2f(mousePosition) - sf::Vector2f(WIDTH / 2.0f, HEIGTH / 2.0f));

	// Update bullets
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets.at(i).travel();
		if (!bullets.at(i).isAlive()) {
			bullets.erase(bullets.begin() + i);
		}
	}

	// Update displayed framerate
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