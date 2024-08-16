#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IGameState.hpp"
#include "Panel.hpp"

class MenuPanel : public Panel
{
	public:
		MenuPanel();
		MenuPanel(sf::RenderWindow& window, sf::Font& font);
		~MenuPanel();
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);

	private:
		sf::Sprite background;
};

