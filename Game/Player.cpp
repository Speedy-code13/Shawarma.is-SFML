#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 300.f;
}


void Player::initObj( unsigned int initialMass)
{
	
	this->obj.setSize(sf::Vector2f( initialMass, initialMass));
	//this->obj.setOrigin(this->obj.getSize() / 2.f);
	this->obj.setPosition(sf::Vector2f(rand() % int(this->mapSize.x), rand() % int(this->mapSize.y)));
	
	
}

//Constructor
Player::Player(const sf::Vector2f map_size, unsigned int initialMass)
	:mapSize(map_size)
{
	this->initVariables();
	this->initObj( initialMass);
}


//Accesors
void Player::setTexture(sf::Texture* texture) { this->obj.setTexture(texture); }

void Player::setPosition(float x, float y) { this->obj.setPosition({ x, y }); }

void Player::setMovementSpeed(float movement_speed)
{
	this->movementSpeed = movement_speed;
}



const sf::FloatRect Player::getGlobal() const {	return this->obj.getGlobalBounds(); }

const sf::Vector2f Player::getSize() const { return this->obj.getSize();}

const sf::Vector2f Player::getPosition() const{	return this->obj.getPosition(); }



void Player::updateSize(float  mass)
{
	obj.setSize({ mass, mass });
	//this->obj.setOrigin(this->obj.getSize() / 2.f);
}



//Functions
void Player::update(float dt, std::shared_ptr<sf::RenderWindow> window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		obj.move(0.f, (this->movementSpeed * -1.f) * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		
		obj.move(0.f, (this->movementSpeed * 1.f) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		obj.move((this->movementSpeed * 1.f) * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		obj.move((this->movementSpeed * -1.f) * dt, 0.f);
	}
}

void Player::render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->obj);
}
