#include "UI.hpp"

#include "Events.hpp"
#include "../Events.hpp"

void UI::Init(ProgramInfo program_info, uint32_t* program_state)
{
	// listen events
	Listen<WindowResizedEvent>();
	Listen<UISettingEvent>();

	// store program var
	m_program_state = program_state;
	m_program_info = program_info;
	m_program_info.scale = &m_scale;
	m_scale = 4.f;
	m_view = m_program_info.window->getView();

	// load textures
	m_program_info.texture_manager->LoadTexture("cursor_color", R"(Data\Cursor\default-color.png)");
	m_program_info.texture_manager->LoadTexture("cursor_outline", R"(Data\Cursor\default-outline.png)");
	m_program_info.texture_manager->LoadTexture("title", R"(Data\UI\title.png)");
	m_program_info.texture_manager->LoadButtonTexture("play", R"(Data\UI\Buttons)");
	m_program_info.texture_manager->LoadButtonTexture("how_to_play", R"(Data\UI\Buttons)");
	m_program_info.texture_manager->LoadButtonTexture("exit", R"(Data\UI\Buttons)");

	// load font
	font_man.LoadFont("arial", "Data/UI/Fonts/arial.ttf");

	// add elements
	element_man.Init(m_program_info, input_man);

	auto& cursor = element_man.Add<CursorElement>("cursor"); // config
	cursor.SetTextures("cursor_color", "cursor_outline");
	cursor.SetScale(m_view.getSize().y / window_ui_scale);

	auto& sprite = element_man.Add<SpriteElement>("title", 2.f);
	sprite.SetTexture("title");
	sprite.SetScale(m_view.getSize().y / window_ui_scale);
	sprite.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y - sprite.GetSprite().getGlobalBounds().height / 2));

	auto& play_button = element_man.Add<PlayButtonElement>("play_button", 1.5f);
	play_button.SetTexture("play");
	play_button.SetScale(m_view.getSize().y / window_ui_scale);
	play_button.SetPosition(m_view.getCenter());

	auto& how_to_play_button = element_man.Add<HowToPlayButtonElement>("how_to_play_button", 1.5f);
	how_to_play_button.SetTexture("how_to_play");
	how_to_play_button.SetScale(m_view.getSize().y / window_ui_scale);
	how_to_play_button.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y + sprite.GetSprite().getGlobalBounds().height / 4));

	auto& exit_button = element_man.Add<ExitButtonElement>("exit_button", 1.5f);
	exit_button.SetTexture("exit");
	exit_button.SetScale(m_view.getSize().y / window_ui_scale);
	exit_button.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y + sprite.GetSprite().getGlobalBounds().height / 2));

	auto& timer = element_man.Add<TimerElement>("timer");
	timer.SetPosition({ m_view.getCenter().x, m_view.getCenter().y - m_view.getSize().y / 2 });
	timer.SetFont(*font_man.GetFont("arial"));
	timer.SetSize(24);
}

void UI::Update()
{
	m_program_info.window->setView(m_view);

	{ // cursor
		auto& cursor = element_man.Get<CursorElement>("cursor");
		cursor.SetPosition(m_program_info.window->mapPixelToCoords(sf::Mouse::getPosition(*m_program_info.window)));
	}
}

void UI::Draw()
{
	m_program_info.window->setView(m_view);

	if (*m_program_state == Program::State::IN_MAIN_MENU)
	{
		{ // title
			const auto& title = element_man.Get<SpriteElement>("title");
			m_program_info.window->draw(title.GetSprite());
		}
		{ // play button
			const auto& play_button = element_man.Get<ButtonElement>("play_button");
			m_program_info.window->draw(play_button.GetSprite());
		}
		{ // how to play button
			const auto& how_to_play_button = element_man.Get<ButtonElement>("how_to_play_button");
			m_program_info.window->draw(how_to_play_button.GetSprite());
		}
		{ // exit button
			const auto& exit_button = element_man.Get<ButtonElement>("exit_button");
			m_program_info.window->draw(exit_button.GetSprite());
		}
	}
	else if (*m_program_state == Program::State::IN_GAME)
	{
		{ // timer
			const auto& timer = element_man.Get<TextElement>("timer");
			m_program_info.window->draw(timer.GetText());
		}
	}
	{ // cursor
		const auto& cursor = element_man.Get<CursorElement>("cursor");
		m_program_info.window->draw(cursor.GetColorSprite());
		m_program_info.window->draw(cursor.GetOutlineSprite());
	}
}

const sf::View& UI::GetView() const
{
	return m_view;
}

void UI::On(const lev::Event& event)
{
	if (event.Is<WindowResizedEvent>())
	{
		m_view.setSize(static_cast<sf::Vector2f>(m_program_info.window->getSize()));
		lev::Emit<UIRescaleEvent>(m_view.getSize().y / window_ui_scale, m_view);
	}
	else if (event.Is<UISettingEvent>())
	{
		const auto& ui_setting = static_cast<const UISettingEvent&>(event);
		element_man.Get<CursorElement>("cursor").SetColor(ui_setting.crosshair_col);
	}
}
