#include "State.h"

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = this->stateData->window;
	this->dt = this->stateData->dt;
	this->states = this->stateData->states;


	this->quit = false;
	this->updatedRes = false;
	
	
}


const bool& State::getQuit() const { return this->quit; }

const bool& State::getUpdatedRes() const { return this->updatedRes; }

void State::endState()
{	
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateMusicButton(){ }





