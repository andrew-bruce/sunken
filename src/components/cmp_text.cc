#include "cmp_text.hh"

#include <resources.hh>
#include <renderer.hh>

// Class overrides
CmpText::CmpText(Entity* const p, const std::string& string)
: Component(p)
{
	text.setString(string);
	text.setFont(*resources::get<sf::Font>("FiraCode-Regular.ttf"));
}



// Logic
void CmpText::update(const float& delta_time)
{}

void CmpText::render()
{
	renderer::queue(&text);
}
