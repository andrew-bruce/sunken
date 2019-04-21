#include "scene_menu.hh"

#include <renderer.hh>
#include <engine.hh>

#include "../sunken.hh"
#include "../components/cmp_button.hh"
#include "../components/cmp_camera.hh"
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
		start->add_tag("start");
		start->move_to(sf::Vector2f(0.0f, -64.0f));

		start->add_component<CmpButton>();
		auto text = start->add_component<CmpText>("Start");

		auto size = sf::Vector2f(text->text.getLocalBounds().width, text->text.getLocalBounds().height);

		text->text.setOrigin(size / 2.0f);
		text->text.setPosition(start->position());
	}

	// Quit button
	{
		auto quit = make_entity();
		quit->add_tag("quit");
		quit->move_to(sf::Vector2f(0.0f, 64.0f));

		quit->add_component<CmpButton>();
		auto text = quit->add_component<CmpText>("Quit");

		auto size = sf::Vector2f(text->text.getLocalBounds().width, text->text.getLocalBounds().height);

		text->text.setOrigin(size / 2.0f);
		text->text.setPosition(quit->position());
	}

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

		auto start = entities_.find("start").front();
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
