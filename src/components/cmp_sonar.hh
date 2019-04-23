#pragma once

#include <ecm.hh>

struct CmpSonar : Component
{
private:
	float         cooldown_;
	float         radius_;
	float         speed_;
	unsigned char strength_;

public:
	// Class overrides
	CmpSonar() = delete;
	explicit CmpSonar(Entity* const p);
	~CmpSonar() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
