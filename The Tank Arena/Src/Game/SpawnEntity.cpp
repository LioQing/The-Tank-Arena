#include "SpawnEntity.hpp"

#include "Components.hpp"

namespace spawn
{
	namespace
	{
		template <typename T>
		concept IsComponent = std::is_base_of<lic::Component, T>::value;

		ProgramInfo* program_info;
		lic::Manager* man;

		template <IsComponent T, typename ...Ts>
		T& AddComponent_Info(lic::EntityID entity, Ts&&... TArgs)
		{
			return man->AddComponent<T>(entity, *program_info, TArgs...);
		}
		template <IsComponent T, typename ...Ts>
		T& AddComponent(lic::EntityID entity, Ts&&... TArgs)
		{
			return man->AddComponent<T>(entity, TArgs...);
		}
	}
}

void spawn::Init(ProgramInfo& program_info, lic::Manager& man)
{
	spawn::program_info = &program_info;
	spawn::man = &man;
}

lic::Entity spawn::Player()
{
	lic::EntityID player = man->AddEntity();

	auto& sprite = AddComponent_Info<TankSpriteComponent>(player, "hull", "turret");

	auto& transform = AddComponent<TankTransformComponent>(player, lio::Vec2i(20, 19), .15f); // size, speed
	transform.position = { 400, 300 };

	auto& control = AddComponent<PlayerControlComponent>(player);

	auto& collider = AddComponent<TankColliderComponent>(player);

	auto& turret = AddComponent<TurretComponent>(player, .2f, 200.f, 2); // speed, interval, bounce_count

	return lic::Entity(man, player);
}

lic::Entity spawn::Projectile(
	const lio::Vec2f& start_pos,
	const lio::Vec2f& pos, 
	const lio::Vec2f& init_vel, 
	float speed,
	float bounce_count)
{
	lic::EntityID projectile = man->AddEntity();

	auto& sprite = AddComponent_Info<ProjectileSpriteComponent>(projectile, "bullet");

	auto& transform = AddComponent<ProjectileTransformComponent>(projectile, speed, 2.f); // speed, radius
	transform.position = pos;
	transform.velocity = init_vel;

	auto& proj_comp = AddComponent<ProjectileComponent>(projectile, bounce_count, start_pos); // bounce_count, pos

	return lic::Entity(man, projectile);
}
