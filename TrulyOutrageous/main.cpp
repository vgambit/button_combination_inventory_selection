#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "Digit.h"
#include "Gem.h"
#include "GemUnit.h"

int main()
{	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Truly Outrageous");	
	std::string currentDirection = "n";

	GemUnit* gemUnit;
	gemUnit = new GemUnit(200, 200);

	sf::SoundBuffer highlightBuffer, selectBuffer, backspaceBuffer;
	highlightBuffer.LoadFromFile("highlight.wav");
	selectBuffer.LoadFromFile("select.wav");
	backspaceBuffer.LoadFromFile("back.wav");

	sf::Sound highlightSound, selectSound, backspaceSound;	
	selectSound.SetBuffer(selectBuffer);
	highlightSound.SetBuffer(highlightBuffer);
	backspaceSound.SetBuffer(backspaceBuffer);

	bool lpNow = false, lpBefore = false, mpNow = false, mpBefore = false, lkNow = false, lkBefore = false;
		
	sf::Music music;
	if(!music.OpenFromFile("sfa3charselect.ogg"))
		return EXIT_FAILURE;

	int currentFrameTime = 0;

	music.SetVolume(40.f);
	music.Play();

	while(App.IsOpened())
	{
		sf::Event event;

		lpBefore = lpNow;
		lkBefore = lkNow;
		mpBefore = mpNow;

		currentFrameTime = App.GetFrameTime();

		if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == -38)
		{
			if (currentDirection != "db")
			{
				highlightSound.Play();
				currentDirection = "db";
			}
		}
		else if((sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) >= -1.f) && (sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) < 0.f))
		{
			if (currentDirection != "d")
			{
				highlightSound.Play();
				currentDirection = "d";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == 38)
		{
			if (currentDirection != "df")
			{
				highlightSound.Play();
				currentDirection = "df";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == -70)
		{
			if (currentDirection != "b")
			{
				highlightSound.Play();
				currentDirection = "b";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == 0)
		{
			if (currentDirection != "n")
			{
				highlightSound.Play();
				currentDirection = "n";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == 70)
		{
			if (currentDirection != "f")
			{
				highlightSound.Play();
				currentDirection = "f";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == -92)
		{
			if (currentDirection != "ub")
			{
				highlightSound.Play();
				currentDirection = "ub";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == 100)
		{
			if (currentDirection != "u")
			{
				highlightSound.Play();
				currentDirection = "u";
			}
		}
		else if((int)sf::Joystick::GetAxisPosition(0, sf::Joystick::Axis::PovX) == 92)
		{
			if (currentDirection != "uf")
			{
				highlightSound.Play();
				currentDirection = "uf";
			}
		}
		

		while(App.PollEvent(event))
		{
			//sf::Sleep(0.1f);
			if(event.Type == sf::Event::Closed)
				App.Close();
		}

		if (sf::Joystick::IsButtonPressed(0, 2))
			lpNow = true;
		else
			lpNow = false;

		if (sf::Joystick::IsButtonPressed(0, 3))
			mpNow = true;
		else
			mpNow = false;

		if (sf::Joystick::IsButtonPressed(0, 0))
			lkNow = true;
		else
			lkNow = false;

		if (lpNow && !lpBefore)
			selectSound.Play();

		if (mpNow && !mpBefore)
			selectSound.Play();

		if (lkNow && !lkBefore)
			backspaceSound.Play();

		gemUnit->Update(currentFrameTime, currentDirection, lpNow && !lpBefore, mpNow && !mpBefore, lkNow && !lkBefore);

		App.Clear();
		gemUnit->Draw(App);
		App.Display();
	}

	return EXIT_SUCCESS;
}