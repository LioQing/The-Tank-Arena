#include "GunfireSpriteComponent.hpp"

GunfireSpriteComponent::GunfireSpriteComponent(ProgramInfo& program_info, const lio::Vec2f& pos, float rot)
{
	sprite.setTexture(*program_info.texture_manager->GetTexture("gunfire"));
	sprite.setScale((*program_info.scale).sfVec2f());
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height);

	sprite.setPosition(lio::ltosvec<float>(pos));
	sprite.setRotation(rot * 180.0 / M_PI);
}
