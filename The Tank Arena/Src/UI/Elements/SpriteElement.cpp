#include "SpriteElement.hpp"

#include "../Events.hpp"

SpriteElement::SpriteElement(const Scale& xscale)
    : xscale(xscale)
{
    Listen<UIRescaleEvent>();
}

void SpriteElement::SetPosition(const sf::Vector2f& pos)
{
    sprite.setPosition(pos);
}

void SpriteElement::SetTexture(const std::string& id)
{
    sprite.setTexture(*program_info->texture_manager->GetTexture(id));
    sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
}

void SpriteElement::SetScale(const Scale& scale)
{
    sprite.setScale(Scale(scale.Get() * xscale.Get()).sfVec2f());
}

void SpriteElement::SetColor(const sf::Color& col)
{
    sprite.setColor(col);
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
        auto factor = rescale_event.scale / (lio::stolvec<float>(sprite.getScale()) / xscale.Get());
        auto center = lio::stolvec<float>(rescale_event.view.getCenter());

        SetScale(rescale_event.scale);
        SetPosition(lio::ltosvec<float>(center + (lio::stolvec<float>(sprite.getPosition()) - center) * factor));
    }
}
