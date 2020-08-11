#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"

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

	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player();
}