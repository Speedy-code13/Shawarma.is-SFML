#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>


class Shawarma
{
private:
	//Shape
	sf::CircleShape shape;

public:
	//Constructors 
	Shawarma(sf::Texture* texture, sf::Vector2f map_size);
	
	//Accesors
	const sf::FloatRect getGlobal() const;
	//Functions
	void render(sf::RenderTarget& target);
};

