#pragma once

#include <lic.hpp>

class ArenaManager
{
private:

	lic::Entity m_arena_entity;

public:

	void SetArena(lic::Entity entity);

	void LoadMap(const std::string& path);
};