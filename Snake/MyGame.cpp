#include "MyGame.hpp"

MyGame::MyGame() : startMenuPanel(window, font), gameState(MyGame::StartMenu)
{
    //startMenupanel = Panel(window);
    //gameState = GameState::StartMenu;
}

void MyGame::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        switch (gameState)
        {
            case MyGame::StartMenu:
            {
                handleStartMenuEvents(event);
                break;
            }
            case MyGame::Playing:
            {
                handlePlayingEvents(event);
                break;
            }
            case MyGame::GameOver:
            {

                break;
            }
            default:
                std::cerr << "Invalid game state in Events" << std::endl;
                break;
        }
    }
}

void MyGame::Update(sf::Time deltaTime)
{
    switch (gameState)
    {
        case MyGame::StartMenu:
        {
            break;
        }
        case MyGame::Playing:
        {
            break;
        }
        case MyGame::GameOver:
        {

            break;
        }
        default:
            std::cerr << "Invalid game state in Update" << std::endl;
            break;
    }
}

void MyGame::Render()
{
    window.clear();

    switch (gameState)
    {
        case MyGame::StartMenu:
        {
            handleStartMenuDrawings(window);
            break;
        }
        case MyGame::Playing:
        {
            break;
        }
        case MyGame::GameOver:
        {
            break;
        }
        default:
            std::cerr << "Invalid game state in Render" << std::endl;
            break;
    }

    window.display();
}

void MyGame::handleStartMenuEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if(startMenuPanel.GetButton("Start").IsMouseOnButton(window))
		{
			gameState = MyGame::Playing;
		}
        else if (startMenuPanel.GetButton("Options").IsMouseOnButton(window))
		{
			// TODO: Implement options menu
		}
		else if (startMenuPanel.GetButton("Exit").IsMouseOnButton(window))
		{
			window.close();
		}
    }
}

void MyGame::handleStartMenuDrawings(sf::RenderWindow& window)
{
    if (startMenuPanel.GetButton("Start").IsMouseOnButton(window))
    {
        startMenuPanel.GetButton("Start").SetSprite(TextureManager::getTexture("blueButton13"));
        startMenuPanel.GetButton("Start").SetTextFillColor(sf::Color::Black);
    }
    else if (startMenuPanel.GetButton("Options").IsMouseOnButton(window))
    {
        startMenuPanel.GetButton("Options").SetSprite(TextureManager::getTexture("yellowButton"));
    }
    else if (startMenuPanel.GetButton("Exit").IsMouseOnButton(window))
    {
        startMenuPanel.GetButton("Exit").SetSprite(TextureManager::getTexture("yellowButton"));
    }
    else
	{
        startMenuPanel.GetButton("Start").SetTextFillColor(sf::Color::White);
		startMenuPanel.GetButton("Start").SetSprite(TextureManager::getTexture("yellowButton"));
		startMenuPanel.GetButton("Options").SetSprite(TextureManager::getTexture("blueButton"));
		startMenuPanel.GetButton("Exit").SetSprite(TextureManager::getTexture("blueButton"));
	}
    // viel zu übel ich darf nicht ständig die texturen neu laden und setzen 
    startMenuPanel.Render(window);
}

void MyGame::handlePlayingEvents(sf::Event& event)
{
}

void MyGame::handleGameOver(sf::Event& event)
{
}
