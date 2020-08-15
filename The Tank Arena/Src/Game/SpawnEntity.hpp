#pragma once

#include <lic.hpp>

#include "../ProgramUtils.hpp"

namespace spawn
{
	void Init(ProgramInfo& program_info, lic::Manager& man);

	lic::Entity Player();
}