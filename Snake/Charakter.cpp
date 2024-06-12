#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	sprite.setTexture(TextureManager::getTexture("headLeft"));
	sprites.push_front(sprite);
	sprites.front().setPosition(window.getSize().x / 2 - sprite.getGlobalBounds().width / 2, window.getSize().y / 2 - sprite.getGlobalBounds().height / 2);
	speed = 20.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);
}

Charakter::~Charakter()
{
}

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Right)
		{
			direction = sf::Vector2f(1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			direction = sf::Vector2f(-1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			direction = sf::Vector2f(0.0f, 1.0f);
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			direction = sf::Vector2f(0.0f, -1.0f);
		}
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	window.draw(sprites.front());
}

void Charakter::Update(sf::Time deltaTime)
{
	Move(deltaTime);
}

void Charakter::Move(sf::Time deltaTime)
{
	if (direction.x > 0)
	{
		sprites.front().move(speed * deltaTime.asSeconds(), 0.0f);
		sprites.front().setTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		sprites.front().move(-speed * deltaTime.asSeconds(), 0.0f);
		sprites.front().setTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		sprites.front().move(0.0f, speed * deltaTime.asSeconds());
		sprites.front().setTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		sprites.front().move(0.0f, -speed * deltaTime.asSeconds());
		sprites.front().setTexture(TextureManager::getTexture("headUp"));
	}
}
