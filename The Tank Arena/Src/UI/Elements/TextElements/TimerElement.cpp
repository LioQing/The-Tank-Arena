#include "TimerElement.hpp"

#include "../../Events.hpp"
#include "../../../Events.hpp"

TimerElement::TimerElement()
{
	Listen<UIRescaleEvent>();
	Listen<TimerEvent>();
	Listen<StateChangeEvent>();
}

void TimerElement::On(const lev::Event& event)
{
	if (event.Is<UIRescaleEvent>() && is_in_game)
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

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
	}
	else if (event.Is<StateChangeEvent>())
	{
		const auto& state_change = static_cast<const StateChangeEvent&>(event);
		if (state_change.state == Program::State::IN_GAME)
		{
			is_in_game = true;

			text.setOutlineColor(sf::Color::Black);
			text.setOutlineThickness(2);
			SetSize(24);

			min = 0;
			sec = 0.f;
			SetText("0:00");

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
			SetPosition({ ui_view->getCenter().x, ui_view->getCenter().y - ui_view->getSize().y / 2 });
		}
		else if (state_change.state == Program::State::ENDGAME_MENU)
		{
			is_in_game = false;

			text.setOutlineThickness(0);
			SetSize(28);

			SetText("Time: " + GetText().getString());

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(0, 0);
			SetPosition({ ui_view->getCenter().x - 150, ui_view->getCenter().y - 36 });
		}
	}
}
