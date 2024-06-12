#include "Apple.hpp"

Apple::Apple()
{
	srand(time(NULL));
	position = sf::Vector2f(rand() % 800, rand() % 600);
	sprite.setPosition(position);
	sprite.setTexture(TextureManager::getTexture("apple"));
}

void Apple::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Apple::Update()
{
}
