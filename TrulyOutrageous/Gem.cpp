#include "Gem.h"

Gem::Gem(int posx, int posy, bool isactive)
{
	this->posX = posx;
	this->posY = posy;

	for (int i=0; i<3; i++)
	{
		this->digits[i] = new Digit();
		digits[i]->SetPosition(posX + i*55, posY);
	}

	this->currentDigit = 0;
	this->isDisplayed = isactive;
	this->isCurrent = isactive;
}

Gem::~Gem() {}

void Gem::Update(int currentTime, std::string stickDirection, bool isLpPressed, bool isMpPressed, bool isLkPressed)
{
	if (this->isDisplayed && this->isCurrent)
	{
		if ((currentDigit > -1) && (currentDigit < 3))
		{
			this->digits[currentDigit]->SetState(Digit::State::Current);
			this->digits[currentDigit]->Update(currentTime, stickDirection);
			if (isMpPressed)
			{
				this->digits[currentDigit]->SetState(Digit::State::Set);
				this->digits[currentDigit]->SetDigit(0);
				currentDigit++;
			}
			else if (isLkPressed)
			{
				this->digits[currentDigit]->SetDigit(5);
				this->digits[currentDigit]->SetState(Digit::State::NotSet);
				currentDigit--;
			}
			else if (isLpPressed)
			{
				this->digits[currentDigit]->SetState(Digit::State::Set);
				currentDigit++;
			}	

			if (currentDigit > 2)
				currentDigit = 2;
			else if (currentDigit < 0)
				currentDigit = 0;
		}
	}
}

void Gem::Reopen()
{
	currentDigit = 2;
	isCurrent = true;
}

void Gem::Confirm()
{
	this->isCurrent = false;
}

void Gem::Deactivate()
{
	this->isCurrent = false;
	this->isDisplayed = false;
}

int Gem::GetCurrentDigit()
{
	return this->currentDigit;
}

void Gem::EnableDisplay()
{
	isDisplayed = true;
	isCurrent = true;
	digits[currentDigit]->SetState(Digit::State::Current);
}

void Gem::Draw(sf::RenderWindow &app)
{
	if (this->isDisplayed)
	{
		for(int i=0;i<3;i++)
		{
			app.Draw(digits[i]->GetSprite());
		}
	}
}