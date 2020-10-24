#include "TimerElement.hpp"

#include "../../Events.hpp"
#include "../../../Events.hpp"

TimerElement::TimerElement()
{
	Listen<UIRescaleEvent>();
	Listen<TimerEvent>();
	Listen<StateChangeEvent>();

	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	SetText("0:00");
}

void TimerElement::On(const lev::Event& event)
{
	if (event.Is<UIRescaleEvent>())
	{
		const auto& rescale_event = static_cast<const UIRescaleEvent&>(event);
		SetPosition({ rescale_event.view.getCenter().x, rescale_event.view.getCenter().y - rescale_event.view.getSize().y / 2 });
	}
	else if (event.Is<TimerEvent>())
	{
		const auto& timer = static_cast<const TimerEvent&>(event);
		sec += timer.dt / 1000;
		if (sec >= 60.f)
		{
			sec -= 60.f;
			++min;
		}

		if (sec < 10.f)
			SetText(std::to_string(min) + ":0" + std::to_string(static_cast<int>(sec)));
		else
			SetText(std::to_string(min) + ":" + std::to_string(static_cast<int>(sec)));
	}
	else if (event.Is<StateChangeEvent>())
	{
		const auto& state_change = static_cast<const StateChangeEvent&>(event);
		if (state_change.state == Program::State::IN_GAME)
		{
			min = 0;
			sec = 0.f;
			SetText("0:00");
		}
	}
}
