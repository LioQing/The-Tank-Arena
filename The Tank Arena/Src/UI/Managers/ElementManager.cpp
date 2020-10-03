#include "ElementManager.hpp"

void ElementManager::Init(ProgramInfo& program_info, InputManager& input_man)
{
	this->program_info = &program_info;
	this->input_man = &input_man;
}
