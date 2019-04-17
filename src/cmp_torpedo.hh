#pragma once

#include <ecm.hh>

struct CmpTorpedo : Component
{
private:
	float speed_;

public:
	// Class overrides
	CmpTorpedo() = delete;
	explicit CmpTorpedo(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

