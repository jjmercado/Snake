#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture, sf::Vector2f prev)
{
	collisionRect = sf::IntRect(0, 0, 40, 40);
	bodyPart.setPosition(prev);
	bodyPart.setTexture(texture);
	dynamicCounter = 1700;

	for(int i = 0; i < 20; i++)
	{
		positions.push_back(prev);
	}
}

BodyPart::~BodyPart()
{
}

void BodyPart::SetDirection(const sf::Vector2f& direction)
{
	this->direction = direction;
}

sf::Vector2f BodyPart::GetDirection()
{
	return direction;
}

void BodyPart::SetPosition(const sf::Vector2f& position)
{
	bodyPart.setPosition(position);
}

sf::Vector2f BodyPart::GetPosition()
{
	return bodyPart.getPosition();
}

sf::IntRect BodyPart::GetBodyRect()
{
	return bodyPart.getTextureRect();
}

sf::IntRect BodyPart::GetCollisionRect()
{
	return collisionRect;
}

void BodyPart::SetTexture(sf::Texture& texture)
{
	bodyPart.setTexture(texture);
}

void BodyPart::Render(sf::RenderWindow& window)
{
	window.draw(bodyPart);

	directions.push_back(direction);

	if(directions.size() > dynamicCounter)
	{
		directions.pop_front();
	}
}

void BodyPart::Update(const sf::Vector2f prev)
{
	positions.push_back(prev);

	if (positions.size() > 2000)
	{
		positions.pop_front();
	}
}

sf::Vector2f& BodyPart::GetLastPosition()
{
	return positions.front();
}

sf::Vector2f& BodyPart::GetLastDirection()
{
	return directions.front();
}

void BodyPart::RotateBodyPart()
{
	bodyPart.setOrigin(20, 20);
	if (direction.x < 0 || direction.x > 0)
	{
		bodyPart.setRotation(0);
	}
	else if (direction.y < 0 || direction.y > 0)
	{
		bodyPart.setRotation(90);
	}
	bodyPart.setOrigin(0, 0);
}
