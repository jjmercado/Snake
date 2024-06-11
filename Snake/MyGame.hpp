#pragma once
#include <iostream>
#include "Game.hpp"
#include "Menu.hpp"
#include "Play.hpp"
#include "IGameState.hpp"

class MyGame : public Game, public IGameState
{
	public:
		MyGame();
		~MyGame();
		void SetState(GameState state) override;

	protected:
		void ProcessEvents() override;
		void Update(sf::Time deltaTime) override;
		void Render() override;
		void handleGameOver(sf::Event& event);

	private:
		GameState gameState;
		Menu menu;
		Play play;
};

