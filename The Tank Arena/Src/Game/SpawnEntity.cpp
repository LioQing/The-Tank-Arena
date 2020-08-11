#include "SpawnEntity.hpp"

#include "Components.hpp"

void spawn::Init(ProgramInfo& program_info, lic::Manager& man)
{
	spawn::program_info = &program_info;
	spawn::man = &man;
}

lic::Entity spawn::Player()
{
	lic::EntityID player = man->AddEntity();
	auto& sprite = AddComponent_Info<TankSpriteComponent>(player, "hull", "turret");
	auto& transform = AddComponent<TankTransformComponent>(player);
	transform.position = lio::Vec2f(400, 300);

	return lic::Entity(man, player);
}
