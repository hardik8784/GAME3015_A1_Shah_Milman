#include "Entity.h"

void Entity::setVelocity(XMVECTOR velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity = XMVECTOR{ vx, vy, vz };
}

XMVECTOR Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(GameTimer dt, std::vector<std::unique_ptr<RenderItem>>& renderList)
{
	XMVECTOR move = mVelocity * dt.DeltaTime();
	mPosition = XMVectorAdd(SceneNode::getWorldPosition(), move);
	renderItem = std::move(renderList[renderIndex]);
	renderItem->NumFramesDirty = 1;
	XMStoreFloat4x4(&renderItem->World, XMMatrixScaling(XMVectorGetX(ScaleFactor), XMVectorGetY(ScaleFactor), XMVectorGetZ(ScaleFactor)) * XMMatrixTranslationFromVector(mPosition));
	renderList[renderIndex] = std::move(renderItem);

}


//* Week3-Demo7 Code
//#include "Entity.hpp"
//
//void Entity::setVelocity(sf::Vector2f velocity)
//{
//	mVelocity = velocity;
//}
//
//void Entity::setVelocity(float vx, float vy)
//{
//	mVelocity.x = vx;
//	mVelocity.y = vy;
//}
//
//sf::Vector2f Entity::getVelocity() const
//{
//	return mVelocity;
//}
//
//void Entity::updateCurrent(sf::Time dt)
//{
//	move(mVelocity * dt.asSeconds());
//}\


