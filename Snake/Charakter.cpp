#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	AddBodyPart(TextureManager::getTexture("headLeft"));
	AddBodyPart(TextureManager::getTexture("bodyHorizontal"));
	AddBodyPart(TextureManager::getTexture("tailRight"));

	sprites.front().setPosition(window.getSize().x / 2, window.getSize().y / 2 - 20);

	auto itr = sprites.begin();
	std::advance(itr, 1);
	itr->setPosition(window.getSize().x / 2 + 40, window.getSize().y / 2 - 20);

	sprites.back().setPosition(window.getSize().x / 2 + 80, window.getSize().y / 2 - 20);

	speed = 160.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);
}

Charakter::~Charakter()
{
}

void Charakter::Events(sf::Event& event)
{

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
		{
			direction = sf::Vector2f(1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
		{
			direction = sf::Vector2f(-1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			direction = sf::Vector2f(0.0f, 1.0f);
		}
		else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
		{
			direction = sf::Vector2f(0.0f, -1.0f);
		}
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	for (auto& part : sprites)
	{
		window.draw(part);
	}
}

void Charakter::Update(sf::Time deltaTime)
{
	// Zielposition basierend auf der aktuellen Richtung und der Grid-Größe berechnen
	sf::Vector2f targetPosition = CalculateTargetPosition();

	// Interpolationsfaktor basierend auf der Geschwindigkeit und der Zeit aktualisieren
	float t = std::min(1.0f, speed * deltaTime.asSeconds() / 40); // Angenommen, die Grid-Größe ist 40

	// Neue Position mit linearer Interpolation berechnen
	sf::Vector2f newPosition = Lerp(sprites.front().getPosition(), targetPosition, t);

	// Setzt die neue Position des Charakters
	sprites.front().setPosition(newPosition);

	rect = sf::IntRect(sprites.front().getPosition().x, sprites.front().getPosition().y, sprites.front().getGlobalBounds().width, sprites.front().getGlobalBounds().height);
	Move(deltaTime);
	MoveBodyParts(deltaTime);
}

void Charakter::Move(sf::Time deltaTime)
{
	if (direction.x > 0)
	{
		sprites.front().setTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		sprites.front().setTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		sprites.front().setTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		sprites.front().setTexture(TextureManager::getTexture("headUp"));
	}
}

// Klappt nicht so ganz
void Charakter::MoveBodyParts(sf::Time deltaTime)
{
	sf::Vector2f lastPosition = sprites.front().getPosition();
	sf::Vector2f lastDirection = direction;

	for (auto& part : sprites)
	{
		sf::Vector2f tempPosition = part.getPosition();
		part.setPosition(lastPosition);
		lastPosition = tempPosition;
	}
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
	sprites.push_back(sprite);
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + t * (b - a);
}

sf::Vector2f Charakter::CalculateTargetPosition()
{
	sf::Vector2f currentPosition = sprites.front().getPosition();
	sf::Vector2f gridPosition = sf::Vector2f(
		std::round(currentPosition.x / 40.0f) * 40.0f,
		std::round(currentPosition.y / 40.0f) * 40.0f
	);

	return gridPosition + (direction * 40.0f); // Angenommen, die Grid-Größe ist 40
}
