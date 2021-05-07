#pragma once
#include "State.h"
class CharactersState : 
	public State
{
private:
	sf::RectangleShape bg;
private:
	//Initializers
	void initTextures();
	void initBackground();
public:
	//Constructor 
	CharactersState(StateData* stateData);

	//Core functions
	void updateResolution();
	void update();
	void render();

};

