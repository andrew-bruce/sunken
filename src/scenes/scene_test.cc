#include "scene_test.hh"

#include <level_loader.hh>

#include "../components/cmp_shape.hh"
#include "../components/cmp_movement_player.hh"
#include "../components/cmp_combat_player.hh"
#include "../components/cmp_movement_enemy.hh"
#include "../components/cmp_combat_enemy.hh"

void SceneTest::load()
{
	level::load("res/levels/maze.txt");

	sf::Vector2f position(
		level::tile_position(
			level::find_tiles(level::Tile::Start).front())
		+ sf::Vector2f(level::tile_size(), level::tile_size()) / 2.0f);

	// Make player
	auto p = make_entity();
	p->move_to(position);
	p->add_tag("player");

	auto s = p->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(sf::Vector2f(20.0f, 10.0f));
	s->shape().setOrigin(sf::Vector2f(5.0f, 5.0f));
	s->shape().setFillColor(sf::Color::Green);

	auto m = p->add_component<CmpMovementPlayer>();
	auto c = p->add_component<CmpCombatPlayer>();
	// Make player

	// Spawn enemy //
	auto e = make_entity();
	e->move_to(position);

	auto es = e->add_component<CmpShape>();
	es->use_shape<sf::RectangleShape>(sf::Vector2f(20.0f, 10.0f));
	es->shape().setOrigin(sf::Vector2f(5.0f, 5.0f));
	es->shape().setFillColor(sf::Color::Blue);

	auto em = e->add_component<CmpMovementEnemy>();
	auto ec = e->add_component<CmpCombatEnemy>();


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
