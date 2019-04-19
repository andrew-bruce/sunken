#include "engine.hh"

#include <iostream>
#include <memory>
#include <numeric>

#include <resources.hh>
#include <renderer.hh>

namespace engine
{
	// Input information
	std::array<bool, sf::Keyboard::KeyCount> keyboard;
	std::array<bool, sf::Mouse::ButtonCount> mouse;
	sf::Vector2f                             mouse_position;

	// Engine information
	static std::string                       window_title_;
	static std::unique_ptr<sf::RenderWindow> window_       = nullptr;
	static Scene*                            active_scene_ = nullptr;

	// Loading information
	static bool  loading_         = false;
	static float loadimg_time_    = 0.0f;
	static float loading_spinner_ = 0.0f;



	// Loading scenes
	void loading_update(const float& delta_time)
	{
		if (active_scene_->is_loaded())
		{
			std::cout << "INFO exiting loading screen" << std::endl;
			loading_ = false;
		}
		else
		{
			loading_spinner_ += 220.0f * delta_time;
			loadimg_time_ += delta_time;
		}
	}

	void loading_render()
	{
		const float size = window_size().x / 16.0f;
		const sf::Color colour(255, 255, 255, std::min(255.0f, 40.0f * loadimg_time_));

		static sf::CircleShape octagon(size, 8);
		octagon.setOrigin(size, size);
		octagon.setRotation(loading_spinner_);
		octagon.setPosition(sf::cast<float>(window_size()) * 0.5f);
		octagon.setFillColor(colour);

		static sf::Text t("Loading", *resources::get<sf::Font>("FiraCode-Regular.ttf"));
		t.setFillColor(colour);
		t.setOrigin(t.getLocalBounds().width / 2.0f, t.getLocalBounds().height / 2.0f);
		t.setPosition(sf::cast<float>(window_size()) * sf::Vector2f(0.5f, 0.3f));

		renderer::queue(&t);
		renderer::queue(&octagon);
	}



	// Handle window events
	void event()
	{
		static sf::Event event;

		while (window_->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window_->close();

			else if (event.type     == sf::Event::KeyPressed
			     &&  event.key.code != sf::Keyboard::Unknown)
				keyboard[event.key.code] = true;

			else if (event.type     == sf::Event::KeyReleased
			     &&  event.key.code != sf::Keyboard::Unknown)
				keyboard[event.key.code] = false;

			else if (event.type == sf::Event::MouseButtonPressed)
				mouse[event.mouseButton.button] = true;

			else if (event.type == sf::Event::MouseButtonReleased)
				mouse[event.mouseButton.button] = false;

			else if (event.type == sf::Event::MouseMoved)
				mouse_position = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));

		if (keyboard[sf::Keyboard::Escape])
			window_->close();
	}



	// Update scene
	void update()
	{
		static sf::Clock clock;
		const float delta_time = clock.restart().asSeconds();

		// Update window title with current framerate
		{
			static std::array<float, 256> frame_times;
			static unsigned char ftc = 0;

			frame_times[++ftc] = delta_time;
			static std::string avg = window_title_ + " FPS:";
			if (ftc % 60 == 0)
			{
				double davg = std::accumulate(frame_times.begin(), frame_times.end(), 0.0);
				davg = 1.0 / (davg / 255.0);
				window_->setTitle(avg + to_decimal_place(2, davg));
			}
		}

		// Physics/framerate separation toggle comment
		{
			event();

			if (loading_)
				loading_update(delta_time);
			else
				active_scene_->update(delta_time);
		}
		/*/
		{
			static float accumulator = 0.0f;
			accumulator += delta_time;
			static const float physics_tick = 1.0f / 100.0f;

			while (accumulator >= physics_tick)
			{
				accumulator -= physics_tick;

				event();

				if (loading_)
					loading_update(physics_tick);
				else if (active_scene_ != nullptr)
					active_scene_->update(physics_tick);
			}

			if (accumulator > 0.0f)
			{
				event();

				if (loading_)
					loading_update(accumulator);
				else if (active_scene_ != nullptr)
					active_scene_->update(accumulator);
				accumulator = 0.0f;
			}
		}
		//*/
	}



	// Render scene
	void render()
	{
		if (loading_)
			loading_render();
		else
			active_scene_->render();
		renderer::render();
	}



	// Start engine
	void start(const std::string& title,
	           const unsigned&    width,
	           const unsigned&    height,
	                 Scene*       scene)
	{
		window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
		window_title_ = title;

		renderer::initialise(window_.get());
		change_scene(scene);

		// Main engine loop
		while (window_->isOpen())
		{
			update();
			render();
		}

		if (active_scene_ != nullptr)
		{
			active_scene_->unload();
			active_scene_ = nullptr;
		}

		window_->close();
		renderer::shutdown();
	}



	// Window information
	sf::RenderWindow* window()
	{
		return window_.get();
	}

	sf::Vector2ul window_size()
	{
		return sf::Vector2ul(window_->getSize());
	}

	void vsync(const bool& b)
	{
		window_->setVerticalSyncEnabled(b);
	}



	// Unload old scene and load new scene
	void change_scene(Scene* scene)
	{
		std::cout << "INFO engine changing scene" << std::endl;

		auto old = active_scene_;
		active_scene_ = scene;

		if (old != nullptr)
			old->unload();

		if (!scene->is_loaded())
		{
			std::cout << "INFO entering loading screen" << std::endl;
			loadimg_time_ = 0.0;
			active_scene_->load_async();
			loading_ = true;
		}
	}
}
