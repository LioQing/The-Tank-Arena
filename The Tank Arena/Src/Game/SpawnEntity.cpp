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
	auto& sprite = AddComponent<TankSpriteComponent>(player, "hull", "turret");

	return lic::Entity(man, player);
}
