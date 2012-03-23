#include "GemUnit.h"

GemUnit::GemUnit(int posx, int posy)
{
	this->posX = posx;
	this->posY = posy;
	this->gems[0] = new Gem(posX, posY, true);
	for(int i=1; i<3; i++)
		this->gems[i] = new Gem(posX, posY + 75*i, false);
	this->currentGem = 0;
}
GemUnit::~GemUnit() {}

void GemUnit::Update(int currentTime, std::string stickDirection, bool isLpPressed, bool isMpPressed, bool isLkPressed)
{
	// there are 3 gems per gem unit right now, but magic numbers are still bad
	if ((currentGem > -1) && (currentGem < 3))
	{
		if (isMpPressed && (gems[currentGem]->GetCurrentDigit() == 2) && (currentGem < 2))
		{
			this->gems[currentGem]->Update(currentTime, stickDirection, isLpPressed, isMpPressed, isLkPressed);
			this->gems[currentGem]->Confirm();
			currentGem++;
			this->gems[currentGem]->EnableDisplay();
			isMpPressed = false;
		}
		else if (isLkPressed && (gems[currentGem]->GetCurrentDigit() == 0) )
		{
			if ((currentGem > 0))
			{
				this->gems[currentGem]->Update(currentTime, stickDirection, isLpPressed, isMpPressed, isLkPressed);
				this->gems[currentGem]->Deactivate();
				currentGem--;
				this->gems[currentGem]->Reopen();
				isLkPressed = false;
			}
			else if (currentGem == 0){}
		}
		else if (isLpPressed && (gems[currentGem]->GetCurrentDigit() == 2))
		{
			if (currentGem < 2)
			{
				this->gems[currentGem]->Update(currentTime, stickDirection, isLpPressed, isMpPressed, isLkPressed);
				this->gems[currentGem]->Confirm();
				currentGem++;
				this->gems[currentGem]->EnableDisplay();
				isLpPressed = false;
			}
			else if (currentGem == 2)
			{
				this->gems[currentGem]->Update(currentTime, stickDirection, isLpPressed, isMpPressed, isLkPressed);
				this->gems[currentGem]->Confirm();
				currentGem++;
			}
		}	
		else
			this->gems[currentGem]->Update(currentTime, stickDirection, isLpPressed, isMpPressed, isLkPressed);
	}
	else if ((currentGem == 3) && isLkPressed)
	{
		currentGem--;
		gems[currentGem]->Reopen();
	}
}
void GemUnit::Draw(sf::RenderWindow &app)
{
	for(int i=0; i<3; i++)
	{
		gems[i]->Draw(app);
	}
}
