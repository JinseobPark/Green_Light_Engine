/****************************************************************************
\file   Factory.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  ObjectFactory handles the creation, management,
		and destruction of all objects
*****************************************************************************/


#include "Factory.h"
#include "DebugTool.h"
#include "Application.h"
#include "../GoodTest/GoodTest/PlayerController.h"

using namespace GLE;

namespace GLE
{
	ObjectFactory* FACTORY = nullptr;
}

ObjectFactory::ObjectFactory()
{
	DEBUG_ASSERT(FACTORY != nullptr, "Factory already created! There can only be 1!");
	FACTORY = this;
	LastObjectID = 0; //There is over 4 billion numbers
}

ObjectFactory::~ObjectFactory()
{
	DestroyAllObject();
}

void ObjectFactory::Initialize()
{

}

void ObjectFactory::Update(float /*dt*/)
{
	//Todo : Delete all object in the ObjectToBeDeleted list
	for (auto it = ObjectsToBeDeleted.begin(); it != ObjectsToBeDeleted.end(); ++it)
	{
		Object* gameObject = *it;
		auto IDit = ObjectIDMap.find(gameObject->objID);

		//DEBUG_ASSERT(IDit == ObjectIDMap.end(), "Object was bad memory.");
		if (IDit != ObjectIDMap.end())
		{
			//delete and remove form the map
			delete gameObject;
			ObjectIDMap.erase(IDit);
		}
	}
	ObjectsToBeDeleted.clear();
}

void ObjectFactory::Destory(Object* gameObject)
{
	ObjectsToBeDeleted.push_back(gameObject);
}

void ObjectFactory::DestroyAllObject()
{
	printf("deleted1\n");

	for (auto it : ObjectIDMap)
		delete it.second;

	ObjectIDMap.clear();

	LastObjectID = 0;
	
	printf("deleted2\n");
}

void ObjectFactory::IDGameObject(Object* gameObject)
{
	//Just increment the LastObjectID used. Does not handle overflow
	//but it would take over 4 billion objects to break
	++LastObjectID;
	gameObject->objID = LastObjectID;

	//Store the game object in the ObjectIDMap
	ObjectIDMap[LastObjectID] = gameObject;
}

Object* ObjectFactory::GetObjectwID(ObjectID id)
{
	std::map<ObjectID, Object*>::iterator it = ObjectIDMap.find(id);
	if (it != ObjectIDMap.end())
		return it->second;

	return nullptr;
}


Object* ObjectFactory::CreateEmptyObject()
{
	Object* gameObject = new Object();
	IDGameObject(gameObject);

	return gameObject;
}

Object* ObjectFactory::CreatePlayer(const Vector2& position, const Vector2& vel, const Vector2& scale)
{
	Object* player = CreateEmptyObject();

	Transform * transform = new Transform();
	transform->SetPosition(position);
	player->AddComponent(transform);

	//Todo : add Sprite and Body components

	Sprite* sprite = new Sprite();
	sprite->Size.Set(scale);
	//Todo : Load texture and get texture id
	sprite->TextureID = 1;
	player->AddComponent(sprite);
	player->AddComponent(new PlayerController());
	player->AddComponent(new RigidBody(vel, DYNAMIC, PLAYER_1));

	player->Initialize();
	return player;
}

Object* ObjectFactory::CreateWall(const Vector2& position, const Vector2& vel, const Vector2& scale)
{
	Object* wall = CreateEmptyObject();

	Transform * transform = new Transform();
	transform->SetPosition(position);
	wall->AddComponent(transform);

	//Todo : add Sprite and Body components
	Sprite* sprite = new Sprite();
	sprite->Size.Set(scale);
	//Todo : Load texture and get texture id
	sprite->TextureID = 0;
	wall->AddComponent(sprite);
	wall->AddComponent(new RigidBody(vel, STATIC, WALL));

	wall->Initialize();
	return wall;
}

Object* ObjectFactory::CreateItem(const Vector2& position, const Vector2& vel, const Vector2& scale)
{
	Object* item = CreateEmptyObject();
	Transform * transform = new Transform();
	transform->SetPosition(position);
	item->AddComponent(transform);

	//Todo : add Sprite and Body components
	Sprite* sprite = new Sprite();
	sprite->Size.Set(scale);
	//Todo : Load texture and get texture id
	sprite->TextureID = 0;
	item->AddComponent(sprite);
	item->AddComponent(new RigidBody(vel, DYNAMIC, ITEM));
	item->Initialize();
	return item;
}