#include "cmp_pickup.hh"
#include "cmp_shape.hh"

CmpPickup::CmpPickup(Entity * p) : Component(p)
{
}

void CmpPickup::pickup()
{
	parent_->delete_please();
}
