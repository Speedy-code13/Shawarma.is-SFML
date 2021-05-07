#pragma once
#include "State.h"
#include "Player.h"
#include "Shawarma.h"
class GameState : public State
{
private:

	//Variables
	bool newGame;
	sf::Vector2f mapSize;
	sf::RectangleShape mapRect;
	sf::RectangleShape background;
	std::unique_ptr<Player> player;
	sf::View view;
	std::vector<Shawarma*> shawarmas;
	sf::Font font;
	sf::Text massText;
	unsigned int maxShawarmas;
	unsigned int mass;
	unsigned int initialMass;
	float spawnTimer;
	float spawnTimerMax;
	sf::Music* music;

	int massDivider;


	
	//Initializers
	void initVariables();
	void initTextures();
	void initFont();
	void initMap();
	void initBackground();
	void initPlayer();
	void initView();

	//Functions
	void spawnShawarmas();
	void saveGame();
	void loadGame();
	void endState();
	void playerDeath();

	void updateView();
	void updateResolution();
	void updatePlayerCollisionShawarmas();
	void updateMassText();
	void updatePlayer();
	void updateMusic();
	void renderShawarmas();
	
	


public:
	//Constructor & Deconstructor
	GameState(StateData* stateData, bool new_game, sf::Music* music);
	virtual ~GameState();

	void update();
	void render();
};

