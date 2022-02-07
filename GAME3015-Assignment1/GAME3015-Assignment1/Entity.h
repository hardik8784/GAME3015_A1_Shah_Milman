#pragma once

#include "SceneNode.h"
#include <vector>


class Entity
{

public:
	void setVelocity(XMVECTOR velocity);
	void setVelocity(float vx, float vy, float vz);
	XMVECTOR getVelocity() const;

	virtual	void updateCurrent(GameTimer dt);
public:
	XMVECTOR mVelocity;
};

//* Week3-Demo7 Code
//#pragma once
//#include <SceneNode.hpp>
//
//
//class Entity : public SceneNode
//
//{
//public:
//	void				setVelocity(sf::Vector2f velocity);
//	void				setVelocity(float vx, float vy);
//	sf::Vector2f		getVelocity() const;
//
//	virtual	void		updateCurrent(sf::Time dt);
//
//public:
//	sf::Vector2f		mVelocity;
//};
//
