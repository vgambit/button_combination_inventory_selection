#ifndef DIGIT_H
#define DIGIT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Digit
{	
public:
	enum State 
	{
		// fade in/out
		Current,  

		// 255 alpha
		Set,

		// 100 alpha
		NotSet
	};

	Digit();
	~Digit();

	sf::Sprite GetSprite(); // returns Sprite of current number
	void SetDigit(int digit = 5);
	void SetState(State state);
	void Update(int currentTime, std::string stickDirection);
	void CheckHighlight(std::string stickDirection);
	void SetPosition(int posx, int posy);
	
private:
	int opacityLevel; // 0-255
	int totalTime; 
	bool incrementingTime; // used to calculate fade out level
	int currentNumber; // 0-9
	int currentDisplayedNumber;
	sf::Texture digits[10];
	sf::Sprite currentDigit;
	State currentState;
};
#endif