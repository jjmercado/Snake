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

void BodyPart::RenderCurveBodyParts(std::list<BodyPart>::iterator itr, std::list<BodyPart>::iterator listEnd)
{
	auto prev = std::prev(itr);
	auto next = std::next(itr);
	sf::Vector2f prevDir = prev->GetLastDirection();
	sf::Vector2f nextDir;

	if (next != listEnd)
		nextDir = next->GetLastDirection();
	else
		nextDir = sf::Vector2f(0, 0);

	if (prevDir.x < 0 && nextDir.y < 0) // hoch dann links
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomLeft"));
	}
	else if(prevDir.x > 0 && nextDir.y < 0) // hoch dann rechts
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomRight"));
	}
	else if(prevDir.x < 0 && nextDir.y > 0) // runter dann links
	{
		bodyPart.setTexture(TextureManager::GetTexture("topLeft"));
	}
	else if(prevDir.x > 0 && nextDir.y > 0) // runter dann rechts
	{
		bodyPart.setTexture(TextureManager::GetTexture("topRight"));
	}
	else if(prevDir.y < 0 && nextDir.x < 0) // links dann hoch
	{
		bodyPart.setTexture(TextureManager::GetTexture("topRight"));
	}
	else if(prevDir.y > 0 && nextDir.x < 0) // links dann runter
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomRight"));
	}
	else if(prevDir.y < 0 && nextDir.x > 0) // rechts dann hoch
	{
		bodyPart.setTexture(TextureManager::GetTexture("topLeft"));
	}
	else if(prevDir.y > 0 && nextDir.x > 0) // rechts dann runter
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomLeft"));
	}
}


