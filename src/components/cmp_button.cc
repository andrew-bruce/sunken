#include "cmp_button.hh"

#include <renderer.hh>
#include <engine.hh>

#include "cmp_text.hh"

// Clas overrides
CmpButton::CmpButton(Entity* const p)
: Component(p)
{}



// Logic
void CmpButton::update(const float& delta_time)
{
	const auto text = parent_->compatible_components<CmpText>().front();
	if (text == nullptr)
		return;

	const auto bounds = text->text.getGlobalBounds();

	active_ = bounds.contains(engine::mouse_position);
	clicked_ = active_ && engine::mouse[sf::Mouse::Left];

	if (active_)
		text->text.setFillColor(sf::Color(255, 255, 255, 255));
	else
		text->text.setFillColor(sf::Color(127, 127, 127, 255));
}

void CmpButton::render()
{}



// Values
bool CmpButton::is_active() const
{
	return active_;
}

bool CmpButton::clicked() const
{
	return clicked_;
}
