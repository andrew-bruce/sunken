#include "cmp_button.hh"

#include <renderer.hh>
#include <engine.hh>

#include "cmp_text.hh"

// Clas overrides
CmpButton::CmpButton(Entity* const p, const std::string& string)
: CmpText (p, string),
  active_ (false),
  clicked_(false)
{}



// Logic
void CmpButton::update(const float& delta_time)
{
	CmpText::update(delta_time);

	const auto bounds = text.getGlobalBounds();

	active_ = bounds.contains(engine::mouse_position);
	clicked_ = active_ && engine::mouse[sf::Mouse::Left];

	if (active_)
		text.setFillColor(sf::Color(255, 255, 255, 255));
	else
		text.setFillColor(sf::Color(127, 127, 127, 255));
}



// Values
bool CmpButton::is_active() const
{
	return active_;
}

bool CmpButton::clicked() const
{
	return clicked_;
}
