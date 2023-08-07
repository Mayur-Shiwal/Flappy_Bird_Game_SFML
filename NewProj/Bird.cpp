#include "Bird.h"
#include"Globals.h"

Bird::Bird() :
	gravity(20),
	flapSpeed(450),
	anim_counter(0),
	textureSwitch(1),
	shouldFly(0)
{
	textures[0].loadFromFile("assets/birddown.png");
	textures[1].loadFromFile("assets/birdup.png");

	birdSprite.setTexture(textures[0]);
	birdSprite.setScale(ScaleFactor, ScaleFactor);
	resetBirdPosition();

}


void Bird::setShouldFly(bool shouldFly)
{
	this->shouldFly = shouldFly;
}

void Bird::flapBird(sf::Time &dt)
{
	velocity_y = -flapSpeed * dt.asSeconds();

}

void Bird::resetBirdPosition()
{
	birdSprite.setPosition(100, 50);
	velocity_y = 0;
}

void Bird::update(sf::Time& dt)
{
	if (birdSprite.getGlobalBounds().top < 548 && shouldFly) {
		if (anim_counter == 4) {
			birdSprite.setTexture(textures[textureSwitch]);
			textureSwitch = (textureSwitch) ? 0 : 1;
			anim_counter = 0;
		}
		anim_counter = anim_counter + 1;
		velocity_y += gravity * dt.asSeconds();
		birdSprite.move(0, velocity_y);
		if (birdSprite.getGlobalBounds().top < 0) birdSprite.setPosition(100, 0);
	}
}

float Bird::getRightBound()
{
	return birdSprite.getGlobalBounds().left + birdSprite.getGlobalBounds().width;
}


