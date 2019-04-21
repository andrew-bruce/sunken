#pragma once

#include <ecm.hh>

struct CmpButton : Component
{
protected:
	bool active_;
	bool clicked_;

public:
	// Class overrides
	CmpButton() = delete;
	explicit CmpButton(Entity* const p);
	~CmpButton() = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Values
	bool is_active() const;
	bool clicked() const;
};
