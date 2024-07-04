#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	tail.setTexture(TextureManager::getTexture("tailRight"));

	headPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	tailPosition = headPosition + sf::Vector2f(40, 0);

	head.setPosition(headPosition);
	tail.setPosition(tailPosition);

	speed = 1.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);

	isLerping = false;
}

Charakter::~Charakter()
{
}

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		sf::Vector2f newDirection = direction;

		if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
		{
			newDirection = sf::Vector2f(1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
		{
			newDirection = sf::Vector2f(-1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			newDirection = sf::Vector2f(0.0f, 1.0f);
		}
		else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
		{
			newDirection = sf::Vector2f(0.0f, -1.0f);
		}

		if (directionChangeClock.getElapsedTime().asSeconds() > 0.085f) 
		{
			direction = newDirection;
			isLerping = true;
			directionChangeClock.restart();
		}
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	window.draw(head);
	window.draw(tail);

	if (!bodyParts.empty())
	{
		for (auto& part : bodyParts)
		{
			window.draw(part);
		}
	}
}

void Charakter::Update(sf::Time deltaTime)
{
	//sf::Vector2f offset = direction * 40.0f;

	positions.push_back(head.getPosition());

	if (isLerping)
	{
		float lerpRate = 2.0f;

		// Berechnet die Zielposition auf dem Grid
		targetPosition = CalculateTargetPosition(deltaTime);

		// Interpoliert die Position des Charakters zur Zielposition
		sf::Vector2f currentPosition = head.getPosition();
		sf::Vector2f newPosition = Lerp(currentPosition, targetPosition, lerpRate * deltaTime.asSeconds());
		head.setPosition(newPosition);

		DelaySetPosition();

		// Setzt die neue Position

		// Überprüft, ob der Charakter nahe genug an der Zielposition ist
		if (std::abs(newPosition.x - targetPosition.x) < 0.1f && std::abs(newPosition.y - targetPosition.y) < 0.1f)
		{
			// Korrigiert die Position, um kleine Abweichungen zu vermeiden
			head.setPosition(targetPosition);
			
			isLerping = false; // Stoppt die Interpolation, wenn die Zielposition erreicht ist
		}
	}
	else
	{
		// Führt die kontinuierliche Bewegung nur aus, wenn der Charakter nicht interpoliert wird
		sf::Vector2f newPosition = head.getPosition() + (direction * speed * deltaTime.asSeconds());
		head.setPosition(newPosition);

		DelaySetPosition();
	}

	rect = sf::IntRect(head.getPosition().x, head.getPosition().y, head.getGlobalBounds().width, head.getGlobalBounds().height);
	Move(deltaTime);

	MoveBodyParts(deltaTime);
}

void Charakter::Move(sf::Time deltaTime)
{
	if (direction.x > 0)
	{
		head.setTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		head.setTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		head.setTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		head.setTexture(TextureManager::getTexture("headUp"));
	}
}

void Charakter::MoveTail()
{
	if (direction.x > 0)
	{
		tail.setTexture(TextureManager::getTexture("tailLeft"));
	}
	else if (direction.x < 0)
	{
		tail.setTexture(TextureManager::getTexture("tailRight"));
	}
	else if (direction.y > 0)
	{
		tail.setTexture(TextureManager::getTexture("tailUp"));
	}
	else if (direction.y < 0)
	{
		tail.setTexture(TextureManager::getTexture("tailDown"));
	}
}

void Charakter::MoveBodyParts(sf::Time deltaTime)
{
	//sf::Vector2f offset = 40.0f * direction;

	//for (auto itr = std::next(sprites.begin()); itr != sprites.end(); ++itr)
	//{
	//	sf::Vector2f previousPosition = positions.front();
	//	sf::Vector2f newPosition = previousPosition - offset;

	//	itr->setPosition(newPosition);
	//}

	//if(sprites.size() < positions.size())
	//	positions.pop_front();
}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (this->rect.intersects(rect))
	{
		apple.SetPosition(sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40));
	}
}

void Charakter::AddBodyPart(sf::Texture& texture)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	bodyParts.push_back(sprite);
}

sf::Vector2f Charakter::CalculateTargetPosition(sf::Time deltaTime)
{
	sf::Vector2f currentPosition = head.getPosition();
	sf::Vector2f gridPosition = sf::Vector2f(
		std::round(currentPosition.x / 40.0f) * 40.0f,
		std::round(currentPosition.y / 40.0f) * 40.0f
	);

	return gridPosition + (direction * 40.0f * deltaTime.asSeconds()); // Angenommen, die Grid-Größe ist 40
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + (b - a) * t;
}

void Charakter::DelaySetPosition()
{
	if (positions.size() >= 2000)
	{
		tail.setPosition(positions.front());
		MoveTail();
		positions.pop_front();
	}
}