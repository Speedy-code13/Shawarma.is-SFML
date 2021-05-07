#include "Button.h"


//Constructor / Deconstructor
Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{

	this->buttonState = BTN_IDLE;
	this->shape.setPosition({ x, y });
	this->shape.setSize({ width, height });

	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(18);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

Button::~Button()
{



}
void Button::setSize(float x,float  y)
{
	this->shape.setPosition({ x, y });
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}
const sf::Vector2f Button::getSize() const
{
	return this->shape.getSize();
}
const sf::FloatRect Button::getGlobal() const
{
	return this->shape.getGlobalBounds();
}
//Acessors
const bool Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;

}
//Functions

void Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/


	
	//Idle
	this->buttonState = BTN_IDLE;
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}

}

void Button::render(std::shared_ptr<sf::RenderWindow> target)
{
	
	target->draw(this->shape);
	target->draw(this->text);
}
