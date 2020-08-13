#pragma once

#include <lic.hpp>

#include "../../ProgramUtils.hpp"

class ArenaManager
{
private:

	lic::Entity m_arena_entity;

public:

	void SetArena(lic::Entity entity);

	void LoadMap(ProgramInfo& program_info, const std::string& path);
};