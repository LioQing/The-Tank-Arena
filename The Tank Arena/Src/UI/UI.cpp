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
	m_program_info.texture_manager->LoadTexture("background", R"(Data\UI\background.png)");

	m_program_info.texture_manager->LoadButtonTexture("play", R"(Data\UI\Buttons)");
	m_program_info.texture_manager->LoadButtonTexture("how_to_play", R"(Data\UI\Buttons)");
	m_program_info.texture_manager->LoadButtonTexture("exit", R"(Data\UI\Buttons)");
	m_program_info.texture_manager->LoadButtonTexture("main_menu", R"(Data\UI\Buttons)");

	m_program_info.texture_manager->LoadTexture("square_button", R"(Data\UI\Buttons\square_button.png)");
	m_program_info.texture_manager->LoadTexture("square_button_clicked", R"(Data\UI\Buttons\square_button_clicked.png)");
	m_program_info.texture_manager->LoadTexture("numbers_hover", R"(Data\UI\Numbers\hover.png)");
	m_program_info.texture_manager->LoadTexture("numbers_clicked", R"(Data\UI\Numbers\clicked.png)");
	m_program_info.texture_manager->LoadTexture("numbers_idle", R"(Data\UI\Numbers\idle.png)");

	// load font
	font_man.LoadFont("jbm", "Data/UI/Fonts/JetBrainsMono-Regular.ttf");

	// add elements
	element_man.Init(m_program_info, input_man, m_view);

	auto& cursor = element_man.Add<CursorElement>("cursor"); // config
	cursor.SetTextures("cursor_color", "cursor_outline");
	cursor.SetScale(m_view.getSize().y / window_ui_scale);

	auto& title = element_man.Add<SpriteElement>("title", 2.f);
	title.SetTexture("title");
	title.SetScale(m_view.getSize().y / window_ui_scale);
	title.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y - m_view.getSize().y * 3 / 12));

	auto& background = element_man.Add<SpriteElement>("background", .25f);
	background.SetTexture("background");
	background.SetScale(m_view.getSize().y / window_ui_scale);
	background.SetPosition(m_view.getCenter());
	background.SetColor(sf::Color(255, 255, 255, 127));

	auto& play_button = element_man.Add<PlayButtonElement>("play_button", 1.5f, static_cast<uint32_t>(Program::State::IN_MAIN_MENU));
	play_button.SetTexture("play");
	play_button.SetScale(m_view.getSize().y / window_ui_scale);
	play_button.SetPosition(m_view.getCenter());

	auto& how_to_play_button = element_man.Add<HowToPlayButtonElement>("how_to_play_button", 1.5f, static_cast<uint32_t>(Program::State::IN_MAIN_MENU));
	how_to_play_button.SetTexture("how_to_play");
	how_to_play_button.SetScale(m_view.getSize().y / window_ui_scale);
	how_to_play_button.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y + title.GetSprite().getGlobalBounds().height / 4));

	auto& exit_button = element_man.Add<ExitButtonElement>("exit_button", 1.5f, static_cast<uint32_t>(Program::State::IN_MAIN_MENU));
	exit_button.SetTexture("exit");
	exit_button.SetScale(m_view.getSize().y / window_ui_scale);
	exit_button.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y + title.GetSprite().getGlobalBounds().height / 2));

	auto& timer = element_man.Add<TimerElement>("timer");
	timer.SetFont(*font_man.GetFont("jbm"));

	auto& main_menu_button = element_man.Add<MainMenuButtonElement>("main_menu_button", 1.5f, static_cast<uint32_t>(Program::State::ENDGAME_MENU));
	main_menu_button.SetTexture("main_menu");
	main_menu_button.SetScale(m_view.getSize().y / window_ui_scale);
	main_menu_button.SetPosition(sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y + title.GetSprite().getGlobalBounds().height * 5 / 6));

	auto& stat_bullet_shot = element_man.Add<StatElement>("stat_bullet_shot", StatElement::Type::BULLET_SHOT);
	stat_bullet_shot.SetPosition({ m_view.getCenter().x - 150, m_view.getCenter().y });
	stat_bullet_shot.SetFont(*font_man.GetFont("jbm"));
	stat_bullet_shot.SetSize(28);

	auto& stat_tank_destroyed = element_man.Add<StatElement>("stat_tank_destroyed", StatElement::Type::TANK_DESTROYED);
	stat_tank_destroyed.SetPosition({ m_view.getCenter().x - 150, m_view.getCenter().y + 36 });
	stat_tank_destroyed.SetFont(*font_man.GetFont("jbm"));
	stat_tank_destroyed.SetSize(26);

	for (auto i = 0; i < number_of_level; ++i)
	{
		auto& level_button = element_man.Add<LevelButtonElement>("level_" + std::to_string(i + 1) + "_button", 1.5f, static_cast<uint32_t>(Program::State::LEVEL_MENU));
		level_button.SetTexture();
		level_button.SetNumber(i + 1);
		level_button.SetScale(m_view.getSize().y / window_ui_scale);
		level_button.SetPosition({ 
			m_view.getCenter().x - m_view.getSize().x * 1 / 3 + m_view.getSize().x * (i % 10) / 15.f, 
			m_view.getCenter().y - m_view.getSize().y * 1 / 5 + m_view.getSize().y * (i / 10) / 5.f });
	}
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
		{ // background
			const auto& background = element_man.Get<SpriteElement>("background");
			m_program_info.window->draw(background.GetSprite());
		}
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
	else if (*m_program_state == Program::State::ENDGAME_MENU)
	{
		{ // main menu button
			const auto& main_menu_button = element_man.Get<ButtonElement>("main_menu_button");
			m_program_info.window->draw(main_menu_button.GetSprite());
		}
		{ // stat bullet shot
			const auto& stat_bullet_shot = element_man.Get<StatElement>("stat_bullet_shot");
			m_program_info.window->draw(stat_bullet_shot.GetText());
		}
		{ // stat tank destroyed
			const auto& stat_tank_destroyed = element_man.Get<StatElement>("stat_tank_destroyed");
			m_program_info.window->draw(stat_tank_destroyed.GetText());
		}
		{ // timer
			const auto& timer = element_man.Get<TextElement>("timer");
			m_program_info.window->draw(timer.GetText());
		}
	}
	else if (*m_program_state == Program::State::LEVEL_MENU)
	{
		{ // background
			const auto& background = element_man.Get<SpriteElement>("background");
			m_program_info.window->draw(background.GetSprite());
		}
		{ // level button
			for (auto i = 0; i < number_of_level; ++i)
			{
				const auto& level_button = static_cast<const LevelButtonElement&>(element_man.Get<ButtonElement>("level_" + std::to_string(i + 1) + "_button"));
				m_program_info.window->draw(level_button.GetButtonSprite());
				for (auto j = 0; j < 2; ++j)
					m_program_info.window->draw(level_button.GetNumberSprite(j));
			}
		}
	}
	{ // cursor
		const auto& cursor = element_man.Get<CursorElement>("cursor");
		m_program_info.window->draw(cursor.GetColorSprite());
		m_program_info.window->draw(cursor.GetOutlineSprite());
	}
}

void UI::Input()
{
	sf::Event event;
	while (m_program_info.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			*m_program_state = Program::State::CLOSED;
			m_program_info.window->close();
		}
		else if (event.type == sf::Event::Resized)
		{
			lev::Emit<WindowResizedEvent>();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			lev::Emit<InputEvent>(lio::stolvec<float>(m_program_info.window->mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y })), event.mouseButton.button);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			lev::Emit<InputEvent>(lio::stolvec<float>(m_program_info.window->mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y })), false, true);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			lev::Emit<InputEvent>(lio::stolvec<float>(m_program_info.window->mapPixelToCoords(
				{ event.mouseMove.x, event.mouseMove.y })), true, false);
		}
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
