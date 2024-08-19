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
		void Update(sf::RenderWindow& window);
		void SetActive(bool status);
		bool GetActive();
		bool IsMouseOnPanel(sf::RenderWindow& window);

	private:
		static sf::Sprite sliderArrow;
		Button button;
		sf::Sprite sliderHorizontalLine;
		sf::Text sliderText;
		bool isActive;
		bool isDragging;
		sf::Listener volumeSound;
};

