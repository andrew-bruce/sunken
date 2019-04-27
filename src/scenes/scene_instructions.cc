#include "scene_instructions.hh"

#include <cmath>

#include <renderer.hh>
#include <engine.hh>
#include <resources.hh>

#include "../sunken.hh"
#include "../components/cmp_button.hh"
#include "../components/cmp_camera.hh"
#include "../components/cmp_music.hh"
#include "../components/cmp_shape.hh"
#include "../components/cmp_text.hh"
#include "../components/cmp_sprite.hh"

// Loading
void SceneInstructions::load()
{
	// Camera
	{
		auto camera = make_entity();
		camera->add_tag("camera");
		camera->add_component<CmpCamera>();
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

	// Controls
	{
		auto c = make_entity();
		c->add_tag("controls");
		auto tex = resources::get<sf::Texture>("controls.png");


		if (!tex)
			throw std::runtime_error("Cannot find texture 'res/textures/controls.png'");

		auto s = c->add_component<CmpSprite>();
		s->use_sprite<sf::Sprite>();
		s->sprite().setTexture(*tex);

		const auto sprite_size = sf::Vector2f(s->sprite().getLocalBounds().width, s->sprite().getLocalBounds().height);
		c->move_to(-sprite_size / 2.f);
	}


	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Scene::loaded(true);
}



// Logic
void SceneInstructions::update(const float& delta_time)
{
	if (engine::keyboard[sf::Keyboard::Escape])
		return engine::change_scene(&scene_menu);

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

	Scene::update(delta_time);
}

void SceneInstructions::render()
{
	renderer::target(nullptr);

	entities_.render();

	renderer::render();
	renderer::draw();
}
