#include "TankSpriteComponent.hpp"

#include "../../../Program.hpp"

TankSpriteComponent::TankSpriteComponent(ProgramInfo& program_info, const std::string& hull_id, const std::string& turret_id)
{
	hull_sprite.setTexture(*program_info.texture_manager->GetTexture(hull_id));
	turret_sprite.setTexture(*program_info.texture_manager->GetTexture(turret_id));

	hull_sprite.setScale((*program_info.scale * .5f).sfVec2f());
	turret_sprite.setScale((*program_info.scale * .5f).sfVec2f());

	hull_sprite.setOrigin(hull_sprite.getTextureRect().width / 2.f, hull_sprite.getTextureRect().height / 2.f);
	turret_sprite.setOrigin(turret_sprite.getTextureRect().width / 2.f, turret_sprite.getTextureRect().height / 2.f);
}
