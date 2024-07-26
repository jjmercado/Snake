#include "Apple.hpp"
#include "Charakter.hpp"

Apple::Apple()
{
	srand(time(NULL));
	position = sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40);
	sprite.setPosition(position);
	sprite.setTexture(TextureManager::getTexture("apple"));
	rect = sf::IntRect(position.x, position.y, sprite.getTextureRect().width, sprite.getTextureRect().height);
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
	rect = sf::IntRect(position.x, position.y, sprite.getTextureRect().width, sprite.getTextureRect().height);
}
