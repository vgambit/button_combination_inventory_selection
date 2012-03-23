#include "Digit.h"
#include <iostream>
#include <sstream>

Digit::Digit()
{
	for (int i = 0; i < 10; i++)
	{
		std::stringstream currentFile;
		currentFile << i << ".png";
		digits[i].LoadFromFile(currentFile.str()); // need to check for failure
	}

	totalTime = 0;
	currentNumber = 5;
	currentDisplayedNumber = 5;
	currentState = NotSet;
	currentDigit.SetTexture(digits[5]);
	opacityLevel = 100;
	currentDigit.SetColor(sf::Color(255, 255, 255, opacityLevel));
	incrementingTime = true;
}

sf::Sprite Digit::GetSprite()
{
	if (currentDisplayedNumber != currentNumber)
	{
		currentDisplayedNumber = currentNumber;
		currentDigit.SetTexture(digits[currentNumber]);
	}
	
	currentDigit.SetColor(sf::Color(255, 255, 255, opacityLevel));
	return currentDigit;
}

void Digit::SetDigit(int digit)
{
	if ((digit < 10) && (digit > -1))
		currentNumber = digit;
}

void Digit::SetState(State state)
{
	currentState = state;
	if (currentState == Set)
		opacityLevel = 255;
	else if (currentState == NotSet)
		opacityLevel = 100;
}

void Digit::Update(int currentTime, std::string stickDirection)
{
	this->CheckHighlight(stickDirection);
	if (incrementingTime)
	{
		totalTime += currentTime;
		if (totalTime >= 1000)
			incrementingTime = false;
	}
	else
	{
		totalTime -= currentTime;
		if (totalTime <= 100)
			incrementingTime = true;
	}
	
	if (currentState == Current)
		opacityLevel = 255 * ((float)totalTime / 1000);	
}

void Digit::CheckHighlight(std::string stickDirection)
{
	if (this->currentState == Current)
	{	
		if(stickDirection == "db")
			this->SetDigit(1);
		else if(stickDirection == "d")
			this->SetDigit(2);
		else if(stickDirection == "df")
			this->SetDigit(3);
		else if(stickDirection == "b")
			this->SetDigit(4);
		else if(stickDirection == "n")
			this->SetDigit(5);
		else if(stickDirection == "f")
			this->SetDigit(6);
		else if(stickDirection == "ub")
			this->SetDigit(7);
		else if(stickDirection == "u")
			this->SetDigit(8);
		else if(stickDirection == "uf")
			this->SetDigit(9);
	}
}

void Digit::SetPosition(int posx, int posy)
{
	this->currentDigit.SetPosition((float)posx, (float)posy);
}