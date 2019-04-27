#include "scene_menu.hh"

#include <cmath>

#include <renderer.hh>
#include <engine.hh>

#include "../sunken.hh"
#include "../components/cmp_button.hh"
#include "../components/cmp_camera.hh"
#include "../components/cmp_music.hh"
#include "../components/cmp_shape.hh"
#include "../components/cmp_text.hh"

// Loading
void SceneMenu::load()
{
	// Camera
	{
		auto camera = make_entity();
		camera->add_tag("camera");
		camera->add_component<CmpCamera>();
	}

	// Start button
	{
		auto start = make_entity();
		start->add_tag("play");
		start->move_to(sf::Vector2f(0.0f, -64.0f));

		auto button = start->add_component<CmpButton>("Play");

		auto size = sf::Vector2f(button->text.getLocalBounds().width, button->text.getLocalBounds().height);

		button->text.setOrigin(size / 2.0f);
	}

	// Quit button
	{
		auto quit = make_entity();
		quit->add_tag("quit");
		quit->move_to(sf::Vector2f(0.0f, 64.0f));

		auto button = quit->add_component<CmpButton>("Quit");

		auto size = sf::Vector2f(button->text.getLocalBounds().width, button->text.getLocalBounds().height);

		button->text.setOrigin(size / 2.0f);
	}

	// Music
	{
		auto music = make_entity();
		music->add_tag("music");

		auto m = music->add_component<CmpMusic>("unseen-horrors.ogg");
		if (m->loaded())
			m->music()->play();
		else
			music->delete_please();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Scene::loaded(true);
}



// Logic
void SceneMenu::update(const float& delta_time)
{

	// Camera
	{
		auto camera = entities_.find("camera").front();
		if (camera != nullptr)
		{
			auto c = camera->compatible_components<CmpCamera>().front();
			if (c != nullptr)
			{
				const auto size = engine::window_size();
				if (size.x > size.y)
					c->zoom = size.x;
				else
					c->zoom = size.y;
			}
		}
	}

	// Start button
	{

		auto start = entities_.find("play").front();
		if (start != nullptr)
		{
			auto s = start->compatible_components<CmpButton>().front();
			if (s != nullptr && s->clicked())
				return engine::change_scene(&scene_game);
		}
	}

	// Quit button
	{

		auto quit = entities_.find("quit").front();
		if (quit != nullptr)
		{
			auto q = quit->compatible_components<CmpButton>().front();
			if (q != nullptr && q->clicked())
				return engine::window()->close();
		}
	}

	Scene::update(delta_time);
}

void SceneMenu::render()
{
	renderer::target(nullptr);

	entities_.render();

	renderer::render();
	renderer::draw();
}
