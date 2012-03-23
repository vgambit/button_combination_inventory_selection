#ifndef GEM_H
#define GEM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Digit.h"

class Gem
{
public:
	Gem(int posx, int posy, bool isactive);
	~Gem();

	void Update(int currentTime, std::string stickDirection, bool isLpPressed, bool isMpPressed, bool isLkPressed);
	void Draw(sf::RenderWindow &app);
	void Reopen(); // returning to a gem that has already been set
	void EnableDisplay();
	void Confirm(); // done with the current gem
	void Deactivate(); // going back to the previous gem
	int GetCurrentDigit();

private:
	Digit* digits[3];
	int posX, posY, currentDigit;
	bool isDisplayed;
	bool isCurrent;
};


#endif