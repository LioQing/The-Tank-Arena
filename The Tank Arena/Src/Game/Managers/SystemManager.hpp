#pragma once

#include <map>
#include <typeinfo>
#include <memory>

#include "../../ProgramUtils.hpp"
#include "../Systems/System.hpp"

class System;

template <typename T>
concept IsSystem = std::is_base_of<System, T>::value;

class SystemManager
{
private:

	std::map<const type_info*, std::unique_ptr<System>> systems;

	ProgramInfo* program_info;
	lic::Manager* manager;
	float dt = 0.f;

public:

	void Init(ProgramInfo& program_info, lic::Manager& manager);
	void SetDeltaTime(float dt);

	template <IsSystem S, typename ...Ts>
	void Add(Ts... TArgs)
	{
		System* sys(new S(std::forward(TArgs)...));
		sys->program_info = program_info;
		sys->manager = manager;

		std::unique_ptr<System> u_ptr{ sys };
		systems.emplace(&typeid(S), std::move(u_ptr));
	}

	template <IsSystem S>
	S& Get()
	{
		auto it = systems.find(&typeid(S));
		assert_msg(it != systems.end(), "System manager: No system found");

		it->second->dt = dt;
		it->second->space_time_scale = dt * program_info->scale->Get();
		return static_cast<S&>(*it->second);
	}
};