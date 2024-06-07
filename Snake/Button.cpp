#include "Button.hpp"

Button::Button()
{
}

Button::Button(sf::Font& font)
{
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
}

void Button::SetPosition(sf::Vector2f position)
{
	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
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

void Button::SetTextFillColor(sf::Color color)
{
	text.setFillColor(color);
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

void Button::SetSprite(sf::Texture& texture)
{
	sprite.setTexture(texture);
}
