#include "ProjectileComponent.hpp"

ProjectileComponent::ProjectileComponent(uint32_t bounce_count, const lio::Vec2f& start_pt, TurretComponent& turret)
	: bounce_count(bounce_count), start_pt(start_pt), turret(turret)
{
}
