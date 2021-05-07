#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>		
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include <map>
#include <stack>
#include <fstream>
enum button_states { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;
	//Variables
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


public:
	//Constructor / Deconstructor
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();


	//Acessors
	void setSize(float x, float y);
	const sf::Vector2f getSize() const;
	const sf::FloatRect getGlobal() const;
	const bool isPressed() const;




	//Functions
	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderWindow> target);

};

