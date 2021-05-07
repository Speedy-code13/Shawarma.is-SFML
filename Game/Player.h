#pragma once
#include <SFML/Graphics.hpp>


class Player
{
private:
	sf::RectangleShape obj;
	float movementSpeed;
	sf::Vector2f mapSize;
private:
	//Initializers
	void initVariables();
	void initTextures();	
	
public:
	//Constructor
	Player(const sf::Vector2f map_size, unsigned int initialMass);

	//Initializer Functions
	void initObj(unsigned int initialMass);

	//Accesors
	void setTexture(sf::Texture* texture);
	void setPosition(float x, float  y);
	void setMovementSpeed(float movement_speed);
	const sf::FloatRect getGlobal() const;
	const sf::Vector2f getSize() const;
	const sf::Vector2f getPosition() const;

	//Functions
	void updateSize(float mass);
	void update(float dt, std::shared_ptr<sf::RenderWindow>  window);
	void render(std::shared_ptr<sf::RenderWindow>  window);
};

