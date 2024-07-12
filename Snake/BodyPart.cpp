#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture)
{
	bodyPart.setTexture(texture);
	delay = 0.5f;
	currentTime = 0.0f;
}

BodyPart::~BodyPart()
{
}

void BodyPart::SetPosition(const sf::Vector2f& position)
{
	bodyPart.setPosition(position);
}

sf::Vector2f BodyPart::GetPosition()
{
	return bodyPart.getPosition();
}

sf::IntRect BodyPart::GetRect()
{
	return bodyPart.getTextureRect();
}

void BodyPart::Render(sf::RenderWindow& window)
{
	window.draw(bodyPart);
}

void BodyPart::Update(const sf::Vector2f& prevPos)
{
	currentTime = clock.getElapsedTime().asSeconds();

	if(currentTime - lastUpdateTime > delay)
	{
		this->bodyPart.setPosition(prevPos);
		lastUpdateTime = currentTime;
	}
}