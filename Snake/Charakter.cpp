#include "Charakter.hpp"

Charakter::Charakter()
{
}

Charakter::Charakter(sf::RenderWindow& window)
{
	if(!moveBuffer.loadFromFile("move.wav"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	move.setBuffer(moveBuffer);

	if(!gameOverBuffer.loadFromFile("game-over.mp3"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	gameOver.setBuffer(gameOverBuffer);

	if(!eatBuffer.loadFromFile("eat.mp3"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	eat.setBuffer(eatBuffer);

	srand(time(NULL));
	isBodyCollisionActive = false;
	hasCollided = false;
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	direction = sf::Vector2f(-1.0f, 0.0f);
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("headLeft"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("tailRight"), startPosition));

	snakeBodyParts.front().SetPosition(startPosition);

	speed = 250.0f;

	isLerping = false;
	counter = 0;
}

Charakter::~Charakter()
{
}

// eventuell ein struct definieren für die richtungen

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && !hasCollided)
	{
		sf::Vector2f newDirection = direction;

		if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && newDirection != sf::Vector2f(-1.0f, 0.0f))
		{
			newDirection = sf::Vector2f(1.0f, 0.0f);
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && newDirection != sf::Vector2f(1.0f, 0.0f))
		{
			newDirection = sf::Vector2f(-1.0f, 0.0f);
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && newDirection != sf::Vector2f(0.0f, -1.0f))
		{
			newDirection = sf::Vector2f(0.0f, 1.0f);
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && newDirection != sf::Vector2f(0.0f, 1.0f))
		{
			newDirection = sf::Vector2f(0.0f, -1.0f);
			move.play();
		}

		if(event.key.code == sf::Keyboard::Space)
		{
			for(int i = 0; i < 10; i++)
				AddBodyPart();
		}

		if (directionChangeClock.getElapsedTime().asSeconds() > 0.120f && newDirection != direction) 
		{
			direction = newDirection;
			isLerping = true;
			directionChangeClock.restart();
		}
		isBodyCollisionActive = true; // collision nach dem ersten input aktivieren
	}
}

void Charakter::Render(sf::RenderWindow& window)
{

	for (auto& bodyPart : snakeBodyParts)
	{
		bodyPart.Render(window);
		bodyPart.SetDirection(direction);
	}

	if (!hasCollided)
	{
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
			{
				itr = std::next(itr, 1);
			}

			lastDirection = std::prev(itr)->GetLastDirection();
			itr->SetDirection(lastDirection);

			if (lastDirection.x < 0 || lastDirection.x > 0)
			{
				itr->SetTexture(TextureManager::getTexture("bodyHorizontal")); // performance issue
			}
			else if (lastDirection.y < 0 || lastDirection.y > 0)
			{
				itr->SetTexture(TextureManager::getTexture("bodyVertical"));
			}
			//itr->RotateBodyPart();

			ChangeTailTexture();
		}
	}

	ChangeHeadTexture();
}

void Charakter::Update(sf::Time deltaTime, IGameState& gameState)
{
	if (hasCollided)
	{
		speed = 0.0f;
		gameState.SetState(IGameState::GameIsOver);
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
				itr = std::next(itr, 1);

			itr->SetPosition(itr->GetPosition());
		}
	}
	else
	{
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
			{
				itr = std::next(itr, 1);
			}

			itr->Update(std::prev(itr)->GetPosition());
			lastPosition = itr->GetLastPosition();
			itr->SetPosition(lastPosition);
		}
	}

	if (isLerping)
	{
		float lerpRate = 60.0f;

		// Berechnet die Zielposition auf dem Grid
		targetPosition = CalculateTargetPosition(deltaTime);

		// Interpoliert die Position des Charakters zur Zielposition
		sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
		sf::Vector2f newPosition = Lerp(currentPosition, targetPosition, lerpRate * deltaTime.asSeconds());
		snakeBodyParts.front().SetPosition(newPosition);

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
		sf::Vector2f velocity = direction * speed * deltaTime.asSeconds();
		sf::Vector2f newPosition = snakeBodyParts.front().GetPosition() + velocity;
		snakeBodyParts.front().SetPosition(newPosition);
	}

	for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
	{
		if (itr == snakeBodyParts.begin())
			itr = std::next(itr, 1);

		sf::IntRect col = sf::IntRect(itr->GetPosition().x, itr->GetPosition().y, itr->GetCollisionRect().width, itr->GetCollisionRect().height);

		BodyPartCollision(col, gameState);
	}

	if (direction.x > 0) // rechts
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 45, snakeBodyParts.front().GetPosition().y + 17.5, 5, 5);
	}
	else if (direction.x < 0) // links
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x - 5, snakeBodyParts.front().GetPosition().y + 20, 5, 5);
	}
	else if (direction.y > 0) // runter
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 17.5, snakeBodyParts.front().GetPosition().y + 45, 5, 5);
	}
	else if (direction.y < 0) // hoch
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 20, snakeBodyParts.front().GetPosition().y - 5, 5, 5);
	}

	CheckBoundaries();
}

void Charakter::ChangeHeadTexture()
{
	if (direction.x > 0)
	{
		//snakeBodyParts.front().bodyPart.setScale(-1, 1);
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		//snakeBodyParts.front().bodyPart.setScale(1, 1);
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		//snakeBodyParts.front().bodyPart.setScale(1, -1);
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		//snakeBodyParts.front().bodyPart.setScale(1, 1);
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headUp"));
	}
}

void Charakter::ChangeTailTexture()
{
	if (lastDirection.x > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailLeft"));
	}
	else if (lastDirection.x < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailRight"));
	}
	else if (lastDirection.y > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailUp"));
	}
	else if (lastDirection.y < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailDown"));
	}
}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (snakeHeadRect.intersects(rect))
	{
		eat.play();
		rndApplePos = sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40);

		for(auto position : snakeBodyParts)
		{
			if(position.GetPosition() == rndApplePos)
			{
				rndApplePos = sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40);
			}
		}
		apple.SetPosition(rndApplePos + sf::Vector2f(20,20));
		AddBodyPart();
	}
}

void Charakter::AddBodyPart()
{
	auto back = snakeBodyParts.back();
	sf::Vector2f positionOffsetX = sf::Vector2f(25, 0); // nötig um die Lücke zu schließen wenn ein BodyPart hinzugefügt wird
	sf::Vector2f positionOffsetY = sf::Vector2f(0, 25);

	if (lastDirection.x > 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal"), back.GetPosition() + positionOffsetX));
	}
	else if (lastDirection.x < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal"), back.GetPosition() - positionOffsetX));
	}
	else if (lastDirection.y > 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyVertical"), back.GetPosition() + positionOffsetY));
	}
	else if(lastDirection.y < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyVertical"), back.GetPosition() - positionOffsetY));
	}
}

void Charakter::Reset(sf::RenderWindow& window, Apple& apple)
{
	gameOver.stop();
	snakeBodyParts.clear();
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("headLeft"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("tailRight"), startPosition));

	snakeBodyParts.front().SetPosition(startPosition);

	isBodyCollisionActive = false;
	hasCollided = false;

	rndApplePos = sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40);
	apple.SetPosition(rndApplePos + sf::Vector2f(20,20));

	speed = 250.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);

	isLerping = false;
	counter = 0;
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

void Charakter::BodyPartCollision(const sf::IntRect& bodyPartRect, IGameState& gameState)
{
	if (snakeHeadRect.intersects(bodyPartRect) && isBodyCollisionActive)
	{
		gameState.SetState(IGameState::GameIsOver);
		gameOver.play();
		hasCollided = true;
	}
}

void Charakter::CheckBoundaries()
{
	if (snakeBodyParts.front().GetPosition().x < 0 || snakeBodyParts.front().GetPosition().x > 800 - 40)
	{
		gameOver.play();
		hasCollided = true;
	}
	else if (snakeBodyParts.front().GetPosition().y < 0 || snakeBodyParts.front().GetPosition().y > 600 - 40)
	{
		gameOver.play();
		hasCollided = true;
	}
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + (b - a) * t;
}