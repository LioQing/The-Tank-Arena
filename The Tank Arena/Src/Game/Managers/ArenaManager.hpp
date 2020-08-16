#pragma once

#include <lic.hpp>

#include "../../ProgramUtils.hpp"

class ArenaManager
{
private:

	lic::Entity m_arena_entity;
	ProgramInfo* program_info;

public:

	void Init(ProgramInfo& program_info);
	lic::Entity& SetArena(lic::Entity entity);

	void LoadMap(const std::string& path);

	const lic::Entity& GetEntity() const;
};