#include "system_renderer.hh"

// STD
#include <iostream>
#include <queue>


namespace Renderer
{
	// Target rendered to
	static sf::RenderWindow* render_target;

	// Queue of drawables to be rendered
	static std::queue<const sf::Drawable*> render_queue;



	// Window being used
	sf::RenderWindow& window()
	{
		return *render_target;
	}



	// Initialise renderer with window
	void initialise(sf::RenderWindow& window)
	{
		render_target = &window;
	}



	// Update renderer
	void update(const float& delta_time) {}



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
			std::cerr <<
				"ERROR -> RENDERER -> RENDER -> NO TARGET"
				<< std::endl;
			return shutdown();
		}

		render_target->clear();

		while (!render_queue.empty())
		{
			render_target->draw(
				*render_queue.front());
			render_queue.pop();
		}

		render_target->display();
	}



	// Shutdown renderer
	void shutdown()
	{
		while (!render_queue.empty())
			render_queue.pop();
	}
};
