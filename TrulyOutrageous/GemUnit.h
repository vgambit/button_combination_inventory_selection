#ifndef GEMUNIT_H
#define GEMUNIT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gem.h"

class GemUnit
{
public:
	GemUnit(int posx, int posy);
	~GemUnit();

	void Update(int currentTime, std::string stickDirection, bool isLpPressed, bool isMpPressed, bool isLkPressed);
	void Draw(sf::RenderWindow &app);

private:
	Gem* gems[3];
	int posX, posY, currentGem;
};
#endif