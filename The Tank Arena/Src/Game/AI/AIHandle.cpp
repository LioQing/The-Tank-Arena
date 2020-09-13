#include "AIHandle.hpp"

AIHandle::AIHandle(lic::EntityID id, AIControlComponent& handle)
	: id(id), control(handle)
{
}