#include "OptionPanel.hpp"

sf::Sprite OptionPanel::sliderArrow;

OptionPanel::OptionPanel()
{
}

OptionPanel::OptionPanel(sf::RenderWindow& window, sf::Font& font) : button(font)
{
	button.SetSprite(TextureManager::GetTexture("greenPanel"));
	button.SetScale(sf::Vector2f(3.0f, 1.5f));
	button.SetPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	isActive = false;

	sliderHorizontalLine.setTexture(TextureManager::GetTexture("graySliderHorizontal"));
	sliderHorizontalLine.setOrigin(sf::Vector2f(sliderHorizontalLine.getLocalBounds().width / 2, sliderHorizontalLine.getLocalBounds().height / 2));
	sliderHorizontalLine.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 30));

	sliderArrow.setTexture(TextureManager::GetTexture("graySliderDown"));
	sliderArrow.setOrigin(sf::Vector2f(sliderArrow.getLocalBounds().width / 2, sliderArrow.getLocalBounds().height / 2));
	sliderArrow.setPosition(sf::Vector2f(window.getSize().x / 2 + 90, window.getSize().y / 2 + 10));

	sliderText.setFont(font);
	sliderText.setCharacterSize(30);
	sliderText.setFillColor(sf::Color::White);
	sliderText.setString("Volume");
	sliderText.setPosition(sf::Vector2f(window.getSize().x / 2 - 75, window.getSize().y / 2 - 60));
}

void OptionPanel::Render(sf::RenderWindow& window)
{
	button.Render(window);
	window.draw(sliderHorizontalLine);
	window.draw(sliderArrow);
	window.draw(sliderText);
}

void OptionPanel::HandleEvents(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
		sliderArrow.setPosition(sliderArrow.getPosition().x, sliderArrow.getPosition().y);
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (sf::Mouse::getPosition(window).x > sliderArrow.getPosition().x - sliderArrow.getGlobalBounds().width / 2 &&
                sf::Mouse::getPosition(window).x < sliderArrow.getPosition().x + sliderArrow.getGlobalBounds().width / 2 &&
                sf::Mouse::getPosition(window).y > sliderArrow.getPosition().y - sliderArrow.getGlobalBounds().height / 2 &&
                sf::Mouse::getPosition(window).y < sliderArrow.getPosition().y + sliderArrow.getGlobalBounds().height / 2)
            {
                isDragging = true; // Beginne das Ziehen
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            isDragging = false; // Beende das Ziehen
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (isDragging)
        {
            // Aktualisiere die Position des Slider-Pfeils basierend auf der Mausposition
            float newX = static_cast<float>(sf::Mouse::getPosition(window).x);
            float minX = sliderHorizontalLine.getPosition().x - sliderHorizontalLine.getGlobalBounds().width / 2;
            float maxX = sliderHorizontalLine.getPosition().x + sliderHorizontalLine.getGlobalBounds().width / 2;

            // Begrenze die Position des Slider-Pfeils innerhalb der Slider-Leiste
            if (newX < minX)
                newX = minX;
            if (newX > maxX)
                newX = maxX;

            sliderArrow.setPosition(newX, sliderArrow.getPosition().y);
			volumeSound.setGlobalVolume((newX - minX) / (maxX - minX) * 100);
        }
    }
}

void OptionPanel::Update(sf::RenderWindow& window)
{
	// überprüfen ob der Volume wert sich geäner hat und den slider entsprechend auf die neue Position setzen
}

void OptionPanel::SetActive(bool status)
{
	isActive = status;
}

bool OptionPanel::GetActive()
{
	return isActive;
}

bool OptionPanel::IsMouseOnPanel(sf::RenderWindow& window)
{
	return button.IsMouseOnButton(window);
}
