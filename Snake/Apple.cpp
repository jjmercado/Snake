#include "Apple.hpp"

Apple::Apple()
{
	srand(time(NULL));
	position = sf::Vector2f(rand() % 800, rand() % 600);
	sprite.setPosition(position);
	sprite.setTexture(TextureManager::getTexture("apple"));
	rect = sf::IntRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Apple::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Apple::Update()
{
}

sf::IntRect Apple::GetRect()
{
	return rect;
}

void Apple::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
	sprite.setPosition(position);
	rect = sf::IntRect(position.x, position.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}
