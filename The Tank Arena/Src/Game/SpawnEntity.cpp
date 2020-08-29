#include "SpawnEntity.hpp"

#include "Components.hpp"

namespace spawn
{
	namespace
	{
		template <typename T>
		concept is_component = std::is_base_of<lic::Component, T>::value;

		ProgramInfo* program_info;
		lic::Manager* man;

		template <is_component T, typename ...Ts>
		T& AddComponent_Info(lic::EntityID entity, Ts&&... TArgs)
		{
			return man->AddComponent<T>(entity, *program_info, TArgs...);
		}
		template <is_component T, typename ...Ts>
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

lic::Entity spawn::Player(
	const lio::Vec2f& pos,
	const lio::Vec2i& hull_size,
	float speed,
	float projectile_speed,
	float turret_interval,
	float projectile_bounce_count)
{
	lic::EntityID player = man->AddEntity();

	auto& sprite = AddComponent_Info<TankSpriteComponent>(player, "hull", "turret");

	auto& transform = AddComponent<TankTransformComponent>(player, hull_size, speed);
	transform.position = pos;

	auto& control = AddComponent<PlayerControlComponent>(player);

	auto& collider = AddComponent<TankColliderComponent>(player);

	auto& turret = AddComponent<TurretComponent>(player, projectile_speed, turret_interval, projectile_bounce_count);

	return lic::Entity(man, player);
}

lic::Entity spawn::Enemy(
	const lio::Vec2f& pos,
	const lio::Vec2i& hull_size)
{
	lic::EntityID enemy = man->AddEntity();

	auto& sprite = AddComponent_Info<TankSpriteComponent>(enemy, "ehull", "eturret");

	auto& transform = AddComponent<TankTransformComponent>(enemy, hull_size, 0.f);
	transform.position = pos;

	return lic::Entity(man, enemy);
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
