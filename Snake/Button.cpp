#include "Button.hpp"

Button::Button()
{
	LoadSpriteSheet("..\\UIpack\\Spritesheet\\blueSheet.png");

	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	sprite.setTexture(texture);

	if(!font.loadFromFile("..\\UIpack\\Font\\kenvector_future.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
}


bool Button::LoadTexture(std::string filePath)
{
	if (!texture.loadFromFile(filePath))
	{
		return EXIT_FAILURE;
	}
	std::cout << "Button loaded" << std::endl;
	return EXIT_SUCCESS;
}

bool Button::LoadTexture(sf::IntRect rect)
{
	//textureToCopy = ;
	if (!texture.loadFromImage(texture.copyToImage(), rect))
	{
		return EXIT_FAILURE;
	}
	std::cout << "Texture copied" << std::endl;
	return EXIT_SUCCESS;
}
bool Button::LoadSpriteSheet(std::string filePath)
{
	if (!textureSpriteSheet.loadFromFile(filePath))
	{
		return EXIT_FAILURE;
	}
	std::cout << "SpriteSheet loaded" << std::endl;
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
