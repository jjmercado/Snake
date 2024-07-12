#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("headLeft")));
	AddBodyPart();
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("tailRight")));

	snakeBodyParts.front().SetPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20));

	speed = 1.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);

	isLerping = false;
	counter = 0;

	maxValues = 3000;
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
	for (auto& bodyPart : snakeBodyParts)
	{
		bodyPart.Render(window);
	}
}

void Charakter::Update(sf::Time deltaTime)
{
	int counter = 0;

	for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
	{
		if(itr == snakeBodyParts.begin())
			itr = std::next(itr, 1);

		itr->Update(std::prev(itr)->GetPosition());
	}

	if (isLerping)
	{
		float lerpRate = 2.0f;

		// Berechnet die Zielposition auf dem Grid
		targetPosition = CalculateTargetPosition(deltaTime);

		// Interpoliert die Position des Charakters zur Zielposition
		sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
		sf::Vector2f newPosition = Lerp(currentPosition, targetPosition, lerpRate * deltaTime.asSeconds());
		snakeBodyParts.front().SetPosition(newPosition);

		// Setzt die neue Position

		// Überprüft, ob der Charakter nahe genug an der Zielposition ist
		if (std::abs(newPosition.x - targetPosition.x) < 0.1f && std::abs(newPosition.y - targetPosition.y) < 0.1f)
		{
			// Korrigiert die Position, um kleine Abweichungen zu vermeiden
			snakeBodyParts.front().SetPosition(targetPosition);
			
			isLerping = false; // Stoppt die Interpolation, wenn die Zielposition erreicht ist
		}
	}
	else
	{
		// Führt die kontinuierliche Bewegung nur aus, wenn der Charakter nicht interpoliert wird

		//Move(deltaTime);
		sf::Vector2f newPosition = snakeBodyParts.front().GetPosition() + (direction * speed * deltaTime.asSeconds());
		snakeBodyParts.front().SetPosition(newPosition);
	}

	rect = sf::IntRect(snakeBodyParts.front().GetPosition().x, snakeBodyParts.front().GetPosition().y, snakeBodyParts.front().GetRect().width, snakeBodyParts.front().GetRect().height);
	//MoveHead();
}

//void Charakter::MoveHead()
//{
//	if (direction.x > 0)
//	{
//		head.setTexture(TextureManager::getTexture("headRight"));
//	}
//	else if (direction.x < 0)
//	{
//		head.setTexture(TextureManager::getTexture("headLeft"));
//	}
//	else if (direction.y > 0)
//	{
//		head.setTexture(TextureManager::getTexture("headDown"));
//	}
//	else if (direction.y < 0)
//	{
//		head.setTexture(TextureManager::getTexture("headUp"));
//	}
//}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (this->rect.intersects(rect))
	{
		apple.SetPosition(sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40));
		AddBodyPart();
	}
}

void Charakter::AddBodyPart()
{
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal")));
}

sf::Vector2f Charakter::CalculateTargetPosition(sf::Time deltaTime)
{
	sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
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