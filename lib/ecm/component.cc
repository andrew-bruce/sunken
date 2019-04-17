#include "component.hh"

// Class overrides
Component::Component(Entity* const p)
: parent_(p), for_deletion_(false)
  
{ }
Component::~Component() { }

// Deletion
bool Component::is_for_deletion() const
{
	return for_deletion_;
}
