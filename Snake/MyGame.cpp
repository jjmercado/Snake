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
            startMenuPanel.Render(window);
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
    }
}

void MyGame::handlePlayingEvents(sf::Event& event)
{
}

void MyGame::handleGameOver(sf::Event& event)
{
}
