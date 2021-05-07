#include "MainMenuState.h"
#include "CharactersState.h"

void MainMenuState::updateResolution()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->positionButtons();
	this->musicButton.setPosition({ 0.f, this->window->getSize().y - this->musicButton.getGlobalBounds().height });
	
	
}

void MainMenuState::updateButtons()
{
	for (auto& i : buttons)
		i.second->update(this->mousePosView);

	if (this->buttons["NEW_GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->stateData, true, this->music));
	else if (this->buttons["LOAD_GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->stateData,false, this->music));
	else if (this->buttons["CHARACTERS_STATE"]->isPressed())
		this->states->push(new CharactersState(this->stateData));
	else if (this->buttons["EXIT_STATE"]->isPressed())
		this->window->close();
}



void MainMenuState::positionButton(const std::string &name, const float offset)
{ 
	this->buttons[name]->setSize(this->window->getSize().x / 2.f - this->buttons[name]->getGlobal().width / 2.f, this->window->getSize().y / 2.f - this->buttons[name]->getGlobal().height / 2.f + offset);
}

void MainMenuState::positionButtons()
{
	this->positionButton("NEW_GAME_STATE", -200.f);
	this->positionButton("LOAD_GAME_STATE", -100.f);
	this->positionButton("CHARACTERS_STATE", 0.f);
	this->positionButton("EXIT_STATE", 100.f);

}

void MainMenuState::updateMusicButton()
{

	if (this->musicButton.getGlobalBounds().contains(this->mousePosView))
	{
		switch (this->buttonState)
		{
		case BUTTON::MAX:
			this->musicButton.setTexture(&this->textures["BUTTON_LOWER"]);
			this->music->setVolume(50.f);
			this->buttonState = BUTTON::LOWER;
			break;
		case BUTTON::LOWER:
			this->musicButton.setTexture(&this->textures["BUTTON_OFF"]);
			this->music->pause();
			this->buttonState = BUTTON::OFF;
			break;
		case BUTTON::OFF:
			this->musicButton.setTexture(&this->textures["BUTTON_MAX"]);
			this->music->setVolume(100.f);
			this->music->play();
			this->buttonState = BUTTON::MAX;

			break;
		}
	
	}
}

		



void MainMenuState::initVariables()
{


}

void MainMenuState::initFont()
{
	this->font.loadFromFile("Resources/Fonts/arial.ttf");
}

void MainMenuState::initTextures()
{
	
	this->textures["BACKGROUND"].loadFromFile("Resources/Images/Backgrounds/bg1.jpg");
	this->textures["BUTTON_MAX"].loadFromFile("Resources/Images/Buttons/musicButton1.png");
	this->textures["BUTTON_LOWER"].loadFromFile("Resources/Images/Buttons/musicButton2.png");
	this->textures["BUTTON_OFF"].loadFromFile("Resources/Images/Buttons/musicButton3.png");

}

void MainMenuState::initMusicButton()
{
	this->buttonState = BUTTON::MAX;
	this->musicButton.setSize({ 100.f, 100.f });
	this->musicButton.setPosition({ 0.f, this->window->getSize().y - this->musicButton.getGlobalBounds().height });
	this->music->openFromFile("Resources/Audio/halo.wav");

	this->music->setLoop(true);

	switch (this->buttonState)
	{
	case BUTTON::MAX:
		this->musicButton.setTexture(&this->textures["BUTTON_MAX"]);
		this->music->setVolume(100.f);
		this->music->play();
		break;
	case BUTTON::LOWER:
		this->musicButton.setTexture(&this->textures["BUTTON_LOWER"]);
		this->music->setVolume(50.f);
		this->music->play();
		break;
	case BUTTON::OFF:
		this->musicButton.setTexture(&this->textures["BUTTON_OFF"]);
		this->music->play();
		this->music->pause();

		break;
	}
	
	
}

//Initializers
void MainMenuState::initBackground()
{
	
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	
	this->background.setTexture(&this->textures["BACKGROUND"]);
}

void MainMenuState::initButtons()
{	
	this->buttons["NEW_GAME_STATE"] = std::make_unique<Button>(0, 0, 250, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["LOAD_GAME_STATE"] = std::make_unique<Button>(0, 0, 250, 50,
		&this->font, "Load Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["CHARACTERS_STATE"] = std::make_unique<Button>(0, 0, 250, 50,
		&this->font, "Characters",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = std::make_unique<Button>(0, 0, 250, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	//Positions all the buttons corectly
	this->positionButtons();
}

//Constructor & Deconstructor
MainMenuState::MainMenuState(StateData* stateData, sf::Music* music)
	: State(stateData), music(music)
{	
	this->initVariables();
	this->initFont();
	this->initTextures();	
	this->initMusicButton();
	this->initBackground();
	this->initButtons();

}

MainMenuState::~MainMenuState()
{
	//std::cout << "Deleted  MainMenuState!\n";
}

void MainMenuState::update()
{
	//Updating the mouse position
	this->updateMousePositions();
	
	
	//Updating the buttons
	this->updateButtons();
	
	
}

void MainMenuState::render()
{

		//std::cout << "Drawing main menu background" << "\n";
		

		this->window->draw(this->background);
		//Rendering buttons
		for (auto& i : buttons)
			i.second->render(this->window);
		this->window->draw(this->musicButton);
		


	
}
