
#pragma once
#include "MainMenuState.h"



class Game
{
private:
	//Variables
	std::string title;
	float dt;
	bool fullscreen;
	bool iconLoaded;
	bool updatedRes;
	unsigned short  framerateLimit;
	std::map<std::string, int> supportedKeys;
	

	//SFML variables
	sf::Image icon;
	sf::Music music;
	std::shared_ptr<sf::RenderWindow> window;
	std::stack<State*> states;
	StateData stateData;
	sf::Event event;	
	sf::VideoMode windowBounds;	
	sf::Clock dtClock;
private:
	//Initializers
	void initVariables();
	void initWindow();
	void initIcon();
	void initStates();
	
	//Private Functions
	void updateResolution();
	void updateEvents();
	void updateDt();
	void endApplication();
	void update();
	void render();
public:
	//Constructor & Deconstructor
	Game();
	~Game();

	//Game core
	void run();
};

