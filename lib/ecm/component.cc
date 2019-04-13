#include "component.hh"

// Class overrides
Component::Component(Entity* const p)
	:	for_deletion_(false),
		parent_(p)
{ }
Component::~Component() { }

// Deletion
bool Component::is_for_deletion() const
{
	return for_deletion_;
}
