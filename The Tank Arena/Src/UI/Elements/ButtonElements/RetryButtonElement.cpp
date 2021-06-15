#include "RetryButtonElement.hpp"

#include "../../../Events.hpp"
#include "../../../Program.hpp"

RetryButtonElement::RetryButtonElement(const Scale& xscale, uint32_t active_state)
    : ButtonElement(xscale, active_state)
{
}

void RetryButtonElement::OnRelease()
{
    lev::Emit<StateChangeEvent>(Program::State::IN_GAME);
}