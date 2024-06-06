#include "Button.hpp"

Button::Button()
{
}

Button::Button(sf::Font& font)
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

bool Button::IsMouseOnButton(sf::RenderWindow& window)
{
	if (sf::Mouse::getPosition(window).x > sprite.getPosition().x - sprite.getLocalBounds().width / 2 &&
		sf::Mouse::getPosition(window).x < sprite.getPosition().x + sprite.getLocalBounds().width / 2 &&
		sf::Mouse::getPosition(window).y > sprite.getPosition().y - sprite.getLocalBounds().height / 2 &&
		sf::Mouse::getPosition(window).y < sprite.getPosition().y + sprite.getLocalBounds().height / 2)
	{
		return true;
	}
	return false;
}

//void Button::SetSprite(std::string filePath)
//{
//	sf::Texture newTexture;
//	if (!newTexture.loadFromFile(filePath)) {
//		// Fehlerbehandlung, z.B. Fehlermeldung ausgeben oder Ausnahme werfen
//		std::cerr << "Failed to load texture from file: " << filePath << std::endl;
//		return;
//	}
//
//	// Ersetzen der aktuellen Textur und des Sprites
//	texture = newTexture;
//	sprite.setTexture(texture);
//}
