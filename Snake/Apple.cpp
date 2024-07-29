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
    const float delay = 0.6f;
    const float maxScale = 1.5f;
    const float minScale = 1.0f;
    sf::Time time = clock.getElapsedTime();

    if (time.asSeconds() > delay)
    {
        float currentScale = sprite.getScale().x; // Da x und y gleich sind, reicht es, eine zu überprüfen

        if (currentScale <= maxScale)
        {
            sprite.setScale(currentScale + animationSpeed, currentScale + animationSpeed);
        }        
		else
		{
			sprite.setScale(minScale, minScale);
		}
        clock.restart();
    }
}
