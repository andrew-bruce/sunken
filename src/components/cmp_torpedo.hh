#pragma once

#include <ecm.hh>
#include "cmp_movement.hh"
#include <maths.hh>
#include <engine.hh>

struct CmpTorpedo : CmpMovement
{
public:
	// Class overrides
	CmpTorpedo() = delete;
	explicit CmpTorpedo(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

