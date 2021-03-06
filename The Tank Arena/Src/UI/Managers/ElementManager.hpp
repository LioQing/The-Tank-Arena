#pragma once

#include <unordered_map>
#include <memory>
#include <concepts>
#include <SFML/Graphics.hpp>

#include "../Elements/Element.hpp"
#include "../Elements.hpp"
#include "InputManager.hpp"

class Element; // nani!? this solves problem of "unique_ptr: unspecialized class template cannot be used..." error

template <typename T>
concept IsElement = std::is_base_of<Element, T>::value;

class ElementManager
{
private:

	std::unordered_map<std::string, std::unique_ptr<Element>> elements;

	ProgramInfo* program_info;
	sf::View* view;
	InputManager* input_man;

public:

	void Init(ProgramInfo& program_info, InputManager& input_man, sf::View& view);

	template <IsElement T, typename ...TArgs>
	T& Add(const std::string& id, TArgs ...args)
	{
		auto u_ptr = std::unique_ptr<Element>(new T(std::forward<TArgs>(args)...));
		u_ptr->program_info = program_info;
		u_ptr->ui_view = view;
		auto& ref = *u_ptr;

		if (std::is_base_of<ButtonElement, T>::value)
		{
			input_man->AddButton(static_cast<ButtonElement*>(u_ptr.get()));
		}

		elements.insert(std::make_pair(id, std::move(u_ptr)));
		return static_cast<T&>(ref);
	}

	template <IsElement T>
	T& Get(const std::string& id)
	{
		return static_cast<T&>(*elements.find(id)->second);
	}
};