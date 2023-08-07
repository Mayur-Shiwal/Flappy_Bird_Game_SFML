#pragma once
#include <SFML/Graphics.hpp>


class Bird
{
private:
	sf::Texture textures[2];
	const int gravity;
	const int flapSpeed;
	float velocity_y;
	int anim_counter, textureSwitch;
	bool shouldFly;

public:
	sf::Sprite birdSprite;
	Bird();
	void setShouldFly(bool);
	void flapBird(sf::Time &time);
	void resetBirdPosition();
	void update(sf::Time &time);
	float getRightBound();
};

