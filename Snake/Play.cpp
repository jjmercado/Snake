#include "Play.hpp"

Play::Play(sf::RenderWindow& window, sf::Font& font) : charakter(window)
{
	background.setTexture(TextureManager::GetTexture("playingBackground"));
}

void Play::HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			gameState.SetState(IGameState::StartMenu);
		}
	}
	charakter.Events(event);
}

void Play::HandleDrawings(sf::RenderWindow& window)
{
	window.draw(background);
	charakter.Render(window);
	apple.Render(window);
}

void Play::HandleUpdate(sf::Time deltaTime, IGameState& gameState)
{
	charakter.Update(deltaTime, gameState);
	charakter.Collision(apple.GetRect(), apple);
}

Charakter& Play::GetCharakter()
{
	return charakter;
}

Apple& Play::GetApple()
{
	return apple;
}
