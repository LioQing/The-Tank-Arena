#include "AIManager.hpp"

void AIManager::Init(const ProgramInfo& program_info)
{
	m_program_info = &program_info;
	is_processing = false;
}

void AIManager::AIThreadProcess()
{
	while (is_processing)
	{
		std::cout << "Hi from AI thread" << std::endl;
	}
}

void AIManager::ReadData(lic::Manager& manager)
{
}

void AIManager::StartProcess()
{
	process_thread = std::thread(&AIManager::AIThreadProcess, this);
	is_processing = true;
}

void AIManager::EndProcess()
{
	is_processing = false;
	process_thread.join();
}
