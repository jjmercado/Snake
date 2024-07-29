#include "Apple.hpp"
#include "Charakter.hpp"

Apple::Apple()
{
	srand(time(NULL));
	position = sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40);
	sprite.setPosition(position + sf::Vector2f(20,20));
	sprite.setTexture(TextureManager::getTexture("apple"));
	rect = sf::IntRect(position.x, position.y, sprite.getTextureRect().width, sprite.getTextureRect().height);
	animationSpeed = 0.1f;
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
}

void Apple::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	Animation();
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

void Apple::Animation()
{
	float delay = 0.6f;
	sf::Time time = clock.getElapsedTime();

	sprite.setScale(1.0f + animationSpeed, 1.0f + animationSpeed);

	if (time.asSeconds() > delay)
	{
		if(sprite.getScale().x < 1.5f)
		{
			animationSpeed += 0.1f;
		}
		else
		{
			animationSpeed -= 0.1f;
		}

		if (sprite.getScale().y < 1.5f)
		{
			animationSpeed += 0.1f;
		}
		else
		{
			animationSpeed -= 0.1f;
		}
		clock.restart();
	}
}
