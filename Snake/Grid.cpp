#include "Grid.hpp"

Grid::Grid()
{
}

void Grid::Render(sf::RenderWindow& window)
{
	// Draw the grid
	for (int i = 0; i < window.getSize().x; i += 40)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i, 0)),
			sf::Vertex(sf::Vector2f(i, window.getSize().y))
		};
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(0, i)),
			sf::Vertex(sf::Vector2f(window.getSize().x, i))
		};
		window.draw(line, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
	}
}
