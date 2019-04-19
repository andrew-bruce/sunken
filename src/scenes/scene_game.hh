#pragma once

#include <scene.hh>

struct SceneGame : Scene
{
	// Class overrides
	SceneGame() = default;
	~SceneGame() = default;

	void load() override;

	void update(const float& delta_time) override;
	void render() override;
};
