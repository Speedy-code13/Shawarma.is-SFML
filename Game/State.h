#pragma once
#include "Button.h"

class State;
struct StateData
{
	std::shared_ptr<sf::RenderWindow> window;
	const float* dt;
	std::stack<State*>* states;	
};
class State
{
protected:
	StateData* stateData;
	std::shared_ptr<sf::RenderWindow> window;
	std::stack<State*>* states;
	std::map<std::string, sf::Texture> textures;
	bool updatedRes;
	const float* dt;
	
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	
public:
	//Constructor
	State(StateData* stateData);

	//Accesors
	const bool& getQuit() const;
	const bool& getUpdatedRes() const;
	//Functions	
	virtual void endState();

	virtual void updateMousePositions();
	virtual void updateMusicButton();
	virtual void updateResolution() = 0;
	virtual void render() = 0;
	virtual void update() = 0;

};

