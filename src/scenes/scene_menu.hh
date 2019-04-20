#pragma once

#include <scene.hh>

struct SceneMenu : Scene
{
	// Class overrides
	SceneMenu() = default;
	~SceneMenu() = default;

	void load() override;
	void unload() override;

	void update(const float& delta_time) override;
	void render() override;
};
