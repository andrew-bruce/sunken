#pragma once

#include <SFML/Graphics.hpp>

namespace renderer
{
	// Initialise renderer with window
	void initialise(sf::RenderWindow&);

	// Window being used
	sf::RenderWindow& window();

	// Update renderer
	void update(const float&);

	// Queue drawable to be rendered
	void queue(const sf::Drawable*);

	// Render queued drawables
	void render();

	// Shutdown renderer
	void shutdown();
};
