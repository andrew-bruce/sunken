#include "scene_test.hh"

#include <level_loader.hh>

#include "../components/cmp_shape.hh"
#include "../components/cmp_movement_player.hh"
#include "../components/cmp_combat_player.hh"

void SceneTest::load()
{
	level::load("res/levels/example.txt", 64.0f);

	{
		sf::Vector2f position =
			level::tile_position(level::find_tiles(
				level::Tile::Player).front())
			+ sf::Vector2f(level::tile_size(), level::tile_size())
			/ 2.0f;
		sf::Vector2f size = sf::Vector2f(level::tile_size(), level::tile_size()) / 8.0f;

		auto p = make_entity();
		p->move_to(position);

		auto s = p->add_component<CmpShape>();
		s->use_shape<sf::RectangleShape>(size);
		s->shape().setOrigin(size / 2.0f);
		s->shape().setFillColor(sf::Color::Yellow);

		p->add_component<CmpMovementPlayer>();
		p->add_component<CmpCombatPlayer>();
	}

	//	std::this_thread::sleep_for(std::chrono::milliseconds(4444));
	loaded(true);
}

void SceneTest::update(const float& delta_time)
{
	Scene::update(delta_time);
}

void SceneTest::render()
{
	level::render();
	Scene::render();
}
