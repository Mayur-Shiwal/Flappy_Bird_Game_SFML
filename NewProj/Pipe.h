#pragma once
#include<SFML/Graphics.hpp>

class Pipe
{
public:
	Pipe(int);
	sf::Sprite spriteUp, spriteDown;
	static void loadTextures();
	void update(sf::Time &dt);
	float getRightBound();

private:
	static sf::Texture textureDown, textureUp;
	static int pipeDistance, moveSpeed;
};

