#pragma once
#include "Entity.h"

class Player
{
public:
	enum Type {
		Eagle,
		Raptor, 
};
private:
	virtual void drawCurrent(ID3D12GraphicsCommandList* cmdList, RenderItem& ritems);
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


