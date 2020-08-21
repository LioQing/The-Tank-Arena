#include "UI.hpp"

#include "../Events.hpp"

void UI::Init(ProgramInfo program_info)
{
	// listen events
	Listen<WindowResizedEvent>();

	// store program var
	m_program_info = program_info;
	m_program_info.scale = &m_scale;
	m_scale = 4.f;
	m_view = m_program_info.window->getView();

	// load textures
	m_program_info.texture_manager->LoadTexture("cursor_color", R"(Assets\Cursor\default-color.png)");
	m_program_info.texture_manager->LoadTexture("cursor_outline", R"(Assets\Cursor\default-outline.png)");

	// add elements
	element_man.Init(m_program_info);
	element_man.Add<CursorElement>("cursor")
		.SetTextures("cursor_color", "cursor_outline")
		.SetScale(2.5f)
		.SetColor(sf::Color::Green);
}

void UI::Update()
{
	m_program_info.window->setView(m_view);

	{ //Cursor
		auto& cursor = element_man.Get<CursorElement>("cursor");
		cursor.SetPosition(m_program_info.window->mapPixelToCoords(sf::Mouse::getPosition(*m_program_info.window)));
	}
}

void UI::Draw()
{
	m_program_info.window->setView(m_view);

	{ // Cursor
		auto& cursor = element_man.Get<CursorElement>("cursor");
		m_program_info.window->draw(cursor.GetColorSprite());
		m_program_info.window->draw(cursor.GetOutlineSprite());
	}
}

void UI::On(const lev::Event& event)
{
	if (event.Is<WindowResizedEvent>())
	{
		m_view.setSize(static_cast<sf::Vector2f>(m_program_info.window->getSize()));
	}
}