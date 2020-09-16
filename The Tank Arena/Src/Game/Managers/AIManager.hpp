#pragma once

#include <lic.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <functional>

#include "../AI/AIHandle.hpp"
#include "../AI/AIProcessData.hpp"
#include "../../ProgramUtils.hpp"

class AIManager
{
private:

	std::vector<std::pair<AIHandle, std::function<void(AIHandle&, const AIProcessData&)>>> ais;
	AIProcessData process_data;
	lic::EntityID player_id;

	std::thread process_thread;
	std::atomic_bool is_processing = false;

	const ProgramInfo* m_program_info;

	void AIThreadProcess();

public:

	void Init(const ProgramInfo& program_info, lic::EntityID player);
	void Spawn(const std::string& path, lic::Manager& manager, size_t tile_size);
	void ReadData(lic::Manager& manager);
	void StartProcess(lic::Manager& manager, const lic::Entity& arena_entity);
	void EndProcess();
};