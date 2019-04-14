#pragma once

#include <scene.hh>

struct SceneTest : Scene
{
	// Class overrides
	SceneTest() = default;
	~SceneTest() = default;

	void load() override;

	void update(const float& delta_time) override;
	void render() override;
};
