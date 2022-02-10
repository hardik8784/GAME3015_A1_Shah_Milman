#pragma once

#include "../../Common/d3dApp.h"
#include "../../Common/MathHelper.h"
#include "../../Common/UploadBuffer.h"
#include "../../Common/GeometryGenerator.h"
#include "../../Common/Camera.h"
#include "FrameResource.h"
#include "Waves.h"
#include <ctime>
#include "SceneNode.h"
#include"Player.h"
#include"AirCraft.h"
#include <vector>

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")


enum class RenderLayer : int
{
	Opaque = 0,
	Transparent,
	AlphaTested,
	AlphaTestedTreeSprites,
	Count
};

class World
{
public:
	explicit World(std::vector<std::unique_ptr<RenderItem>>& renderList, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials,
		std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries,
		std::vector<RenderItem*> RitemLayer[],
		Microsoft::WRL::ComPtr<ID3D12Device> Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList);
	explicit World();
	void update(GameTimer dt, std::vector<std::unique_ptr<RenderItem>>& renderList);
	void draw();

public:
	void loadTextures(std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures,
		Microsoft::WRL::ComPtr<ID3D12Device> Device,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList);
	
	void SetRaptorTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList,
		std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures);
	void SetEagleTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList,
		std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures);
	void SetBackgroundTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList,
		std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures);

	void buildMaterials(std::unordered_map<std::string, std::unique_ptr<Material>>& Materials);

	void BuildRaptorMaterial(std::unique_ptr<Material>& RAPTOR, int& matIndex);
	void BuildEagleMaterial(std::unique_ptr<Material>& EAGLE, int& matIndex);
	void BuildBackgroundMaterial(std::unique_ptr<Material>& BackgroundTex, int& matIndex);

	void buildScene(std::vector<std::unique_ptr<RenderItem>>& renderList,
		std::unordered_map<std::string, std::unique_ptr<Material>>& Materials,
		std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries,
		std::vector<RenderItem*> RitemLayer[]);


	void InstantiateEagle_Left(DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex,
		std::unordered_map<std::string, std::unique_ptr<Material>>& Materials,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries,
		std::vector<RenderItem*>  RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList);

	void InstantiateEagle_Right(DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex,
		std::unordered_map<std::string, std::unique_ptr<Material>>& Materials,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries,
		std::vector<RenderItem*>  RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList);

	void InstantiateRaptor(const DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex,
		std::unordered_map<std::string, std::unique_ptr<Material>>& Materials,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries,
		std::vector<RenderItem*>  RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList);

	void InstantiateSecondBackground(UINT& objCBIndex, std::unordered_map<std::string,
		std::unique_ptr<Material>>&Materials, std::unordered_map<std::string,
		std::unique_ptr<MeshGeometry>>&Geometries, std::vector<RenderItem*>  RitemLayer[],
		std::vector<std::unique_ptr<RenderItem>>& renderList);

	void InstantiateFirstBackground(UINT& objCBIndex, std::unordered_map<std::string,
		std::unique_ptr<Material>>&Materials, std::unordered_map<std::string,
		std::unique_ptr<MeshGeometry>>&Geometries, std::vector<RenderItem*>  RitemLayer[],
		std::vector<std::unique_ptr<RenderItem>>& renderList);


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4 mWorldBounds;
	XMVECTOR mSpawnPosition;
	float mScrollSpeed;
	//Player* mPlayer;
	//Player* mPlayer_left;
	//Player* mPlayer_right;
	Aircraft* mAircraft;
	Aircraft* mAircraft_left;
	Aircraft* mAircraft_right;
	Entity background;
	Entity background2;
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