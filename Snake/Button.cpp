#include "Button.hpp"

Button::Button()
{
	if(!font.loadFromFile("..\\UIpack\\Font\\kenvector_future.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
}

bool Button::LoadTexture(std::string filePath)
{
	if (!texture.loadFromFile(filePath))
	{
		return EXIT_FAILURE;
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	sprite.setTexture(texture);
	std::cout << "Texture loaded" << std::endl;
	return EXIT_SUCCESS;
}

bool Button::LoadTexture(std::string filePath, sf::IntRect rect)
{
	if (!texture.loadFromFile(filePath, rect))
	{
		return EXIT_FAILURE;
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	sprite.setTexture(texture);
	std::cout << "Texture loaded" << std::endl;
	return EXIT_SUCCESS;
}

void Button::SetPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Button::SetText(std::string text)
{
	this->text.setString(text);
}

void Button::SetTextPosition(sf::Vector2f position)
{
	text.setPosition(position);
}

void Button::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(text);
}
