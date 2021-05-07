#pragma once
#include "GameState.h"

enum class BUTTON {MAX, LOWER, OFF};
class MainMenuState : public State
{
private:

	BUTTON buttonState;

	sf::RectangleShape background;
	sf::Text mousePos;
	sf::Music* music;
	sf::RectangleShape musicButton;
	sf::Font font;


	std::map<std::string, std::unique_ptr<Button>> buttons;

private:
	//Initializers
	void initVariables();
	void initFont();
	void initTextures();
	void initMusicButton();
	void initBackground();
	void initButtons();


	//Private Functions
	void positionButton(const std::string &name, const float offset);
	void positionButtons();
	void updateMusicButton();
	void updateResolution();
	void updateButtons();
public:
	//Constructor & Deconstructor
	MainMenuState(StateData* stateData, sf::Music* music);
	virtual ~MainMenuState();

	
	void update();
	void render();
};

