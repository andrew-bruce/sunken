#include "scene_menu.hh"

#include <renderer.hh>
#include <engine.hh>

#include "../sunken.hh"
#include "../components/cmp_camera.hh"
#include "../components/cmp_text.hh"

static CmpCamera* camera;
static CmpText*   start;
static CmpText*   quit;

// Loading
void SceneMenu::load()
{
	auto c = make_entity();
	c->add_tag("camera");
	camera = c->add_component<CmpCamera>();

	auto s = make_entity();
	s->add_tag("start");
	s->move_to(sf::Vector2f(0.0f, -32.0f));
	start = s->add_component<CmpText>("Start");

	auto q = make_entity();
	q->add_tag("quit");
	q->move_to(sf::Vector2f(0.0f, 32.0f));
	quit = q->add_component<CmpText>("Quit");

	Scene::loaded(true);
}

void SceneMenu::unload()
{
	camera = nullptr;
	start = quit = nullptr;
	Scene::unload();
}



// Logic
void SceneMenu::update(const float& delta_time)
{
	if (camera != nullptr)
		camera->zoom = engine::window_size().x;

	if (start != nullptr && quit != nullptr)
		if (engine::mouse[sf::Mouse::Left])
		{
			if (start->bounds().contains(engine::mouse_position))
				return engine::change_scene(&scene_game);

			if (quit->bounds().contains(engine::mouse_position))
				return engine::window()->close();
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
