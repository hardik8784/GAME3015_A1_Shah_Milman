#pragma once

#include "../../Common/d3dApp.h"
#include "../../Common/MathHelper.h"
#include "../../Common/UploadBuffer.h"
#include "../../Common/GeometryGenerator.h"
#include "FrameResource.h"
#include "Waves.h"
#include <ctime>
#include "SceneNode.h"
#include"Player.h"
#include <vector>

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")


class World
{
};
//
//#pragma region step 1
//#pragma once
//
//#include <ResourceHolder.hpp>
//#include <ResourceIdentifiers.hpp>
//#include <SceneNode.hpp>
//#include <SpriteNode.hpp>
//#include <Aircraft.hpp>
//
//#include <SFML/System/NonCopyable.hpp>
//#include <SFML/Graphics/View.hpp>
//#include <SFML/Graphics/Texture.hpp>
//
//#include <array>
//
//
//// Forward declaration
//namespace sf
//{
//	class RenderWindow;
//}
//
//class World : private sf::NonCopyable
//{
//public:
//	explicit							World(sf::RenderWindow& window);
//	void								update(sf::Time dt);
//	void								draw();
//
//
//private:
//	void								loadTextures();
//	void								buildScene();
//
//
//private:
//	enum Layer
//	{
//		Background,
//		Air,
//		LayerCount
//	};
//
//
//private:
//	sf::RenderWindow& mWindow;
//	sf::View							mWorldView;
//	TextureHolder						mTextures;
//
//	SceneNode							mSceneGraph;
//	std::array<SceneNode*, LayerCount>	mSceneLayers;
//
//	sf::FloatRect						mWorldBounds;
//	sf::Vector2f						mSpawnPosition;
//	float								mScrollSpeed;
//	Aircraft* mPlayerAircraft;
//};
//
//#pragma endregion