#pragma once

#include <lic.hpp>

#include "../../ProgramUtils.hpp"
#include "../Managers/SystemManager.hpp"

class System
{
private:

	friend class SystemManager;

protected:

	ProgramInfo* program_info;
	lic::Manager* manager;

public:

	virtual ~System() = default;
	virtual void Update() = 0;
};