#include "ProjectileSpriteComponent.hpp"

ProjectileSpriteComponent::ProjectileSpriteComponent(ProgramInfo& program_info, const std::string& id)
{
	sprite.setTexture(*program_info.texture_manager->GetTexture(id));
	sprite.setScale((*program_info.scale).sfVec2f());
	sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height / 2.f);
}