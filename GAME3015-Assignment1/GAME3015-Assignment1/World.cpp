#include "World.h"

float PlayerBounds = 1.8f;
float BackgroundBounds = 20.0f;

World::World(std::vector<std::unique_ptr<RenderItem>>& renderList, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], Microsoft::WRL::ComPtr<ID3D12Device> Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList)
{
	loadTextures(Textures, Device, mCommandList);
	buildMaterials(Materials);
	buildScene(renderList, Materials, Textures, Geometries, RitemLayer);
}

World::World()
{
}

void World::update(GameTimer dt, std::vector<std::unique_ptr<RenderItem>>& renderList)
{
	if (XMVectorGetX(mAircraft->mPosition) > PlayerBounds || XMVectorGetX(mAircraft->mPosition) < -PlayerBounds)
	{
		mAircraft->mVelocity *= -1;
		mAircraft_left->mVelocity *= -1;
		mAircraft_right->mVelocity *= -1;
	}


	if (XMVectorGetZ(background.mPosition) < -BackgroundBounds)
	{
		background.mPosition = { XMVectorGetX(background.mPosition) , XMVectorGetY(background.mPosition) , BackgroundBounds };
	}

	if (XMVectorGetZ(background2.mPosition) < -BackgroundBounds)
	{
		background2.mPosition = { XMVectorGetX(background2.mPosition) , XMVectorGetY(background2.mPosition) , BackgroundBounds };
	}

	mAircraft->update(dt, renderList);

	mAircraft_left->update(dt, renderList);

	mAircraft_right->update(dt, renderList);

	
	background.update(dt, renderList);
	background2.update(dt, renderList);

	// Apply movements
	mSceneGraph.update(dt, renderList);
}

void World::draw()
{
}

void World::loadTextures(std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures, Microsoft::WRL::ComPtr<ID3D12Device> Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList)
{
	SetBackgroundTexture(Device, mCommandList, Textures);

	SetEagleTexture(Device, mCommandList, Textures);

	SetRaptorTexture(Device, mCommandList, Textures);
}

void World::SetRaptorTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList, std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures)
{
	auto RaptorTex = std::make_unique<Texture>();
	RaptorTex->Name = "RaptorTex";
	RaptorTex->Filename = L"../../Textures/Raptor.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(Device.Get(),
		mCommandList.Get(), RaptorTex->Filename.c_str(),
		RaptorTex->Resource, RaptorTex->UploadHeap));
	Textures[RaptorTex->Name] = std::move(RaptorTex);
}

void World::SetEagleTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList, std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures)
{
	auto EagleTex = std::make_unique<Texture>();
	EagleTex->Name = "EagleTex";
	EagleTex->Filename = L"../../Textures/Eagle.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(Device.Get(),
		mCommandList.Get(), EagleTex->Filename.c_str(),
		EagleTex->Resource, EagleTex->UploadHeap));
	Textures[EagleTex->Name] = std::move(EagleTex);
}

void World::SetBackgroundTexture(Microsoft::WRL::ComPtr<ID3D12Device>& Device, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& mCommandList, std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures)
{
	auto backgroundTex = std::make_unique<Texture>();
	backgroundTex->Name = "BackgroundTex";
	backgroundTex->Filename = L"../../Textures/Desert.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(Device.Get(),
		mCommandList.Get(), backgroundTex->Filename.c_str(),
		backgroundTex->Resource, backgroundTex->UploadHeap));
	Textures[backgroundTex->Name] = std::move(backgroundTex);
}


void World::buildMaterials(std::unordered_map<std::string, std::unique_ptr<Material>>& Materials)
{
	int matIndex = 0;
	auto BackgroundTex = std::make_unique<Material>();
	BuildBackgroundMaterial(BackgroundTex, matIndex);

	auto EAGLE = std::make_unique<Material>();
	BuildEagleMaterial(EAGLE, matIndex);

	auto RAPTOR = std::make_unique<Material>();
	BuildRaptorMaterial(RAPTOR, matIndex);

	Materials["BackgroundTex"] = std::move(BackgroundTex);
	Materials["EagleTex"] = std::move(EAGLE);
	Materials["RaptorTex"] = std::move(RAPTOR);

}

void World::BuildRaptorMaterial(std::unique_ptr<Material>& RAPTOR, int& matIndex)
{
	RAPTOR->Name = "Raptor";
	RAPTOR->MatCBIndex = matIndex;
	RAPTOR->DiffuseSrvHeapIndex = matIndex++;
	RAPTOR->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	RAPTOR->FresnelR0 = XMFLOAT3(0.01f, 0.01f, 0.01f);
	RAPTOR->Roughness = 0.125f;
}

void World::BuildEagleMaterial(std::unique_ptr<Material>& EAGLE, int& matIndex)
{
	EAGLE->Name = "Eagle";
	EAGLE->MatCBIndex = matIndex;
	EAGLE->DiffuseSrvHeapIndex = matIndex++;
	EAGLE->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	EAGLE->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	EAGLE->Roughness = 0.25f;
}

void World::BuildBackgroundMaterial(std::unique_ptr<Material>& BackgroundTex, int& matIndex)
{
BackgroundTex->Name = "BackgroundTex";
BackgroundTex->MatCBIndex = matIndex;
BackgroundTex->DiffuseSrvHeapIndex = matIndex++;
BackgroundTex->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
BackgroundTex->FresnelR0 = XMFLOAT3(0.01f, 0.01f, 0.01f);
BackgroundTex->Roughness = 0.125f;
}


void World::buildScene(std::vector<std::unique_ptr<RenderItem>>& renderList, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<Texture>>& Textures, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[])
{
	UINT objCBIndex = 0;

	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	InstantiateFirstBackground(objCBIndex, Materials, Geometries, RitemLayer, renderList);

	InstantiateSecondBackground(objCBIndex, Materials, Geometries, RitemLayer, renderList);

	XMVECTOR spawnpoint = { -1.0f , 1 , -1 };

	InstantiateRaptor(spawnpoint, objCBIndex, Materials, Geometries, RitemLayer, renderList);

	InstantiateEagle_Right(spawnpoint, objCBIndex, Materials, Geometries, RitemLayer, renderList);

	InstantiateEagle_Left(spawnpoint, objCBIndex, Materials, Geometries, RitemLayer, renderList);
	
}

void World::InstantiateEagle_Left(DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList)
{

	mAircraft_left = new Aircraft(Aircraft::Type::Eagle);
	mAircraft_left->renderItem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&mAircraft_left->renderItem->World, XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixTranslation(-1.25f, 1, -1.25));/// can choose your scaling here
	spawnpoint = { -1.25f , 1.0f , -1.25f };
	mAircraft_left->mPosition = spawnpoint;
	mAircraft_left->mVelocity = { 0.5f, 0.0f, 0.0f };
	mAircraft_left->ScaleFactor = { 0.01f, 0.01f, 0.01f };
	XMStoreFloat4x4(&mAircraft_left->renderItem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	mAircraft_left->renderItem->ObjCBIndex = objCBIndex++;
	mAircraft_left->renderItem->Mat = Materials["EagleTex"].get();
	mAircraft_left->renderItem->Geo = Geometries["groundGeo"].get();
	mAircraft_left->renderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mAircraft_left->renderItem->IndexCount = mAircraft_left->renderItem->Geo->DrawArgs["ground"].IndexCount;
	mAircraft_left->renderItem->StartIndexLocation = mAircraft_left->renderItem->Geo->DrawArgs["ground"].StartIndexLocation;
	mAircraft_left->renderItem->BaseVertexLocation = mAircraft_left->renderItem->Geo->DrawArgs["ground"].BaseVertexLocation;

	RitemLayer[(int)RenderLayer::AlphaTested].push_back(mAircraft_left->renderItem.get());
	renderList.push_back(std::move(mAircraft_left->renderItem));
	mAircraft_left->renderIndex = renderList.size() - 1;
}

void World::InstantiateEagle_Right(DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList)
{
	mAircraft_right = new Aircraft(Aircraft::Type::Eagle);
	mAircraft_right->renderItem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&mAircraft_right->renderItem->World, XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixTranslation(-0.75f, 1, -1.25));/// can choose your scaling here
	spawnpoint = { -0.75f , 1.0f , -1.25f };
	mAircraft_right->mPosition = spawnpoint;
	mAircraft_right->mVelocity = { 0.5f, 0.0f, 0.0f };
	mAircraft_right->ScaleFactor = { 0.01f, 0.01f, 0.01f };
	XMStoreFloat4x4(&mAircraft_right->renderItem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	mAircraft_right->renderItem->ObjCBIndex = objCBIndex++;
	mAircraft_right->renderItem->Mat = Materials["EagleTex"].get();
	mAircraft_right->renderItem->Geo = Geometries["groundGeo"].get();
	mAircraft_right->renderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mAircraft_right->renderItem->IndexCount = mAircraft_right->renderItem->Geo->DrawArgs["ground"].IndexCount;
	mAircraft_right->renderItem->StartIndexLocation = mAircraft_right->renderItem->Geo->DrawArgs["ground"].StartIndexLocation;
	mAircraft_right->renderItem->BaseVertexLocation = mAircraft_right->renderItem->Geo->DrawArgs["ground"].BaseVertexLocation;

	RitemLayer[(int)RenderLayer::AlphaTested].push_back(mAircraft_right->renderItem.get());
	renderList.push_back(std::move(mAircraft_right->renderItem));
	mAircraft_right->renderIndex = renderList.size() - 1;
}

void World::InstantiateRaptor(const DirectX::XMVECTOR& spawnpoint, UINT& objCBIndex, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList)
{

	mAircraft = new Aircraft(Aircraft::Type::Raptor);
	mAircraft->renderItem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&mAircraft->renderItem->World, XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixTranslation(-1.0f, 1, -1));/// can choose your scaling here
	mAircraft->mPosition = spawnpoint;
	mAircraft->mVelocity = { 0.5f, 0.0f, 0.0f };
	mAircraft->ScaleFactor = { 0.01f, 0.01f, 0.01f };
	XMStoreFloat4x4(&mAircraft->renderItem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	mAircraft->renderItem->ObjCBIndex = objCBIndex++;
	mAircraft->renderItem->Mat = Materials["RaptorTex"].get();
	mAircraft->renderItem->Geo = Geometries["groundGeo"].get();
	mAircraft->renderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mAircraft->renderItem->IndexCount = mAircraft->renderItem->Geo->DrawArgs["ground"].IndexCount;
	mAircraft->renderItem->StartIndexLocation = mAircraft->renderItem->Geo->DrawArgs["ground"].StartIndexLocation;
	mAircraft->renderItem->BaseVertexLocation = mAircraft->renderItem->Geo->DrawArgs["ground"].BaseVertexLocation;

	RitemLayer[(int)RenderLayer::AlphaTested].push_back(mAircraft->renderItem.get());
	renderList.push_back(std::move(mAircraft->renderItem));
	mAircraft->renderIndex = renderList.size() - 1;
}

void World::InstantiateSecondBackground(UINT& objCBIndex, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList)
{
	background2.renderItem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&background2.renderItem->World, XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(0.0f, 0, 1));/// can choose your scaling here
	XMStoreFloat4x4(&background2.renderItem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	XMVECTOR spawnpointbackground2 = { 0, 0, 20 };
	background2.mPosition = spawnpointbackground2;
	background2.mVelocity = { 0.0f, 0.0f, -0.5f };
	background2.ScaleFactor = { 1.0f, 1.0f, 1.0f };
	background2.renderItem->ObjCBIndex = objCBIndex++;
	background2.renderItem->Mat = Materials["BackgroundTex"].get();
	background2.renderItem->Geo = Geometries["groundGeo"].get();
	background2.renderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	background2.renderItem->IndexCount = background2.renderItem->Geo->DrawArgs["ground"].IndexCount;
	background2.renderItem->StartIndexLocation = background2.renderItem->Geo->DrawArgs["ground"].StartIndexLocation;
	background2.renderItem->BaseVertexLocation = background2.renderItem->Geo->DrawArgs["ground"].BaseVertexLocation;

	RitemLayer[(int)RenderLayer::Opaque].push_back(background2.renderItem.get());
	renderList.push_back(std::move(background2.renderItem));
	background2.renderIndex = renderList.size() - 1;
}

void World::InstantiateFirstBackground(UINT& objCBIndex, std::unordered_map<std::string, std::unique_ptr<Material>>& Materials, std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& Geometries, std::vector<RenderItem*> RitemLayer[], std::vector<std::unique_ptr<RenderItem>>& renderList)
{
	background.renderItem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&background.renderItem->World, XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(0.0f, 0, 0));/// can choose your scaling here
	XMStoreFloat4x4(&background.renderItem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	XMVECTOR spawnpointBackground = { 0, 0, 0 };
	background.mPosition = spawnpointBackground;
	background.mVelocity = { 0.0f, 0.0f, -0.5f };
	background.ScaleFactor = { 1.0f, 1.0f, 1.0f };
	background.renderItem->ObjCBIndex = objCBIndex++;
	background.renderItem->Mat = Materials["BackgroundTex"].get();
	background.renderItem->Geo = Geometries["groundGeo"].get();
	background.renderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	background.renderItem->IndexCount = background.renderItem->Geo->DrawArgs["ground"].IndexCount;
	background.renderItem->StartIndexLocation = background.renderItem->Geo->DrawArgs["ground"].StartIndexLocation;
	background.renderItem->BaseVertexLocation = background.renderItem->Geo->DrawArgs["ground"].BaseVertexLocation;

	RitemLayer[(int)RenderLayer::Opaque].push_back(background.renderItem.get());
	renderList.push_back(std::move(background.renderItem));
	background.renderIndex = renderList.size() - 1;
}

//
//#pragma region step 2
//#include <World.hpp>
//
//#include <SFML/Graphics/RenderWindow.hpp>
//
//
//World::World(sf::RenderWindow& window)
//	: mWindow(window)
//	, mWorldView(window.getDefaultView())
//	, mTextures()
//	, mSceneGraph()
//	, mSceneLayers()
//	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
//	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
//	, mScrollSpeed(-50.f)
//	, mPlayerAircraft(nullptr)
//{
//	loadTextures();
//	buildScene();
//
//	// Prepare the view
//	mWorldView.setCenter(mSpawnPosition);
//}
//
//void World::update(sf::Time dt)
//{
//	// Scroll the world
//	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
//
//	// Move the player sidewards (plane scouts follow the main aircraft)
//	sf::Vector2f position = mPlayerAircraft->getPosition();
//	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
//
//	// If player touches borders, flip its X velocity
//	if (position.x <= mWorldBounds.left + 150.f
//		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
//	{
//		velocity.x = -velocity.x;
//		mPlayerAircraft->setVelocity(velocity);
//	}
//
//	// Apply movements
//	mSceneGraph.update(dt);
//}
//
//void World::draw()
//{
//	mWindow.setView(mWorldView);
//	mWindow.draw(mSceneGraph);
//}
//
//void World::loadTextures()
//{
//	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
//	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
//	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
//}
//
//void World::buildScene()
//{
//	// Initialize the different layers
//	for (std::size_t i = 0; i < LayerCount; ++i)
//	{
//		SceneNode::Ptr layer(new SceneNode());
//		mSceneLayers[i] = layer.get();
//
//		mSceneGraph.attachChild(std::move(layer));
//	}
//
//	// Prepare the tiled background
//	sf::Texture& texture = mTextures.get(Textures::Desert);
//	sf::IntRect textureRect(mWorldBounds);
//	texture.setRepeated(true);
//
//	// Add the background sprite to the scene
//	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
//	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
//	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
//
//	// Add player's aircraft
//	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
//	mPlayerAircraft = leader.get();
//	mPlayerAircraft->setPosition(mSpawnPosition);
//	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
//	mSceneLayers[Air]->attachChild(std::move(leader));
//
//	// Add two escorting aircrafts, placed relatively to the main plane
//	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
//	leftEscort->setPosition(-80.f, 50.f);
//	mPlayerAircraft->attachChild(std::move(leftEscort));
//
//	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
//	rightEscort->setPosition(80.f, 50.f);
//	mPlayerAircraft->attachChild(std::move(rightEscort));
//}
//
//#pragma region step 2
