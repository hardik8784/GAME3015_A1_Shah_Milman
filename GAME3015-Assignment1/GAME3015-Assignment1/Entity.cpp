#include "Entity.h"

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

class Entity{
public:
	float velocity;
	
private:
	virtual void updateCurrent(GameTimer dt);
};
