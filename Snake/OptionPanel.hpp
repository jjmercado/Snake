#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextureManager.hpp"
#include <SFML/Audio/Listener.hpp>

class OptionPanel
{
	public:
		OptionPanel();
		OptionPanel(sf::RenderWindow& window, sf::Font& font);
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::Event& event, sf::RenderWindow& window);
		void SetActive(bool status);
		bool GetActive();
		bool IsMouseOnPanel(sf::RenderWindow& window);

	private:
		Button button;
		sf::Sprite sliderHorizontalLine;
		sf::Sprite sliderArrow;
		sf::Text sliderText;
		bool isActive;
		bool isDragging;
		sf::Listener volumeSound;
};

