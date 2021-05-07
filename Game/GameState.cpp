#include "GameState.h"

/// Initializers
void GameState::initVariables()
{
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxShawarmas = 200;
	this->massDivider = 3;
	this->initialMass = 350;
	this->mass = this->initialMass;
}
void GameState::initTextures()
{	
	this->textures["BG"].loadFromFile("Resources/Images/Backgrounds/bg2.jpg");
	this->textures["SHAWARMA"].loadFromFile("Resources/Images/Players/shaorma.png");	
	this->textures["EMINEM"].loadFromFile("Resources/Images/Players/eminem.png");
}
void GameState::initFont()
{
	this->font.loadFromFile("Resources/Fonts/arial.ttf");
}
void GameState::initMap()
{
	this->mapSize = { 5000.f, 2500.f };
	this->mapRect.setFillColor(sf::Color::Transparent);
	this->mapRect.setOutlineColor(sf::Color::Red);
	this->mapRect.setOutlineThickness(10.f);
	this->mapRect.setSize(this->mapSize);
}
//Initializers
void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->background.setTexture(&this->textures["BG"]);
}



void GameState::initPlayer()
{
	this->player = std::make_unique<Player>(Player(this->mapSize, this->initialMass / massDivider));
	this->player->setTexture(&this->textures["EMINEM"]);
	
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(this->window->getPosition().x, this->window->getPosition().y));
	this->view.setCenter(sf::Vector2f(this->window->getPosition().x / 2.f, this->window->getPosition().y / 2.f));
	
	
}
//Functions
void GameState::endState()
{
	this->saveGame();
	this->quit = true;
}
void GameState::playerDeath()
{
	this->mass = initialMass;
	this->player->updateSize(mass / massDivider);
	this->player->setPosition(rand() % int(this->mapSize.x), rand() % int(this->mapSize.y));
}
void GameState::updateView()
{
	this->view.setCenter(this->player->getPosition().x + this->player->getSize().x / 2.f,
		this->player->getPosition().y + this->player->getSize().y / 2.f);
	this->view.setSize(this->window->getSize().x + mass / 3, this->window->getSize().y + mass / 3);
	//this->view.setSize(this->mapSize);
	
}
void GameState::updateResolution()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->updatedRes = true;
}
void GameState::updatePlayerCollisionShawarmas()
{
	for (unsigned int i = 0; i < this->shawarmas.size(); i++)
	{

		if (this->player->getGlobal().intersects(this->shawarmas[i]->getGlobal()))
		{

			this->mass++;
			this->player->updateSize(this->mass / massDivider);
			this->shawarmas.erase(this->shawarmas.begin() + i);
		}
	}
}
void GameState::updateMassText()
{
	std::stringstream ss;
	ss << "Mass: " << this->mass;
	this->massText.setString(ss.str());
}
void GameState::updatePlayer()
{	
	this->player->update(*this->dt, this->window);

	//Left
	if (this->player->getGlobal().left <= 0.f)
		this->playerDeath();
	//Right
	else if (this->player->getGlobal().left + this->player->getGlobal().width >= this->mapSize.x) 
		this->playerDeath();
	//Up
	if (this->player->getGlobal().top <= 0.f) 
		this->playerDeath();
	//Down
	else if (this->player->getGlobal().height + this->player->getGlobal().top >= this->mapSize.y) 
		this->playerDeath();
	
}
void GameState::updateMusic()
{
	if (this->music->getPlayingOffset().asSeconds() >= 40.f)
		this->player->setMovementSpeed(600.f);
	else if (this->music->getPlayingOffset().asSeconds() >= 58.f)
		this->player->setMovementSpeed(1000.f);
	if (this->music->getStatus() == sf::SoundStream::Paused)
		this->player->setMovementSpeed(300.f);
}
void GameState::renderShawarmas()
{
	for (auto it : this->shawarmas)
		it->render(*this->window);
}
void GameState::spawnShawarmas()
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else if (this->shawarmas.size() < this->maxShawarmas)
	{

		this->shawarmas.push_back(new Shawarma(&this->textures["SHAWARMA"], this->mapSize));

	}
}
void GameState::saveGame()
{
	std::ofstream ofs("Resources/Saves/game.txt");
	ofs << this->mass << "\n";
	ofs << this->player->getPosition().x << "\n";
	ofs << this->player->getPosition().y << "\n";
	ofs.close();
}
void GameState::loadGame()
{
	float x, y;
	std::ifstream ifs("Resources/Saves/game.txt");
	ifs >> this->mass;
	ifs >> x;
	ifs >> y;
	ifs.close();
	this->player->setPosition(x, y);
	this->player->updateSize(this->mass / massDivider);
}


//Constructor & Deconstructor
GameState::GameState(StateData* stateData, bool new_game, sf::Music* music)
	: State(stateData), newGame(new_game), music(music)
{
	
	this->initVariables();
	this->initTextures();
	this->initFont();
	this->initMap();
	this->initBackground();
	this->initPlayer();
	this->initView();
	this->massText.setFont(this->font);
	if (!this->newGame)
		this->loadGame();
}

GameState::~GameState()
{
	for (auto* it : this->shawarmas)
		delete it;
}

void GameState::update()
{
	this->updateMousePositions();
	this->updatePlayer();
	this->updateView();
	this->updateMassText();
	this->updatePlayerCollisionShawarmas();
	this->spawnShawarmas();
	this->updateMusic();

}

void GameState::render()
{
	this->window->setView(this->window->getDefaultView()); // Background	
	this->window->draw(background);

	this->window->setView(view); // Game Stuff	
	this->window->draw(this->mapRect);
	this->renderShawarmas();
	this->player->render(this->window);

	this->window->setView(this->window->getDefaultView()); // UI	
	this->window->draw(this->massText);



	
}
