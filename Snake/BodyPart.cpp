#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture, sf::Vector2f prev)
{
	collisionRect = sf::IntRect(0, 0, 40, 40);
	bodyPart.setPosition(prev);
	bodyPart.setTexture(texture);
	maxListValue = 8;
	direction = sf::Vector2f(-1, 0);
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

	if(directions.size() > 6)
	{
		directions.pop_front();
	}
}

void BodyPart::Update(const sf::Vector2f prev)
{
	positions.push_back(prev);

	if (positions.size() > maxListValue)
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

void BodyPart::RenderBodyParts()
{
	if (directions.front().x < 0 || directions.front().x > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("bodyHorizontal"));
	}
	else if (directions.front().y < 0 || directions.front().y > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("bodyVertical"));
	}
}


