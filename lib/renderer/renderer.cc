#include "renderer.hh"

#include <iostream>
#include <queue>

namespace renderer
{
	// Backup window handle and render target
	static sf::RenderWindow* render_window;
	static sf::RenderTarget* render_target;

	// Target clear colour
	static sf::Color target_clear_colour;

	// Queue of drawables to be rendered
	static std::queue<const sf::Drawable*> render_queue;

	// Initialise renderer with window
	void initialise(sf::RenderWindow* window)
	{
		render_window = window;
		target(nullptr);
	}

	// Set render target
	void target(sf::RenderTarget* target)
	{
		render_target = target ? target : render_window;
		clear_colour(sf::Color::Black);
	}

	// Set the target clear colour
	void clear_colour(const sf::Color& colour)
	{
		target_clear_colour = colour;
	}

	// Queue drawable to be rendered
	void queue(const sf::Drawable* drawable)
	{
		render_queue.push(drawable);
	}

	// Render queued drawables
	void render()
	{
		if (!render_target)
		{
			std::cerr << "ERROR no render target" << std::endl;
			return;
		}

		render_target->clear(target_clear_colour);

		while (!render_queue.empty())
		{
			render_target->draw(*render_queue.front());
			render_queue.pop();
		}
	}

	// Draw the screen
	void draw()
	{
		render_window->display();
	}

	// Shutdown renderer
	void shutdown()
	{
		while (!render_queue.empty())
			render_queue.pop();
		render_target = render_window = nullptr;
	}
};

