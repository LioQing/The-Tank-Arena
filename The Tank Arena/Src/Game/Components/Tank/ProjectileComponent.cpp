#include "ProjectileComponent.hpp"

ProjectileComponent::ProjectileComponent(float decay, const lio::Vec2f& start_pt)
	: decay(decay), start_pt(start_pt)
{
}
