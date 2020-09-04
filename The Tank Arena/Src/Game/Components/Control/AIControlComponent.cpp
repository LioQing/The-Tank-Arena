#include "AIControlComponent.hpp"

AIControlComponent::AIControlComponent()
{
	turret_dir.store(std::make_shared<lio::Vec2f>(0.f, 0.f));
}
