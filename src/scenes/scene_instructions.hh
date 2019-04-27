#pragma once
#include <scene.hh>

struct SceneInstructions : Scene
{
	// Class overrides
	SceneInstructions() = default;
	~SceneInstructions() = default;

	void load() override;

	void update(const float& delta_time) override;
	void render() override;
};
#pragma once
