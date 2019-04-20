#pragma once

#include <SFML/Graphics.hpp>

namespace renderer
{
	// Initialise renderer with window
	void initialise(sf::RenderWindow* window);

	// Set render target
	void target(sf::RenderTarget* target = nullptr);

	// Queue drawable to be rendered
	void queue(const sf::Drawable* drawable);

	// Render queued drawables to target
	void render();

	// Draw the screen
	void draw();

	// Shutdown renderer
	void shutdown();
};

