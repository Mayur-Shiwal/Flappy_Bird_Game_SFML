#include "Game.h"
#include "Globals.h"
#include<sstream>

Game::Game(sf::RenderWindow& window) :
	win(window), startGame(false), runGame(true), pipeCounter(71), pipeSpawnTime(70), score(0), startMonitoring(false)
{
	win.setFramerateLimit(60);
	bgTexture.loadFromFile("assets/bg.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(ScaleFactor, ScaleFactor);
	bgSprite.setPosition(0.0f, -250.0f);

	groundTexture.loadFromFile("assets/ground.png");
	groundSprite1.setTexture(groundTexture);
	groundSprite2.setTexture(groundTexture);

	groundSprite1.setScale(ScaleFactor, ScaleFactor);
	groundSprite2.setScale(ScaleFactor, ScaleFactor);

	groundSprite1.setPosition(0, 578);
	groundSprite2.setPosition(groundSprite1.getGlobalBounds().width, 578);

	font.loadFromFile("assets/arial.ttf");
	restartText.setFont(font);
	restartText.setCharacterSize(33);
	restartText.setFillColor(sf::Color::Black);
	restartText.setPosition(150, 650);
	restartText.setString("Click here to Restart");

	scoreText.setFont(font);
	scoreText.setCharacterSize(22);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(15, 15);
	scoreText.setString("Score: 0");

	Pipe::loadTextures();
}

void Game::startGameLoop() {
	sf::Clock clock;
	while (win.isOpen()) {	//Game loop
		sf::Time dt = clock.restart();
		sf::Event evnt;
		while (win.pollEvent(evnt)) {	//event loop
			if (evnt.type == sf::Event::Closed) win.close();
			if (evnt.type == sf::Event::KeyPressed && runGame) {
				if (evnt.key.code == sf::Keyboard::Enter && !startGame){
					startGame = 1;
					bird.setShouldFly(true);
				}
				if (evnt.key.code == sf::Keyboard::Space && startGame) bird.flapBird(dt);
			}
			if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left && !runGame) {
				if (restartText.getGlobalBounds().contains(evnt.mouseButton.x, evnt.mouseButton.y)) {
					restartGame();
				}
			}
		}
		doProcessing(dt);
		draw();
		win.display();	//display window
	}
}

void Game::doProcessing(sf::Time& dt)
{
	if (startGame) {
		moveGround(dt);
		if (pipeCounter > pipeSpawnTime) {
			pipes.push_back(Pipe(dist(rd)));
			pipeCounter = 0;
		}
		pipeCounter++;
		for (int i = 0; i < pipes.size(); i++) {
			pipes[i].update(dt);
			if (pipes[i].getRightBound() < 0) pipes.erase(pipes.begin() + i);
		}
		checkCollisions();
		countScore();
	}
	bird.update(dt);
}

void Game::draw() {
	win.draw(bgSprite);
	for (Pipe pipe : pipes) {
		win.draw(pipe.spriteDown);
		win.draw(pipe.spriteUp);
	}
	win.draw(groundSprite1);
	win.draw(groundSprite2);
	win.draw(bird.birdSprite);
	win.draw(scoreText);
	if (!runGame) win.draw(restartText);
}

void Game::checkCollisions()
{
	if (pipes.size() > 0) {
		if (pipes[0].spriteDown.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
			pipes[0].spriteUp.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
			bird.birdSprite.getGlobalBounds().top >= 540) {
			startGame = false;
			runGame = false;
		}
	}
}

void Game::restartGame()
{
	bird.resetBirdPosition();
	bird.setShouldFly(false);
	runGame = true;
	startGame = false;
	pipeCounter = 71;
	pipes.clear();
	score = 0;
	scoreText.setString("Score: 0");
}

void Game::countScore()
{
	if (pipes.size() > 0) {
		if (!startMonitoring) {
			if (bird.birdSprite.getGlobalBounds().left > pipes[0].spriteDown.getGlobalBounds().left &&
				bird.getRightBound() < pipes[0].getRightBound()) {
				startMonitoring = true;
			}
		}
		else {
			if (bird.birdSprite.getGlobalBounds().left > pipes[0].getRightBound()) {
				score = score + 1;
				scoreText.setString("score: " + to_string(score));
				startMonitoring = false;
			}
		}
	}
}

std::string Game::to_string(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

void Game::moveGround(sf::Time& dt) {
	groundSprite1.move(-moveSpeed * dt.asSeconds(), 0.0f);
	groundSprite2.move(-moveSpeed * dt.asSeconds(), 0.0f);

	if (groundSprite1.getGlobalBounds().left + groundSprite1.getGlobalBounds().width < 0) {
		groundSprite1.setPosition(groundSprite2.getGlobalBounds().left + groundSprite2.getGlobalBounds().width, 578);
	}
	if (groundSprite2.getGlobalBounds().left + groundSprite2.getGlobalBounds().width < 0) {
		groundSprite2.setPosition(groundSprite1.getGlobalBounds().left + groundSprite1.getGlobalBounds().width, 578);
	}
}


