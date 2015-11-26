#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "playerCharacter.h"
#include "enemy.h"
#include "math.h"
#include "constants.h"

float xSpeed, ySpeed;

PlayerCharacter* player = NULL;
sf::View view;
sf::Sprite crosshair;
std::vector<Enemy*> enemies;
std::vector<Bullet> bullets;
std::vector<Bullet> enemyBullets;

sf::Sound gameoverSound;
sf::Sound playerDeathSound;
sf::Sound playerShootSound;
sf::Sound enemyShootSound;

int fps = 0;
sf::Text framerateText;
sf::Clock fpsTimer;

void update(sf::RenderWindow&);

int main() {
	srand((unsigned int)time(NULL));

	// Create framerate display for debug
	sf::Font fontArial;
	fontArial.loadFromFile(FONT_FILE);
	framerateText = sf::Text();
	framerateText.setFont(fontArial);
	framerateText.setColor(sf::Color::Red);

	// Load window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), TITLE);
	window.setFramerateLimit(62);
	window.setMouseCursorVisible(false);

	// Load textures
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(BG_TEXTURE_FILE);
	backgroundTexture.setRepeated(true);

	sf::Texture playerTexture;
	playerTexture.loadFromFile(PLAYER_TEXTURE_FILE);

	sf::Texture enemyTexture;
	enemyTexture.loadFromFile(ENEMY_TEXTURE_FILE);

	sf::Texture crosshairTexture;
	crosshairTexture.loadFromFile(CROSSHAIR_TEXTURE_FILE);

	// Load background
	sf::RectangleShape background = sf::RectangleShape::RectangleShape();
	background.setTexture(&backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, (int)GROUND_WIDTH, (int)GROUND_HEIGTH));
	background.setSize(sf::Vector2f(GROUND_WIDTH, GROUND_HEIGTH));

	// Load player
	player = new PlayerCharacter(playerTexture);
	player->setPosition(GROUND_WIDTH / 2, GROUND_HEIGTH / 2);

	// Load enemies
	for (int i = 0; i < 10; ++i) {
		Enemy* enemy = new Enemy(enemyTexture);
		int randX = rand() % (int)GROUND_WIDTH + 1;
		int randY = rand() % (int)GROUND_HEIGTH + 1;
		enemy->setPosition((float)randX, (float)randY);
		enemies.push_back(enemy);
	}
	
	// Load crosshair cursor
	crosshair.setTexture(crosshairTexture);
	crosshair.setOrigin(crosshairTexture.getSize().x * 0.5f, crosshairTexture.getSize().y * 0.5f);
	crosshair.setScale(0.2f, 0.2f);

	// Initialize camera and moving speeds
	view = sf::View(player->getPosition(), sf::Vector2f((float)WIDTH, (float)HEIGTH));
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	// Load music
	sf::Music musicPlayer;
	musicPlayer.openFromFile(BG_MUSIC);
	musicPlayer.setLoop(true);
	musicPlayer.play();

	// Load sound effects
	sf::SoundBuffer sbGameoverSound;
	sf::SoundBuffer sbPlayerDeathSound;
	sf::SoundBuffer sbPlayerShootSound;
	sf::SoundBuffer sbEnenmyShootSound;

	sbGameoverSound.loadFromFile(GAMEOVER_AUDIO);
	sbPlayerDeathSound.loadFromFile(PLAYER_DEATH_AUDIO);
	sbPlayerShootSound.loadFromFile(PLAYER_SHOOT_AUDIO);
	sbEnenmyShootSound.loadFromFile(ENEMY_SHOOT_AUDIO);

	gameoverSound = sf::Sound(sbGameoverSound);
	playerDeathSound = sf::Sound(sbPlayerDeathSound);
	playerShootSound = sf::Sound(sbPlayerShootSound);
	enemyShootSound = sf::Sound(sbEnenmyShootSound);

	// Game loop
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
			if (player->isReadyToFire()) {
				sf::Vector2f bv = crosshair.getPosition() - player->getPosition();
				bullets.push_back(Bullet(Math::vector2fUnit(bv), player->getPosition(), WIDTH * 0.5f));
				player->setReadyToFire(false);
				playerShootSound.play();
			}
		}

		update(window);

		window.clear();
		window.setView(view);
		window.draw(background);
		window.draw(*player);
		for (unsigned int i = 0; i < enemies.size(); i++) {
			window.draw(*(enemies.at(i)));
		}
		for (unsigned int i = 0; i < bullets.size(); i++) {
			window.draw(bullets.at(i));
		}
		for (unsigned int i = 0; i < enemyBullets.size(); i++) {
			window.draw(enemyBullets.at(i));
		}
		window.draw(crosshair);
		if (DEBUG) {
			window.draw(framerateText);
		}
		window.display();
	}

	delete player;
	player = NULL;

	while (enemies.size()) {
		delete enemies.back();
		enemies.back() = NULL;
		enemies.pop_back();
	}

	return 0;
}

void update(sf::RenderWindow& window) {
	const float OFFSET = 50.0f;

	// Update player
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

		player->setHitbox(player->getGlobalBounds());

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
	player->updateTimer();

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
	for (unsigned int i = 0; i < enemyBullets.size(); i++) {
		enemyBullets.at(i).travel();
		if (!enemyBullets.at(i).isAlive()) {
			enemyBullets.erase(enemyBullets.begin() + i);
		}
	}

	// Update enemies
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		Enemy* enemy = NULL;
		enemy = enemies.at(i);
		enemy->update();
		if (enemy->isAlive()) {
			if (Math::vector2fLength(player->getPosition() - enemy->getPosition()) < ENEMY_SHOOTING_DISTANCE) {
				if (enemy->isReadyToFire()) {
					sf::Vector2f bv = player->getPosition() - enemy->getPosition();
					enemyBullets.push_back(Bullet(Math::vector2fUnit(bv), enemy->getPosition(), WIDTH * 0.5f));
					enemy->setReadyToFire(false);
					enemyShootSound.play();
				}
			}
			else {
				sf::Vector2f nextStep = Math::vector2fUnit(player->getPosition() - enemy->getPosition());
				enemy->move(nextStep);
				enemy->setHitbox(enemy->getGlobalBounds());
			}
		}
		else {
			enemy = new Enemy(*(enemies.at(i)->getTexture()));
			int randX = rand() % (int)GROUND_WIDTH + 1;
			int randY = rand() % (int)GROUND_HEIGTH + 1;
			enemy->setPosition((float)randX, (float)randY);
			enemies.push_back(enemy);

			delete enemies.at(i);
			enemies.at(i) = NULL;
			enemies.erase(enemies.begin() + i);
		}
	}

	// Update displayed framerate
	if (DEBUG) {
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

	// Check hits on enemies
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		Enemy* enemy = NULL;
		enemy = enemies.at(i);
		for (int j = bullets.size() - 1; j >= 0; --j) {
			if (enemy->checkHit(bullets.at(j).getPosition())) {
				bullets.erase(bullets.begin() + j);
			}
		}
	}

	// Check hits on player
	for (int i = enemyBullets.size() - 1; i >= 0; --i) {
		if (player->checkHit(enemyBullets.at(i).getPosition())) {
			if (!player->isAlive()) {
				// TODO: Add endscreen and save highscore
				playerDeathSound.play();
				gameoverSound.play();
			}
			enemyBullets.erase(enemyBullets.begin() + i);
		}
	}
}