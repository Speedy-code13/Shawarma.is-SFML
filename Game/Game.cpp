#include "Game.h"

//Initializers
void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
    this->updatedRes = false;
    this->iconLoaded = false;

}
void Game::initWindow()
{
    this->title = "Shawarma.is";
    this->windowBounds = sf::VideoMode::getDesktopMode();
    this->framerateLimit = 120;
    this->fullscreen = true;
    if (this->fullscreen)
        this->window = std::make_shared<sf::RenderWindow>(this->windowBounds, this->title, sf::Style::Fullscreen);
    else
        this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), this->title, sf::Style::Close );
        this->window->setFramerateLimit(this->framerateLimit);
   
 
    
    
}


void Game::initIcon()
{
    if (this->icon.loadFromFile("Resources/Images/Players/shaorma.png"))
    {
        this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
        this->iconLoaded = true;
    }
       
}

void Game::initStates()
{
    this->stateData.window = this->window;
    this->stateData.dt = &this->dt;
    this->stateData.states = &this->states;
        this->states.push(new MainMenuState(&stateData, &this->music));

}



void Game::updateResolution()
{
    
    
    this->states.top()->updateResolution();
   
    this->window->setFramerateLimit(this->framerateLimit);

    if(this->iconLoaded)
        this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}


//Private Functions
void Game::updateEvents()
{
    while (window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->states.top()->endState();
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            switch (this->event.key.code)
            {
            case sf::Keyboard::Key::Escape:
                this->states.top()->endState();
                break;
            case sf::Keyboard::Key::F11:               
                if (this->fullscreen)
                {
                    
                    this->window->create(sf::VideoMode(1280, 720), this->title,  sf::Style::Close);                   
                    this->updateResolution();
                    this->fullscreen = false;

                }
                else
                {
                    this->window->create(this->windowBounds, this->title, sf::Style::None);
                    this->updateResolution();
                    this->fullscreen = true;
                }
           
                break;
         
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.mouseButton.button == sf::Mouse::Left)
                this->states.top()->updateMusicButton();
                break;

           
        }
        
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();

}

void Game::endApplication()
{
    this->window->close();
}

void Game::update()
{
    
    this->updateEvents();
    
    this->updateDt();
   

    if (!this->states.empty())
    {
       if(this->window->hasFocus())
       {
          this->states.top()->update();
          if (this->states.top()->getQuit())
          {
            this->updatedRes = this->states.top()->getUpdatedRes();
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();

            if (this->updatedRes)
            {
                this->states.top()->updateResolution();
                this->updatedRes = false;
            }
          }

        }
    }
    else
    {
        this->endApplication();
    }
}

void Game::render()
{
    this->window->clear();
    if (!this->states.empty())
        this->states.top()->render();
    this->window->display();
}

//Constructor & Deconstructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initIcon();
    this->initStates();
  
    
}

Game::~Game()
{
    while (!this->states.empty())
    {
        delete states.top();
        this->states.pop();
    }
}

//Game core
void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();

    }
}
