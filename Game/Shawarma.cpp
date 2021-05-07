#include "Shawarma.h"

//Constructor
Shawarma::Shawarma(sf::Texture* texture, sf::Vector2f map_size)
{
	this->shape.setRadius(static_cast<float>(rand() % 30 + 15));
	this->shape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % int(map_size.x - this->shape.getGlobalBounds().width)),
			static_cast<float>(rand() % int(map_size.y - this->shape.getGlobalBounds().height))
		)
	);
	this->shape.setTexture(texture);

}

//Accesors
const sf::FloatRect Shawarma::getGlobal() const
{
	return this->shape.getGlobalBounds();
}


//Functions

void Shawarma::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
