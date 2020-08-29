#pragma once

#include <lic.hpp>
#include <thread>
#include <atomic>

#include "../../ProgramUtils.hpp"

class AIManager
{
private:

	// list of ai

	std::thread process_thread;
	std::atomic_bool is_processing = false;

	const ProgramInfo* m_program_info;

	void AIThreadProcess();

public:

	void Init(const ProgramInfo& program_info);
	void ReadData(lic::Manager& manager);
	void StartProcess();
	void EndProcess();

	// read game data

	// process thread
};