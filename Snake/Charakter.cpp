#include "Charakter.hpp"

Charakter::Charakter()
{
	sprite.setTexture(TextureManager::getTexture("headLeft"));
	sprites.push_front(sprite);
}

Charakter::~Charakter()
{
}

void Charakter::Render(sf::RenderWindow& window)
{
	window.draw(sprites.front());
}

void Charakter::Update(sf::Time deltaTime)
{
	sprites.front().setPosition(sprites.front().getPosition().x + 1 * deltaTime.asSeconds(), sprites.front().getPosition().y);
}
