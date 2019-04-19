#pragma once

#include <SFML/Graphics.hpp>

namespace renderer
{
	// Initialise renderer with window
	void initialise(sf::RenderWindow* window);

	// Window being used
	sf::RenderWindow* window();

	// Update renderer
	void update(const float& delta_time);

	// Queue drawable to be rendered
	void queue(const sf::Drawable* drawable);

	// Render queued drawables
	void render();

	// Shutdown renderer
	void shutdown();
};

