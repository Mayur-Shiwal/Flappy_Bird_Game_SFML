#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(int yPosition)
{
	spriteDown.setTexture(textureDown);
	spriteUp.setTexture(textureUp);

	spriteDown.setScale(ScaleFactor, ScaleFactor);
	spriteUp.setScale(ScaleFactor, ScaleFactor);

	spriteUp.setPosition(WinWidth, yPosition);
	spriteDown.setPosition(WinWidth, yPosition - pipeDistance - spriteUp.getGlobalBounds().height);
}

void Pipe::loadTextures()
{
	textureDown.loadFromFile("assets/pipedown.png");
	textureUp.loadFromFile("assets/pipe.png");
}

void Pipe::update(sf::Time &dt)
{
	spriteUp.move(-moveSpeed * dt.asSeconds(), 0);
	spriteDown.move(-moveSpeed * dt.asSeconds(), 0);
}

float Pipe::getRightBound()
{
	return spriteDown.getGlobalBounds().left + spriteDown.getGlobalBounds().width;
}

sf::Texture Pipe::textureDown, Pipe::textureUp;
int Pipe::pipeDistance = 150, Pipe::moveSpeed = 400;
