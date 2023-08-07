#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include<vector>
#include "Pipe.h"
#include <random>

class Game
{

public:
	Game(sf::RenderWindow &window);
	sf::RenderWindow &win;
	void startGameLoop();

private:
	sf::Texture bgTexture, groundTexture;
	sf::Sprite bgSprite, groundSprite1, groundSprite2;
	Bird bird;
	bool startGame, runGame, startMonitoring;
	const int moveSpeed = 250;
	void draw();
	void moveGround(sf::Time& dt);
	void doProcessing(sf::Time &dt);
	void checkCollisions();
	void restartGame();
	void countScore();
	std::string to_string(int);
	int pipeCounter, pipeSpawnTime, score;
	std::vector<Pipe> pipes;
	std::random_device rd;
	std::uniform_int_distribution<int> dist{250, 550};
	sf::Font font;
	sf::Text restartText, scoreText;
};

