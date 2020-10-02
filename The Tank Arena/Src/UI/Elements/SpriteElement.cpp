#include "SpriteElement.hpp"

#include "../Events.hpp"

SpriteElement::SpriteElement(const Scale& xscale)
    : xscale(xscale)
{
    Listen<UIRescaleEvent>();
}

SpriteElement& SpriteElement::SetPosition(const sf::Vector2f& pos)
{
    sprite.setPosition(pos);

    return *this;
}

SpriteElement& SpriteElement::SetTexture(const std::string& id)
{
    sprite.setTexture(*program_info->texture_manager->GetTexture(id));
    sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);

    return *this;
}

SpriteElement& SpriteElement::SetScale(const Scale& scale)
{
    sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());

    return *this;
}

const sf::Sprite& SpriteElement::GetSprite() const
{
    return sprite;
}

const Scale& SpriteElement::GetExScale() const
{
    return xscale;
}

void SpriteElement::On(const lev::Event& event)
{
    if (event.Is<UIRescaleEvent>())
    {
        const auto& rescale_event = static_cast<const UIRescaleEvent&>(event);
        SetScale(rescale_event.scale);
        SetPosition(sf::Vector2f(rescale_event.view.getCenter().x, rescale_event.view.getCenter().y - sprite.getGlobalBounds().height / 2));
    }
}
