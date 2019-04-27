#pragma once

#include "cmp_sound.hh"

struct CmpSoundTemp : CmpSound
{
	// Class overrides
	CmpSoundTemp() = delete;
	explicit CmpSoundTemp(Entity* const p, const std::string& string = "");
	~CmpSoundTemp() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
