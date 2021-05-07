#include "CharactersState.h"

//Constructor
CharactersState::CharactersState(StateData* stateData)
	: State(stateData)
{
	this->initTextures();
	this->initBackground();
}


//Initializers
void CharactersState::initTextures()
{
	this->textures["BG"].loadFromFile("Resources/Images/Backgrounds/bg3.jpg");
}

void CharactersState::initBackground()
{
	this->bg.setSize(sf::Vector2f( this->window->getSize().x, this->window->getSize().y	));
	this->bg.setTexture(&this->textures["BG"]);
}

//Core Functions
void CharactersState::updateResolution()
{
	this->bg.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->updatedRes = true;
}

void CharactersState::update()
{
	this->updateMousePositions();
}

void CharactersState::render()
{
	this->window->draw(bg);

	
}
