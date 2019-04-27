#pragma once

#include "cmp_text.hh"

struct CmpButton : CmpText
{
protected:
	bool active_;
	bool clicked_;

public:
	// Class overrides
	CmpButton() = delete;
	explicit CmpButton(Entity* const p, const std::string& string);
	~CmpButton() = default;

	// Logic
	void update(const float& delta_time) override;

	// Values
	bool is_active() const;
	bool clicked() const;
};
