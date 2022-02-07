#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	enum class Type {
		Eagle,
		Raptor, 
	};


public:

	// Constructor
	Player(Type type);

	// Methods
	void Update();

private:
	// Attributes
	Type type;


	// Methods
	virtual void drawCurrent(GameTimer dt);
};

//* Week3-Demo7 Code
//
//#pragma once
//
//#include <Entity.hpp>
//#include <ResourceIdentifiers.hpp>
//
//#include <SFML/Graphics/Sprite.hpp>
//
//
//class Aircraft : public Entity
//{
//public:
//	enum Type
//	{
//		Eagle,
//		Raptor,
//	};
//
//
//public:
//	Aircraft(Type type, const TextureHolder& textures);
//
//
//private:
//	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
//
//
//private:
//	Type				mType;
//	sf::Sprite			mSprite;
//};
//


