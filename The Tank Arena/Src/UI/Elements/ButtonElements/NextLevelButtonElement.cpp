#include "NextLevelButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

NextLevelButtonElement::NextLevelButtonElement(const Scale& xscale, uint32_t active_state)
    : ButtonElement(xscale, active_state)
{
}

void NextLevelButtonElement::OnRelease()
{
    if (*program_info->current_level < 9) //level
    {
        lev::Emit<LevelChangeEvent>(*program_info->current_level + 1);
        lev::Emit<StateChangeEvent>(Program::State::IN_GAME);
    }
}