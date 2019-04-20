#include "cmp_text.hh"

#include <resources.hh>
#include <renderer.hh>

// Class overrides
CmpText::CmpText(Entity* const p, const std::string& string)
: Component(p),
  string_(string)
{
	text_.setString(string);
	text_.setFont(*resources::get<sf::Font>("FiraCode-Regular.ttf"));
}



// Logic
void CmpText::update(const float& delta_time)
{}

void CmpText::render()
{
	text_.setOrigin(text_.getLocalBounds().width / 2.0f, text_.getLocalBounds().height / 2.0f);
	text_.setPosition(parent_->position());
	renderer::queue(&text_);
}



// Text
void CmpText::text(const std::string& string)
{
	string_ = string;
	text_.setString(string);
}
