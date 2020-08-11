#include "SystemManager.hpp"

void SystemManager::Init(ProgramInfo& program_info, lic::Manager& manager)
{
	this->program_info = &program_info;
	this->manager = &manager;
}
